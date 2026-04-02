#include "unit_test_framework.hpp"
#include <vector>
#include "functor_algorithms.hpp"
using namespace std;

TEST(test00_multiple_10_matcher) {
    MultipleOfTenMatcher matcher;
    ASSERT_TRUE(matcher(20));
    ASSERT_FALSE(matcher(11));
}

TEST(test01_greater_matcher) {
    GreaterThanMatcher matcher(100);
    ASSERT_TRUE(matcher(105));
    ASSERT_FALSE(matcher(95));
}

class TestFunctor {
public:
    bool operator()(int val) {
        return val == 5;
    }
};
TEST(test02_count_matches) {
    vector<int> vs = {1, 5, 5, 9, 5, 1};
    TestFunctor ts;
    ASSERT_EQUAL(count_matches(vs.begin(), vs.end(), ts), 3);
}

TEST(test03_count_multiples_10) {
    vector<int> vs = {1, 50, 5, 90, 5, 0};
    ASSERT_EQUAL(count_multiples_10(vs.begin(), vs.end()), 3);
}

TEST(test04_count_greater_than) {
    vector<int> vs = {1, 50, 5, 90, 5, 10};
    ASSERT_EQUAL(count_greater_than(vs.begin(), vs.end(), 10), 2);
}

TEST_MAIN()