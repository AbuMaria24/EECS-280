#include "unit_test_framework.hpp"
#include "ForwardList.hpp"
#include <vector>
using namespace std;

TEST(test00_baseline) {
    ForwardList<int> fl;
    fl.push_front(3);
    fl.push_front(2);
    fl.push_front(1);

    ASSERT_FALSE(fl.empty());
    ASSERT_SEQUENCE_EQUAL(fl, vector<int>({1, 2, 3}));
    ASSERT_EQUAL(fl.size(), 3);
}

TEST(test01_contains) {
    ForwardList<int> fl;
    fl.push_front(3);
    fl.push_front(2);
    fl.push_front(1);

    ASSERT_FALSE(fl.contains(5));
    ASSERT_TRUE(fl.contains(1));
    ASSERT_TRUE(fl.contains(3));
}

TEST(test02_push_back) {
    ForwardList<int> fl;
    fl.push_back(3);
    fl.push_back(2);
    fl.push_back(1);

    ASSERT_SEQUENCE_EQUAL(fl, vector<int>({3, 2, 1}));
}

TEST(test03_pop_back) {
    ForwardList<int> fl;
    fl.push_back(3);
    fl.push_back(2);
    fl.push_back(1);

    fl.pop_back();
    ASSERT_SEQUENCE_EQUAL(fl, vector<int>({3, 2}));
    fl.pop_back();
    ASSERT_SEQUENCE_EQUAL(fl, vector<int>({3}));
    fl.pop_back();
    ASSERT_TRUE(fl.empty());
}

TEST(test04_prepend_range) {
    ForwardList<int> fl;
    fl.push_front(3);
    vector<int> v1 = {1, 2};
    fl.prepend_range(v1.begin(), v1.end());

    ASSERT_SEQUENCE_EQUAL(fl, vector<int>({1, 2, 3}));

    fl.prepend_range(v1.begin(), v1.begin());
    ASSERT_SEQUENCE_EQUAL(fl, vector<int>({1, 2, 3}));
}

TEST_MAIN()