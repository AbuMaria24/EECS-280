#include "Filter.hpp"
#include "unit_test_framework.hpp"
using namespace std;

TEST(test00_exact_match) {
    ExactMatchFilter em1(LectureString(""));
    ASSERT_TRUE(em1.matches(LectureString("")));

    ExactMatchFilter em2(LectureString("entire string"));
    ASSERT_TRUE(em2.matches(LectureString("entire string")));
    ASSERT_FALSE(em2.matches(LectureString("entire string 1")));
    ASSERT_FALSE(em2.matches(LectureString("entire strin")));
    ASSERT_FALSE(em2.matches(LectureString("eentire string")));
}

TEST(test01_substring) {
    SubstringFilter ss1(LectureString(""));
    ASSERT_TRUE(ss1.matches(LectureString("")));

    SubstringFilter ss2(LectureString("abc"));
    ASSERT_TRUE(ss2.matches(LectureString("abc")));
    ASSERT_TRUE(ss2.matches(LectureString("aabc")));
    ASSERT_TRUE(ss2.matches(LectureString("abcab")));
    ASSERT_FALSE(ss2.matches(LectureString("aab bc")));
}

TEST(test02_pattern) {
    PatternFilter pf1(LectureString(""));
    ASSERT_TRUE(pf1.matches(LectureString("")));

    PatternFilter pf2(LectureString(".."));
    ASSERT_TRUE(pf2.matches(LectureString("ab")));
    ASSERT_FALSE(pf2.matches(LectureString("abc")));

    PatternFilter pf3(LectureString(".#"));
    ASSERT_TRUE(pf3.matches(LectureString("a0")));
    ASSERT_TRUE(pf3.matches(LectureString("b9")));
    ASSERT_FALSE(pf3.matches(LectureString("9b")));
    ASSERT_FALSE(pf3.matches(LectureString("a03")));

    PatternFilter pf4(LectureString(".<"));
    ASSERT_TRUE(pf4.matches(LectureString("aa")));
    ASSERT_TRUE(pf4.matches(LectureString("99")));
    ASSERT_FALSE(pf4.matches(LectureString("9b")));

    PatternFilter pf5(LectureString(".<<"));
    ASSERT_TRUE(pf5.matches(LectureString("aaa")));
    ASSERT_TRUE(pf5.matches(LectureString("999")));
    ASSERT_FALSE(pf5.matches(LectureString("9bb")));

    PatternFilter pf6(LectureString(".<b#"));
    ASSERT_TRUE(pf6.matches(LectureString("aab2")));
    ASSERT_TRUE(pf6.matches(LectureString("33b9")));
    ASSERT_FALSE(pf6.matches(LectureString("aaa3")));
    ASSERT_FALSE(pf6.matches(LectureString("aab22")));

    PatternFilter pf7(LectureString("#<<.<"));
    ASSERT_TRUE(pf7.matches(LectureString("222aa")));
    ASSERT_TRUE(pf7.matches(LectureString("99999")));
    ASSERT_FALSE(pf7.matches(LectureString("aaa22")));
    ASSERT_FALSE(pf7.matches(LectureString("a222aa")));
}

TEST_MAIN()