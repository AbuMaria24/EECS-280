#pragma once

#include <iostream>
#include <vector>

// This is a different Matrix implementation than P2
//  but the interface is the same.
struct Matrix {
    std::vector<std::vector<int> > data;
};

void Matrix_init(Matrix *m, int rows, int cols);
int *Matrix_at(Matrix *m, int row, int col);
const int *Matrix_at(const Matrix *m, int row, int col);
int Matrix_width(const Matrix *m);
int Matrix_height(const Matrix *m);

// EFFECTS:  Loads a Matrix from the stream in, in the format
//   <height> <width> <row 0 col 0> ... <row 0 col m> <row 1 col 0> ...
Matrix Matrix_load(std::istream &in);

// REQUIRES: m points to a valid Matrix
// EFFECTS:  Writes *m to the stream out in the format
//   <height> <width> <row 0 col 0> ... <row 0 col m> <row 1 col 0> ...
//   There must be a trailing space at the end of the output.
void Matrix_save(const Matrix *m, std::ostream &out);

// REQUIRES: Matrix_width(m1) == Matrix_height(m2)
//           Matrix_width(m1) > 0    
// EFFECTS:  Returns the dot product of the row of m1 at index m1_row
//            and the column of m2 at index m2_col
int Matrix_dot_product(const Matrix *m1, int m1_row, const Matrix *m2, int m2_col);

// REQUIRES: Matrix_width(m1) == Matrix_height(m2)
// EFFECTS:  Returns the result of the matrix multiplication of m1 and m2.
//  See https://www.mathsisfun.com/algebra/matrix-multiplying.html
//  for an example of matrix multiplication.
Matrix Matrix_multiply(const Matrix *m1, const Matrix *m2);

// You can uncomment the extra tests in tests.cpp when implementing
//  the stretch functions below.

// Stretch (ungraded)
// EFFECTS: Returns the transpose of a matrix m.
//   https://en.wikipedia.org/wiki/Transpose
Matrix Matrix_transpose(const Matrix *m);

// Stretch (ungraded)
// EFFECTS: Determines whether m2 is the inverse of m1
bool Matrix_is_inverse(const Matrix *m1, const Matrix *m2);

// Stretch (ungraded)
// REQURIES: Matrix_width(m) == Matrix_height(m) == 2
// EFFECTS: Returns the inverse of a 2x2 matrix m
//  see https://www.mathcentre.ac.uk/resources/uploaded/sigma-matrices7-2009-1.pdf
//  Use doubles for intermediate computations.
Matrix Matrix_invert_2x2(const Matrix *m);