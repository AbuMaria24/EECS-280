#include "Book.hpp"
#include <cstring>

// EFFECTS: make a copy of the C-style string in
//  on the heap.
char *duplicate_c_string(const char *in) {
    int length = strlen(in);
    char *copy = new char[length + 1];
    strncpy(copy, in, length + 1);
    return copy;
}

// Your code here
Book::Book(const char *title_in){
    title = duplicate_c_string(title_in);
}

Book::~Book(){
    delete [] title;
}

Book::Book(const Book &other){
    title = duplicate_c_string(other.title);
}

Book &Book::operator=(const Book &other){
    if (this == &other){ 
        return *this; 
       }
    delete [] title;
    title = duplicate_c_string(other.title);
    return *this;

}

char *Book::get_title() const{
    return title;

}