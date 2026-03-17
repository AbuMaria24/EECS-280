#pragma once
#include "LectureString.hpp"

class Filter {
public:
    virtual ~Filter() {}; // ignore this for now
    virtual bool matches(const LectureString &ls) = 0;
};

// Matches when the entire string is exactly the same
//  as the string passed to the constructor.
class ExactMatchFilter : public Filter {
public:
    ExactMatchFilter(const LectureString &match);
    bool matches(const LectureString &ls) override;
private:
    const LectureString match;
};

// Matches when the string passed to the constructor
//  is present anywhere in the string passed in.
class SubstringFilter : public Filter {
public:
    SubstringFilter(const LectureString &match);
    bool matches(const LectureString &ls) override;
private:
    const LectureString match;
};

// Matches when the string follows the pattern passed to the
//  constructor.
// The pattern can contain special characters which do the following:
//    #    Matches a number 0-9
//    .    Matches any character
//    <    Matches when the character is the same as the previous character
// The entire pattern needs to match, without characters left over.
// You can assume the first character of pattern is not <
//
// Example
//   The pattern .<b# matches:  aab2 33b9
//   It does not match:  aaa3 aab22
// Example 2
//   The pattern #<<.< matches: 222aa 99999
//   It does not match:  aaa22 a222aa
class PatternFilter : public Filter {
public:
    PatternFilter(const LectureString &pattern);
    bool matches(const LectureString &ls) override;
private:
    const LectureString pattern;
};
