#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
#include <string>

using namespace std;

TEST(test_empty_tree) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0u);
    ASSERT_EQUAL(tree.height(), 0u);
    ASSERT_TRUE(tree.begin() == tree.end());
}

TEST(test_single_insert) {
    BinarySearchTree<int> tree;
    tree.insert(5);

    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 1u);
    ASSERT_EQUAL(tree.height(), 1u);
    ASSERT_EQUAL(*tree.begin(), 5);
}

TEST(test_inorder_iteration) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    auto it = tree.begin();
    ASSERT_EQUAL(*it, 3);
    ++it;
    ASSERT_EQUAL(*it, 5);
    ++it;
    ASSERT_EQUAL(*it, 7);
    ++it;
    ASSERT_TRUE(it == tree.end());
}

TEST(test_find_present) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(8);

    auto it = tree.find(2);
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 2);
}

TEST(test_find_absent) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(8);

    ASSERT_TRUE(tree.find(6) == tree.end());
}

TEST(test_min_and_max) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(10);

    ASSERT_EQUAL(*tree.min_element(), 1);
    ASSERT_EQUAL(*tree.max_element(), 10);
}

TEST(test_min_greater_than_found) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(12);
    tree.insert(20);

    auto it = tree.min_greater_than(10);
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 12);
}

TEST(test_min_greater_than_not_found) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    ASSERT_TRUE(tree.min_greater_than(15) == tree.end());
}

TEST(test_traverse_inorder) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    ostringstream oss;
    tree.traverse_inorder(oss);
    ASSERT_EQUAL(oss.str(), "1 2 3 4 5 6 7 ");
}

TEST(test_traverse_preorder) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);

    ostringstream oss;
    tree.traverse_preorder(oss);
    ASSERT_EQUAL(oss.str(), "4 2 1 3 6 ");
}

TEST(test_copy_constructor) {
    BinarySearchTree<int> tree1;
    tree1.insert(4);
    tree1.insert(2);
    tree1.insert(6);

    BinarySearchTree<int> tree2(tree1);

    ASSERT_EQUAL(tree2.size(), 3u);
    ASSERT_TRUE(tree2.find(4) != tree2.end());
    ASSERT_TRUE(tree2.find(2) != tree2.end());
    ASSERT_TRUE(tree2.find(6) != tree2.end());
}

TEST(test_copy_constructor_empty_tree) {
    BinarySearchTree<int> tree1;
    BinarySearchTree<int> tree2(tree1);

    ASSERT_TRUE(tree2.empty());
    ASSERT_EQUAL(tree2.size(), 0u);
    ASSERT_EQUAL(tree2.height(), 0u);
    ASSERT_TRUE(tree2.begin() == tree2.end());
}

TEST(test_copy_constructor_preserves_structure) {
    BinarySearchTree<int> tree1;
    tree1.insert(4);
    tree1.insert(2);
    tree1.insert(6);
    tree1.insert(1);
    tree1.insert(3);

    BinarySearchTree<int> tree2(tree1);

    ASSERT_EQUAL(tree2.size(), tree1.size());
    ASSERT_EQUAL(tree2.height(), tree1.height());

    ostringstream out1;
    ostringstream out2;
    tree1.traverse_preorder(out1);
    tree2.traverse_preorder(out2);

    ASSERT_EQUAL(out1.str(), out2.str());
}

TEST(test_copy_constructor_independent_copy) {
    BinarySearchTree<int> tree1;
    tree1.insert(4);
    tree1.insert(2);
    tree1.insert(6);

    BinarySearchTree<int> tree2(tree1);

    *tree2.begin() = 5;

    ASSERT_FALSE(tree2.check_sorting_invariant());
    ASSERT_TRUE(tree1.check_sorting_invariant());

    ostringstream out1;
    tree1.traverse_inorder(out1);
    ASSERT_EQUAL(out1.str(), "2 4 6 ");
}

TEST(test_assignment_operator) {
    BinarySearchTree<int> tree1;
    tree1.insert(10);
    tree1.insert(5);
    tree1.insert(15);

    BinarySearchTree<int> tree2;
    tree2.insert(1);
    tree2 = tree1;

    ASSERT_EQUAL(tree2.size(), 3u);
    ASSERT_TRUE(tree2.find(10) != tree2.end());
    ASSERT_TRUE(tree2.find(5) != tree2.end());
    ASSERT_TRUE(tree2.find(15) != tree2.end());
}

TEST(test_check_sorting_invariant_valid) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);

    ASSERT_TRUE(tree.check_sorting_invariant());
}

TEST(test_check_sorting_invariant_broken) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(0);

    *tree.begin() = 2;

    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test_height_unbalanced) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);

    ASSERT_EQUAL(tree.height(), 4u);
}

TEST(test_copy_constructor_left_skewed) {
    BinarySearchTree<int> tree1;
    tree1.insert(4);
    tree1.insert(3);
    tree1.insert(2);
    tree1.insert(1);

    BinarySearchTree<int> tree2(tree1);

    ASSERT_EQUAL(tree2.size(), 4u);
    ASSERT_EQUAL(tree2.height(), 4u);

    ostringstream out;
    tree2.traverse_inorder(out);
    ASSERT_EQUAL(out.str(), "1 2 3 4 ");
}

TEST(test_copy_constructor_right_skewed) {
    BinarySearchTree<int> tree1;
    tree1.insert(1);
    tree1.insert(2);
    tree1.insert(3);
    tree1.insert(4);

    BinarySearchTree<int> tree2(tree1);

    ASSERT_EQUAL(tree2.size(), 4u);
    ASSERT_EQUAL(tree2.height(), 4u);

    ostringstream out;
    tree2.traverse_inorder(out);
    ASSERT_EQUAL(out.str(), "1 2 3 4 ");
}

TEST(test_copy_constructor_mixed_shape) {
    BinarySearchTree<int> tree1;
    tree1.insert(8);
    tree1.insert(3);
    tree1.insert(10);
    tree1.insert(1);
    tree1.insert(6);
    tree1.insert(14);
    tree1.insert(4);

    BinarySearchTree<int> tree2(tree1);

    ASSERT_EQUAL(tree2.size(), tree1.size());
    ASSERT_EQUAL(tree2.height(), tree1.height());

    ostringstream out1;
    ostringstream out2;
    tree1.traverse_preorder(out1);
    tree2.traverse_preorder(out2);
    ASSERT_EQUAL(out1.str(), out2.str());
}

TEST(test_copy_constructor_single_node) {
    BinarySearchTree<int> tree1;
    tree1.insert(42);

    BinarySearchTree<int> tree2(tree1);

    ASSERT_EQUAL(tree2.size(), 1u);
    ASSERT_EQUAL(tree2.height(), 1u);
    ASSERT_TRUE(tree2.find(42) != tree2.end());
}

TEST(test_min_element_empty_tree) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.min_element() == tree.end());
}

TEST(test_min_element_single_node) {
    BinarySearchTree<int> tree;
    tree.insert(42);

    auto it = tree.min_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 42);
}

TEST(test_min_element_left_skewed_tree) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);

    auto it = tree.min_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 1);
}

TEST(test_min_element_right_skewed_tree) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);

    auto it = tree.min_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 1);
}

TEST(test_min_element_mixed_shape_tree) {
    BinarySearchTree<int> tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);

    auto it = tree.min_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 1);
}

TEST(test_begin_matches_min_element) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(3);

    ASSERT_TRUE(tree.min_element() != tree.end());
    ASSERT_EQUAL(*tree.begin(), *tree.min_element());
}

TEST(test_max_element_empty_tree) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.max_element() == tree.end());
}

TEST(test_max_element_single_node) {
    BinarySearchTree<int> tree;
    tree.insert(42);

    auto it = tree.max_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 42);
}

TEST(test_max_element_right_skewed_tree) {
    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);

    auto it = tree.max_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 4);
}

TEST(test_max_element_left_skewed_tree) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);

    auto it = tree.max_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 4);
}

TEST(test_max_element_mixed_shape_tree) {
    BinarySearchTree<int> tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    tree.insert(4);

    auto it = tree.max_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 14);
}

TEST(test_max_element_matches_last_value) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(3);

    auto it = tree.max_element();
    ASSERT_TRUE(it != tree.end());
    ASSERT_EQUAL(*it, 8);
}
TEST_MAIN()