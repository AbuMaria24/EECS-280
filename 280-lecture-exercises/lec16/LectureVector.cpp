#include <iostream>
#include <vector> 
#include "LectureVector.hpp"
using namespace std;

LectureVector::LectureVector() {
   int size = 0;
   int  capacity = INITIAL_CAPACITY;
    elts = new int[INITIAL_CAPACITY];
}

LectureVector::~LectureVector() {
    delete [] elts;
}

void LectureVector::grow(int new_capacity){
    int* new_elts = new int[INITIAL_CAPACITY];

    
}