#pragma once

#include <iostream>
#include <vector>

class LectureString {
public:
    // EFFECTS: initialize a LectureString to be empty
    LectureString();
    // EFFECTS: initializes a LectureString equal to the given string
    LectureString(const std::string &in);

    // EFFECTS: returns the length of the string
    int length() const;
    // REQUIRES: idx < this->length()
    // EFFECTS: returns the character at index idx
    char at(int idx) const;

    // REQUIRES: other.length() + start_position <= length()
    // EFFECTS: returns true if and only if other is present in *this
    //  at start_position
    // See LectureString_tests.cpp for examples
    bool equalAtPosition(const LectureString &other, int start_position) const;

    // EFFECTS: appends the given character to *this
    void append(char c);
    // EFFECTS: appends the given string to *this
    void append(const LectureString &to_append);

    // EFFECTS: replaces every occurrence of the character find with replacement
    void replace(char find, char replacement);
    // EFFECTS: replaces every occurrence of the character find with replacement
    void replace(char find, const LectureString &replacement);

private:
    std::vector<char> data;
};

// Returns true if the strings are the same length
//  and contain the same characters.
// Hint: you can use equalAtPosition
bool operator==(const LectureString &lhs, const LectureString &rhs);