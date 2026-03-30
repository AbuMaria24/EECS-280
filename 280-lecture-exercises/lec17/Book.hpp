#pragma once
#include <string>
#include <vector>

class Book {
public:
    // EFFECTS: creates a book with the given title
    Book(const char *title_in);
    ~Book();
    Book(const Book &other);
    Book &operator=(const Book &other);

    // EFFECTS: returns the title of the book
    char *get_title() const;

private:
    char *title;
};
