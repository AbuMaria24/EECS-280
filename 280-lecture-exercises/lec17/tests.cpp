#include "unit_test_framework.hpp"
#include "Book.hpp"
#include "Library.hpp"
#include <cstring>
using namespace std;

TEST(test00_book_ctor_dtor) {
    char title[] = "The_Games";
    Book b(title);
    // the book needs to create its own copy
    //  of the title
    ASSERT_NOT_EQUAL(title, b.get_title());
    ASSERT_EQUAL(strcmp(title, b.get_title()), 0);
}

TEST(test01_book_copy_ctor) {
    char title[] = "Countdown";
    Book b(title);
    Book c(b);

    ASSERT_NOT_EQUAL(b.get_title(), c.get_title());
    ASSERT_EQUAL(strcmp(b.get_title(), c.get_title()), 0);
}

TEST(test02_book_assignment) {
    char title[] = "Countdown";
    Book b(title);

    char title2[] = "Cross_The_Line";
    Book c(title2);
    c = b;

    ASSERT_NOT_EQUAL(b.get_title(), c.get_title());
    ASSERT_EQUAL(strcmp(b.get_title(), c.get_title()), 0);
}

TEST(test03_library_ctor_dtor) {
    Library l;
}

TEST(test04_library_read) {
    Library l;
    stringstream ss("Cross_Justice Invisible");
    l.read(ss);
    ASSERT_EQUAL(l.num_books(), 2);
    ASSERT_EQUAL(strcmp(l.get_title(0), "Cross_Justice"), 0);
    ASSERT_EQUAL(strcmp(l.get_title(1), "Invisible"), 0);
}

TEST(test05_library_copy_ctor) {
    Library l;
    stringstream ss("Cross_Justice Invisible");
    l.read(ss);
    Library m(l);

    ASSERT_NOT_EQUAL(l.get_title(0), m.get_title(0));
    ASSERT_EQUAL(m.num_books(), 2);
    ASSERT_EQUAL(strcmp(m.get_title(0), "Cross_Justice"), 0);
    ASSERT_EQUAL(strcmp(m.get_title(1), "Invisible"), 0);
}

TEST(test06_library_assignment) {
    Library l;
    stringstream ss("Cross_Justice Invisible");
    l.read(ss);
    
    Library m;
    stringstream ss2("Bullseye");
    m.read(ss);
    m = l;

    ASSERT_EQUAL(m.num_books(), 2);
    ASSERT_EQUAL(strcmp(m.get_title(0), "Cross_Justice"), 0);
    ASSERT_EQUAL(strcmp(m.get_title(1), "Invisible"), 0);
}

TEST_MAIN()