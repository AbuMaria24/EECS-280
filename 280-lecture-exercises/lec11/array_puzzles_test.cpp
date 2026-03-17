#include "unit_test_framework.hpp"
#include <vector>
using namespace std;

bool is_sorted(int *arr, int size);
TEST(test00_is_sorted) {
    int tv1[] = {1, 2, 3};
    ASSERT_TRUE(is_sorted(tv1, 3));

    int tv2[] = {2, 2, 3};
    ASSERT_TRUE(is_sorted(tv2, 3));

    int tv3[] = {2, 2, 2};
    ASSERT_TRUE(is_sorted(tv3, 3));

    int tv4[] = {2, 1, 2};
    ASSERT_FALSE(is_sorted(tv4, 3));

    int tv6[] = {2};
    ASSERT_TRUE(is_sorted(tv6, 1));
}

bool is_palindrome(int *arr, int size);
TEST(test01_is_palindrome) {
    int tv2[] = {2, 2};
    ASSERT_TRUE(is_palindrome(tv2, 2));

    int tv3[] = {4, 2, 2, 4};
    ASSERT_TRUE(is_palindrome(tv3, 4));

    int tv4[] = {4, 2, 2, 2};
    ASSERT_FALSE(is_palindrome(tv4, 4));
}

void partition(int value, int *in, int in_size, int *less_equal, int &less_equal_size_out, int *greater, int &greater_size_out);
TEST(test02_partition) {
    int in[] = {3, 5, 2, 4, 0, 10, 2};
    int less_equal[10];
    int greater[10];

    int less_equal_size;
    int greater_size;

    partition(-1, in, 7, less_equal, less_equal_size, greater, greater_size);
    ASSERT_EQUAL(less_equal_size, 0);
    ASSERT_EQUAL(greater_size, 7);
    ASSERT_SEQUENCE_EQUAL(vector<int>(less_equal, less_equal + less_equal_size), vector<int>());
    ASSERT_SEQUENCE_EQUAL(vector<int>(greater, greater + greater_size), vector<int>({3, 5, 2, 4, 0, 10, 2}));

    partition(5, in, 7, less_equal, less_equal_size, greater, greater_size);
    ASSERT_EQUAL(less_equal_size, 6);
    ASSERT_EQUAL(greater_size, 1);
    ASSERT_SEQUENCE_EQUAL(vector<int>(less_equal, less_equal + less_equal_size), vector<int>({3, 5, 2, 4, 0, 2}));
    ASSERT_SEQUENCE_EQUAL(vector<int>(greater, greater + greater_size), vector<int>({10}));

    partition(3, in, 7, less_equal, less_equal_size, greater, greater_size);
    ASSERT_EQUAL(less_equal_size, 4);
    ASSERT_EQUAL(greater_size, 3);
    ASSERT_SEQUENCE_EQUAL(vector<int>(less_equal, less_equal + less_equal_size), vector<int>({3, 2, 0, 2}));
    ASSERT_SEQUENCE_EQUAL(vector<int>(greater, greater + greater_size), vector<int>({5, 4, 10}));

    partition(11, in, 7, less_equal, less_equal_size, greater, greater_size);
    ASSERT_EQUAL(less_equal_size, 7);
    ASSERT_EQUAL(greater_size, 0);
    ASSERT_SEQUENCE_EQUAL(vector<int>(less_equal, less_equal + less_equal_size), vector<int>({3, 5, 2, 4, 0, 10, 2}));
    ASSERT_SEQUENCE_EQUAL(vector<int>(greater, greater + greater_size), vector<int>({}));
}

int longest_equal_sequence(int *arr, int size);
TEST(test03_longest_equal_seqeuence) {
    int tv1[] = {1, 2, 3};
    ASSERT_EQUAL(longest_equal_sequence(tv1, 3), 1);

    int tv2[] = {1, 2, 2};
    ASSERT_EQUAL(longest_equal_sequence(tv2, 3), 2);

    int tv3[] = {2, 2, 2};
    ASSERT_EQUAL(longest_equal_sequence(tv3, 3), 3);
}

bool is_subset(int *arr1, int arr1_size, int *arr2, int arr2_size);
TEST(test04_is_subset) {
    int haystack[] = {5, 2, 5, 1, -1, 3};

    int tv1[] = {5};
    ASSERT_TRUE(is_subset(haystack, 6, tv1, 1));

    int tv2[] = {-2};
    ASSERT_FALSE(is_subset(haystack, 6, tv2, 2));

    int tv3[] = {3, 5, 2, -1};
    ASSERT_TRUE(is_subset(haystack, 6, tv3, 4));

    int tv4[] = {3, 5, 2, -1, -5};
    ASSERT_FALSE(is_subset(haystack, 6, tv4, 5));
}

int most_frequent(int *arr, int size);
TEST(test05_most_frequent) {
    int tv1[] = {1, 2, 1, 2, 9};
    ASSERT_EQUAL(most_frequent(tv1, 5), 1);

    int tv2[] = {0, 2, 3, 3, 8};
    ASSERT_EQUAL(most_frequent(tv2, 5), 3);

    int tv3[] = {3};
    ASSERT_EQUAL(most_frequent(tv3, 1), 3);
}

TEST_MAIN()