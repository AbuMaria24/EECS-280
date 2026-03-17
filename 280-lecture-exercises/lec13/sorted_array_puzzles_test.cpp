#include "unit_test_framework.hpp"
#include <vector>
using namespace std;

int *find(int value, int *arr, int size);
TEST(test00_find) {
    int arr1[7] = {3, 6, 8, 10, 12, 14, 90};
    for (int i = 0; i < 7; i++) {
        ASSERT_EQUAL(find(arr1[i], arr1, 7), &arr1[i]);
    }
    ASSERT_EQUAL(find(-1, arr1, 7), nullptr);
    ASSERT_EQUAL(find(1000, arr1, 7), nullptr);
    ASSERT_EQUAL(find(7, arr1, 7), nullptr);
    ASSERT_EQUAL(find(13, arr1, 7), nullptr);

    int arr2[6] = {3, 6, 8, 10, 12, 14 };
    for (int i = 0; i < 6; i++) {
        ASSERT_EQUAL(find(arr2[i], arr2, 6), &arr2[i]);
    }
    ASSERT_EQUAL(find(-1, arr2, 6), nullptr);
    ASSERT_EQUAL(find(1000, arr2, 6), nullptr);
    ASSERT_EQUAL(find(7, arr2, 6), nullptr);
    ASSERT_EQUAL(find(13, arr2, 6), nullptr);
}

int count_below(int value, int *arr, int size);
TEST(test01_count_below) {
    int arr1[7] = {3, 6, 8, 10, 12, 14, 90};
    ASSERT_EQUAL(count_below(3, arr1, 7), 0);
    ASSERT_EQUAL(count_below(6, arr1, 7), 1);
    ASSERT_EQUAL(count_below(90, arr1, 7), 6);
}

int count_above(int value, int *arr, int size);
TEST(test02_count_above) {
    int arr1[7] = {3, 6, 8, 10, 12, 14, 90};
    ASSERT_EQUAL(count_above(3, arr1, 7), 6);
    ASSERT_EQUAL(count_above(6, arr1, 7), 5);
    ASSERT_EQUAL(count_above(90, arr1, 7), 0);
}

void merge(int *arr1, int arr1_size, int *arr2, int arr2_size, int *out, int &out_size);
TEST(test03_merge) {
    int arr1[3] = {1, 4, 5};
    int arr2[3] = {2, 7, 9};
    int arr3[6];
    int arr3_size;
    merge(arr1, 3, arr2, 3, arr3, arr3_size);
    ASSERT_SEQUENCE_EQUAL(
        vector<int>(arr3, arr3 + arr3_size),
        vector<int>({1, 2, 4, 5, 7, 9}));
}

TEST(test04_merge) {
    int arr1[1] = {10};
    int arr2[3] = {2, 7, 9};
    int arr3[4];
    int arr3_size;
    merge(arr1, 1, arr2, 3, arr3, arr3_size);
    ASSERT_SEQUENCE_EQUAL(
        vector<int>(arr3, arr3 + arr3_size),
        vector<int>({2, 7, 9, 10}));
}

TEST(test05_merge) {
    int arr1[3] = {0, 0, 0};
    int arr2[3] = {2, 7, 9};
    int arr3[6];
    int arr3_size;
    merge(arr1, 3, arr2, 3, arr3, arr3_size);
    ASSERT_SEQUENCE_EQUAL(
        vector<int>(arr3, arr3 + arr3_size),
        vector<int>({0, 0, 0, 2, 7, 9}));
}

TEST(test06_merge) {
    int arr1[3] = {2, 7, 9};
    int arr2[1] = {10};
    int arr3[4];
    int arr3_size;
    merge(arr1, 3, arr2, 1, arr3, arr3_size);
    ASSERT_SEQUENCE_EQUAL(
        vector<int>(arr3, arr3 + arr3_size),
        vector<int>({2, 7, 9, 10}));
}

TEST_MAIN()