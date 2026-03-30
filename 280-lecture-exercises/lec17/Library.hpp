#pragma once
#include "Book.hpp"
#include <vector>

class Library {
public:
    Library();
    ~Library();
    Library(const Library &other);
    Library &operator=(const Library &other);

    // EFFECTS: Reads books from the stream in into library.
    // Each title is exactly one word.
    // Hint: you can get a c-string from a std::string
    //   using .c_str()
    void read(std::istream &in);

    size_t num_books() const { return books.size(); }

    // REQUIRES: book_idx < num_books()
    // EFFECTS: returns the title of the book at the given index
    char *get_title(int book_idx) const;

private:
    std::vector<Book *> books;
};