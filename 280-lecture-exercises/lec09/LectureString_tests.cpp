#include "LectureString.hpp"
#include "unit_test_framework.hpp"
using namespace std;

TEST(test00_length) {
    LectureString ls1;
    ASSERT_EQUAL(ls1.length(), 0);

    LectureString ls2("hello");
    ASSERT_EQUAL(ls2.length(), 5);
}

TEST(test01_at) {
    LectureString ls("hello");
    ASSERT_EQUAL(ls.at(0), 'h');
    ASSERT_EQUAL(ls.at(4), 'o');
}

TEST(test02_equal_at_position) {
    LectureString ls("hello world");
    ASSERT_TRUE(ls.equalAtPosition(
        string("hello world"), 0)
    );
    ASSERT_TRUE(ls.equalAtPosition(
        string("ello"), 1)
    );
    ASSERT_TRUE(ls.equalAtPosition(
        string("rld"), 8)
    );
}

TEST(test03_operator_equal) {
    LectureString ls1("hello world");
    LectureString ls2("hello worl");
    LectureString ls3("hello werld");


    ASSERT_TRUE(ls1 == ls1);
    ASSERT_FALSE(ls1 == ls2);
    ASSERT_FALSE(ls1 == ls3);
}

TEST(test04_append_char) {
    LectureString ls("hello");
    ls.append('o');
    ASSERT_TRUE(ls == LectureString("helloo"));
}

TEST(test05_append_ls) {
    LectureString ls1("hello ");
    LectureString ls2("world");
    ls1.append(ls2);
    ASSERT_TRUE(ls1 == LectureString("hello world"));
}

TEST(test06_replace_char) {
    LectureString ls("hello");
    ls.replace('l', 'w');
    ASSERT_TRUE(ls == LectureString("hewwo"));
}

TEST(test07_replace_ls) {
    LectureString ls("hello");
    ls.replace('l', LectureString("abc"));
    ASSERT_TRUE(ls == LectureString("heabcabco"));

    ls.replace('h', LectureString(""));
    ASSERT_TRUE(ls == LectureString("eabcabco"));
}

TEST_MAIN()