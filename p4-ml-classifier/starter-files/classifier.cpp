#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <cmath>
#include "csvstream.hpp"

using namespace std;

set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
        words.insert(word);
    }
    return words;
}

class Classifier {
public:
    
    void train(const string &label, const string &content) {
        ++total_posts;
        labels.insert(label);
        ++label_post_count[label];

        set<string> words = unique_words(content);
        for (const string &word : words) {
            vocabulary.insert(word);
            ++word_post_count[word];
            ++label_word_post_count[label][word];
        }
    }

    int num_posts() const {
        return total_posts;
    }

    int vocab_size() const {
        return static_cast<int>(vocabulary.size());
    }

    double log_prior(const string &label) const {
        double numerator = static_cast<double>(label_post_count.at(label));
        double denominator = static_cast<double>(total_posts);
        return log(numerator / denominator);
    }

    double log_likelihood(const string &label, const string &word) const {
        if (word_seen_with_label(label, word)) {
            return log_likelihood_seen_with_label(label, word);
        }
        if (word_seen_globally(word)) {
            return log_likelihood_seen_globally(word);
        }
        return log_likelihood_unseen();
    }

    double score(const string &label, const string &content) const {
        double total = log_prior(label);
        set<string> words = unique_words(content);

        for (const string &word : words) {
            total += log_likelihood(label, word);
        }

        return total;
    }

    pair<string, double> predict(const string &content) const {
        auto it = labels.begin();
        string best_label = *it;
        double best_score = score(best_label, content);
        ++it;

        for (; it != labels.end(); ++it) {
            update_best_prediction(*it, content, best_label, best_score);
        }
        return {best_label, best_score};
    }

    void print_classes(ostream &out) const {
        out << "classes:" << endl;
        for (const string &label : labels) {
            print_class_line(out, label);
        }
    }

    void print_classifier_parameters(ostream &out) const {
        out << "classifier parameters:" << endl;
        for (const string &label : labels) {
            print_label_parameters(out, label);
        }
    }

private:
    int total_posts = 0;
    set<string> labels;
    set<string> vocabulary;
    map<string, int> label_post_count;
    map<string, int> word_post_count;
    map<string, map<string, int>> label_word_post_count;

    bool word_seen_with_label(const string &label, const string &word) const {
        auto label_it = label_word_post_count.find(label);
        if (label_it == label_word_post_count.end()) {
            return false;
        }
        auto word_it = label_it->second.find(word);
        return word_it != label_it->second.end() && word_it->second > 0;
    }

    bool word_seen_globally(const string &word) const {
        auto it = word_post_count.find(word);
        return it != word_post_count.end() && it->second > 0;
    }

    double log_likelihood_seen_with_label(const string &label,
                                          const string &word) const {
        double numerator =
            static_cast<double>(label_word_post_count.at(label).at(word));
        double denominator = static_cast<double>(label_post_count.at(label));
        return log(numerator / denominator);
    }

    double log_likelihood_seen_globally(const string &word) const {
        double numerator = static_cast<double>(word_post_count.at(word));
        double denominator = static_cast<double>(total_posts);
        return log(numerator / denominator);
    }

    double log_likelihood_unseen() const {
        return log(1.0 / static_cast<double>(total_posts));
    }

    void update_best_prediction(const string &candidate_label,
                                const string &content,
                                string &best_label,
                                double &best_score) const {
        double candidate_score = score(candidate_label, content);
        if (candidate_score > best_score) {
            best_score = candidate_score;
            best_label = candidate_label;
        }
    }

    void print_class_line(ostream &out, const string &label) const {
        out << "  " << label
            << ", " << label_post_count.at(label)
            << " examples, log-prior = " << log_prior(label)
            << endl;
    }

    void print_label_parameters(ostream &out, const string &label) const {
        const map<string, int> &word_counts = label_word_post_count.at(label);
        for (const auto &entry : word_counts) {
            print_parameter_line(out, label, entry.first, entry.second);
        }
    }

    void print_parameter_line(ostream &out,
                              const string &label,
                              const string &word,
                              int count) const {
        out << "  " << label << ":" << word
            << ", count = " << count
            << ", log-likelihood = " << log_likelihood(label, word)
            << endl;
    }
};

void print_training_row(const string &label, const string &content) {
    cout << "  label = " << label
         << ", content = " << content << endl;
}

void train_from_file(csvstream &train_data,
                     Classifier &classifier,
                     bool print_rows) {
    map<string, string> row;

    if (print_rows) {
        cout << "training data:" << endl;
    }

    while (train_data >> row) {
        string label = row["tag"];
        string content = row["content"];

        if (print_rows) {
            print_training_row(label, content);
        }

        classifier.train(label, content);
    }
}

void print_train_only_summary(const Classifier &classifier) {
    cout << "trained on " << classifier.num_posts() << " examples" << endl;
    cout << "vocabulary size = " << classifier.vocab_size() << endl;
    cout << endl;

    classifier.print_classes(cout);
    

    classifier.print_classifier_parameters(cout);
    cout << endl;
}

void print_test_result(const string &correct_label,
                       const string &predicted_label,
                       double score,
                       const string &content) {
    cout << "  correct = " << correct_label
         << ", predicted = " << predicted_label
         << ", log-probability score = " << score
         << endl;
    cout << "  content = " << content << endl;
    cout << endl;
}

void run_test_data(csvstream &test_data, const Classifier &classifier) {
    map<string, string> row;
    int correct_count = 0;
    int total_test_posts = 0;

    cout << "test data:" << endl;

    while (test_data >> row) {
        string correct_label = row["tag"];
        string content = row["content"];

        pair<string, double> result = classifier.predict(content);
        string predicted_label = result.first;
        double score = result.second;

        print_test_result(correct_label, predicted_label, score, content);

        if (predicted_label == correct_label) {
            ++correct_count;
        }
        ++total_test_posts;
    }

    cout << "performance: " << correct_count
         << " / " << total_test_posts
         << " posts predicted correctly" << endl;
}

int main(int argc, char *argv[]) {
    cout.precision(3);

    if (argc != 2 && argc != 3) {
        cout << "Usage: classifier.exe TRAIN_FILE [TEST_FILE]" << endl;
        return 1;
    }

    string train_filename = argv[1];
    bool train_only = (argc == 2);

    try {
        csvstream train_data(train_filename);
        Classifier classifier;

        train_from_file(train_data, classifier, train_only);

        if (train_only) {
            print_train_only_summary(classifier);
        } else {
            cout << "trained on " << classifier.num_posts() << " examples"
                 << endl;
            cout << endl;

            csvstream test_data(argv[2]);
            run_test_data(test_data, classifier);
        }
    } catch (const csvstream_exception &e) {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}