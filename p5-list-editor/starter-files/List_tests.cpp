#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

TEST(test_default_constructor) {
    List<int> list;
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_push_front_single) {
    List<int> list;
    list.push_front(10);

    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(list.front(), 10);
    ASSERT_EQUAL(list.back(), 10);
}

TEST(test_push_back_single) {
    List<int> list;
    list.push_back(20);

    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(list.front(), 20);
    ASSERT_EQUAL(list.back(), 20);
}

TEST(test_push_front_multiple) {
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(list.front(), 3);
    ASSERT_EQUAL(list.back(), 1);
}

TEST(test_push_back_multiple) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 3);
}

TEST(test_pop_front) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();

    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(list.front(), 2);
    ASSERT_EQUAL(list.back(), 3);
}

TEST(test_pop_back) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_back();

    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 2);
}

TEST(test_pop_to_empty_from_front) {
    List<int> list;
    list.push_back(7);

    list.pop_front();

    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_pop_to_empty_from_back) {
    List<int> list;
    list.push_back(7);

    list.pop_back();

    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_clear) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.clear();

    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
    ASSERT_TRUE(list.begin() == list.end());
}

TEST(test_iterator_forward_traversal) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    List<int>::Iterator it = list.begin();
    ASSERT_EQUAL(*it, 10);
    ++it;
    ASSERT_EQUAL(*it, 20);
    ++it;
    ASSERT_EQUAL(*it, 30);
    ++it;
    ASSERT_TRUE(it == list.end());
}

TEST(test_iterator_backward_from_end) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    List<int>::Iterator it = list.end();
    --it;
    ASSERT_EQUAL(*it, 30);
    --it;
    ASSERT_EQUAL(*it, 20);
    --it;
    ASSERT_EQUAL(*it, 10);
}

TEST(test_iterator_postfix_increment) {
    List<int> list;
    list.push_back(5);
    list.push_back(6);

    List<int>::Iterator it = list.begin();
    List<int>::Iterator old = it++;

    ASSERT_EQUAL(*old, 5);
    ASSERT_EQUAL(*it, 6);
}

TEST(test_iterator_equality_same_position) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    List<int>::Iterator it1 = list.begin();
    List<int>::Iterator it2 = list.begin();

    ASSERT_TRUE(it1 == it2);
    ++it2;
    ASSERT_TRUE(it1 != it2);
}

TEST(test_copy_constructor_independent) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);

    List<int> copy(original);
    copy.pop_back();
    copy.push_back(99);

    ASSERT_EQUAL(original.size(), 2);
    ASSERT_EQUAL(original.front(), 1);
    ASSERT_EQUAL(original.back(), 2);

    ASSERT_EQUAL(copy.size(), 2);
    ASSERT_EQUAL(copy.front(), 1);
    ASSERT_EQUAL(copy.back(), 99);
}

TEST(test_assignment_operator_independent) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);

    List<int> b;
    b.push_back(9);

    b = a;
    b.pop_front();
    b.push_back(7);

    ASSERT_EQUAL(a.size(), 2);
    ASSERT_EQUAL(a.front(), 1);
    ASSERT_EQUAL(a.back(), 2);

    ASSERT_EQUAL(b.size(), 2);
    ASSERT_EQUAL(b.front(), 2);
    ASSERT_EQUAL(b.back(), 7);
}

TEST(test_assignment_self) {
    List<int> list;
    list.push_back(4);
    list.push_back(5);

    List<int> &ref = list;
    list = ref;

    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(list.front(), 4);
    ASSERT_EQUAL(list.back(), 5);
}

TEST(test_insert_at_beginning) {
    List<int> list;
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator it = list.begin();
    List<int>::Iterator inserted = list.insert(it, 1);

    ASSERT_EQUAL(*inserted, 1);
    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 3);
}

TEST(test_insert_at_end) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    List<int>::Iterator inserted = list.insert(list.end(), 3);

    ASSERT_EQUAL(*inserted, 3);
    ASSERT_EQUAL(list.size(), 3);
    ASSERT_EQUAL(list.back(), 3);
}

TEST(test_insert_in_middle) {
    List<int> list;
    list.push_back(1);
    list.push_back(3);

    List<int>::Iterator it = list.begin();
    ++it;
    list.insert(it, 2);

    List<int>::Iterator check = list.begin();
    ASSERT_EQUAL(*check, 1);
    ++check;
    ASSERT_EQUAL(*check, 2);
    ++check;
    ASSERT_EQUAL(*check, 3);
}

TEST(test_erase_beginning) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator next = list.erase(list.begin());

    ASSERT_EQUAL(*next, 2);
    ASSERT_EQUAL(list.size(), 2);
    ASSERT_EQUAL(list.front(), 2);
}

TEST(test_erase_middle) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator it = list.begin();
    ++it;

    List<int>::Iterator next = list.erase(it);

    ASSERT_EQUAL(*next, 3);
    ASSERT_EQUAL(list.size(), 2);

    List<int>::Iterator check = list.begin();
    ASSERT_EQUAL(*check, 1);
    ++check;
    ASSERT_EQUAL(*check, 3);
}

TEST(test_erase_last) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    List<int>::Iterator it = list.begin();
    ++it;

    List<int>::Iterator next = list.erase(it);

    ASSERT_TRUE(next == list.end());
    ASSERT_EQUAL(list.size(), 1);
    ASSERT_EQUAL(list.back(), 1);
}

TEST_MAIN()