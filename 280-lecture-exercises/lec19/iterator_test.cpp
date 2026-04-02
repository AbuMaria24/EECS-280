#include "unit_test_framework.hpp"
#include <vector>
#include "iterator_algorithms.hpp"
using namespace std;

TEST(test00_contains) {
    vector<int> v = {1, 2, 9, 6, 2, 5};
    ASSERT_TRUE(lecture_contains(v.begin(), v.end(), 1));
    ASSERT_TRUE(lecture_contains(v.begin(), v.end(), 5));
    ASSERT_TRUE(lecture_contains(v.begin(), v.end(), 2));
    ASSERT_FALSE(lecture_contains(v.begin(), v.end(), 10));
}

TEST(test01_find) {
    vector<int> v = {1, 2, 9, 6, 2, 5};
    ASSERT_EQUAL(lecture_find(v.begin(), v.end(), 1), v.begin());
    ASSERT_EQUAL(lecture_find(v.begin(), v.end(), 2), v.begin() + 1);
    ASSERT_EQUAL(lecture_find(v.begin(), v.end(), 5), v.end() - 1);
    ASSERT_EQUAL(lecture_find(v.begin(), v.end(), 100), v.end());
}

TEST(test02_equal) {
    vector<int> v1 = {5, 6, 7};
    ASSERT_TRUE(lecture_equal(v1.begin(), v1.end(), v1.begin(), v1.end()));

    vector<int> v2 = {5, 6, 7, 8};
    ASSERT_FALSE(lecture_equal(v1.begin(), v1.end(), v2.begin(), v2.end()));

    vector<int> v3 = {5, 8, 7};
    ASSERT_FALSE(lecture_equal(v1.begin(), v1.end(), v3.begin(), v3.end()));
}

TEST_MAIN()