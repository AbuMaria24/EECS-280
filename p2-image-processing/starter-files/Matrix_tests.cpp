#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.
// ------------------------------------------------------------
// Tests that Matrix_init correctly sets width and height
TEST(test_dimensions) {
  Matrix mat;
  Matrix_init(&mat, 4, 3);

  ASSERT_EQUAL(Matrix_width(&mat), 4);
  ASSERT_EQUAL(Matrix_height(&mat), 3);
}

TEST(test_at_single_element) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);

  *Matrix_at(&mat, 1, 0) = 99;
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 0), 99);
}

TEST(test_fill_border) {
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  Matrix_fill(&mat, 0);

  Matrix_fill_border(&mat, 5);

  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 1), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 2), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 2), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 0), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 1), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 2), 5);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), 0);
}

TEST(test_max) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  *Matrix_at(&mat, 0, 0) = -1;
  *Matrix_at(&mat, 0, 1) = 4;
  *Matrix_at(&mat, 1, 0) = 2;
  *Matrix_at(&mat, 1, 1) = 3;
  ASSERT_EQUAL(Matrix_max(&mat), 4);
}

TEST(test_min_value_in_row) {
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 9;
  *Matrix_at(&mat, 0, 1) = 3;
  *Matrix_at(&mat, 0, 2) = 7;
  *Matrix_at(&mat, 0, 3) = 1;
  *Matrix_at(&mat, 0, 4) = 5;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 1, 4), 1);
}

TEST(test_column_of_min_value_in_row) {
  Matrix mat;
  Matrix_init(&mat, 4, 1);
  *Matrix_at(&mat, 0, 0) = 5;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 0, 2) = 2;
  *Matrix_at(&mat, 0, 3) = 9;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 4), 1);
}

TEST(test_matrix_print) {
  Matrix mat;
  Matrix_init(&mat, 1, 1);
  *Matrix_at(&mat, 0, 0) = 42;

  ostringstream expected;
  expected << "1 1\n"
           << "42 \n";

  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(actual.str(), expected.str());
}

TEST(test_column_of_min_negative_values) {
  Matrix mat;
  Matrix_init(&mat, 4, 1);
  *Matrix_at(&mat, 0, 0) = 3;
  *Matrix_at(&mat, 0, 1) = -5;
  *Matrix_at(&mat, 0, 2) = 2;
  *Matrix_at(&mat, 0, 3) = 7;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 4), 1);
}

TEST(test_column_of_min_single_column_range) {
  Matrix mat;
  Matrix_init(&mat, 3, 1);
  *Matrix_at(&mat, 0, 0) = 10;
  *Matrix_at(&mat, 0, 1) = 5;
  *Matrix_at(&mat, 0, 2) = 7;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 1, 2), 1);
}


TEST_MAIN() // Do NOT put a semicolon here
