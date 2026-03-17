#include "Matrix.hpp"
#include <cassert>
using namespace std;

void Matrix_init(Matrix *m, int rows, int cols) {
    m->data.resize(rows);
    for (int i = 0; i < rows; i++) {
        m->data.at(i).resize(cols);
    }
}

int *Matrix_at(Matrix *m, int row, int col) {
    return &m->data.at(row).at(col);
}

const int *Matrix_at(const Matrix *m, int row, int col) {
    return &m->data.at(row).at(col);
}

int Matrix_width(const Matrix *m) {
    assert(m->data.size());
    return m->data.at(0).size();
}

int Matrix_height(const Matrix *m) {
    return m->data.size();
}

Matrix Matrix_load(istream &in) {
    Matrix m;
    int height = 0;
    int width = 0;
    in >> height >> width;
    Matrix_init(&m, height, width);
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            in >> *Matrix_at(&m, r, c);
        }
    }
    return m;
}
void Matrix_save(const Matrix *m, std::ostream &out) {
    int height = Matrix_height(m);
    int width = Matrix_width(m);
    out << height << " " << width << " ";
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            out << *Matrix_at(m, r, c) << " ";
        }
    }
}

int Matrix_dot_product(const Matrix *m1, int m1_row, const Matrix *m2, int m2_col) {
    int width = Matrix_width(m1);
    assert(width == Matrix_height(m2));
    int sum = 0;
    for (int k = 0; k < width; ++k) {
        sum += *Matrix_at(m1, m1_row, k) * *Matrix_at(m2, k, m2_col);
    }
    return sum;
    
}
Matrix Matrix_multiply(const Matrix *m1, const Matrix *m2) {
    assert(Matrix_width(m1) == Matrix_height(m2));
    Matrix result;
    Matrix_init(&result, Matrix_height(m1), Matrix_width(m2));
    for (int r = 0; r < Matrix_height(m1); ++r) {
        for (int c = 0; c < Matrix_width(m2); ++c) {
            *Matrix_at(&result, r, c) = Matrix_dot_product(m1, r, m2, c);
        }
    }
    return result;
}