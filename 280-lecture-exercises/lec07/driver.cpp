#include "Matrix.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

// Load 2 matrices from input files, multiply them,
//  and store result in output file.
//
// Example:
// ./driver.exe mat1.txt mat2.txt output.txt
//
// There are sample input files in mat1.txt and mat2.txt
// The output should match expected.txt.
int main(int argc, char *argv[]) {
    assert(argc == 4);

    ifstream in1(argv[1]);
    ifstream in2(argv[2]);
    ofstream out(argv[3]);

    assert(in1.is_open());
    assert(in2.is_open());
    assert(out.is_open());

    Matrix m1 = Matrix_load(in1);
    Matrix m2 = Matrix_load(in2);
    Matrix result = Matrix_multiply(&m1, &m2);
    Matrix_save(&result, out);

    return 0;
}