#include "unit_test_framework.hpp"
#include "Matrix.hpp"
#include <sstream>
using namespace std;

TEST(test00_matrix_load) {
    stringstream ss("2 3 2 6 4 1 9 7");
    Matrix m = Matrix_load(ss);

    ASSERT_EQUAL(Matrix_height(&m), 2);
    ASSERT_EQUAL(Matrix_width(&m), 3);
    ASSERT_EQUAL(*Matrix_at(&m, 1, 1), 9);
}

TEST(test01_matrix_save) {
    stringstream ss("2 3 2 6 4 1 9 7");
    Matrix m = Matrix_load(ss);

    stringstream out;
    Matrix_save(&m, out);

    // Note the trailing space
    ASSERT_EQUAL(out.str(), "2 3 2 6 4 1 9 7 ")
}

TEST(test02_matrix_dot_product) {
    stringstream ss1("2 3 2 6 4 1 9 7");
    stringstream ss2("3 2 3 2 4 10 11 8");

    Matrix m1 = Matrix_load(ss1);
    Matrix m2 = Matrix_load(ss2);

    ASSERT_EQUAL(Matrix_dot_product(&m1, 1, &m2, 1), 148)
}

TEST(test03_matrix_multiply) {
    stringstream ss1("2 3 2 6 4 1 9 7");
    stringstream ss2("3 2 3 2 4 10 11 8");

    Matrix m1 = Matrix_load(ss1);
    Matrix m2 = Matrix_load(ss2);
    Matrix mult = Matrix_multiply(&m1, &m2);

    stringstream out;
    Matrix_save(&mult, out);
    ASSERT_EQUAL(out.str(), "2 2 74 96 116 148 ")
}

// Uncomment these tests for the stretch functions
/*
TEST(test04_matrix_transpose) {
    stringstream ss1("2 3 2 6 4 1 9 7");
    Matrix m1 = Matrix_load(ss1);
    Matrix m1_t = Matrix_transpose(&m1);

    stringstream out;
    Matrix_save(&m1_t, out);
    ASSERT_EQUAL(out.str(), "3 2 2 1 6 9 4 7 ") 
}

TEST(test05_matrix_is_inverse) {
    // m1 or m2 not square
    stringstream rect_in("2 3 2 6 4 1 9 7");
    Matrix rect = Matrix_load(rect_in);
    stringstream square_in("2 2 0 -1 1 1");
    Matrix square = Matrix_load(square_in);
    ASSERT_FALSE(Matrix_is_inverse(&rect, &square));
    ASSERT_FALSE(Matrix_is_inverse(&square, &rect));

    stringstream small_square_in("1 1 1");
    Matrix square_small = Matrix_load(small_square_in);
    ASSERT_FALSE(Matrix_is_inverse(&square, &square_small));

    stringstream inverse_in("2 2 1 1 -1 0");
    Matrix inverse = Matrix_load(inverse_in);
    ASSERT_TRUE(Matrix_is_inverse(&square, &inverse));
}

TEST(test06_matrix_invert) {
    stringstream square_in("2 2 0 -1 1 1");
    Matrix square = Matrix_load(square_in);
    Matrix invert = Matrix_invert_2x2(&square);

    stringstream out;
    Matrix_save(&invert, out);
    ASSERT_EQUAL(out.str(), "2 2 1 1 -1 0 ") 
}
*/

TEST_MAIN()