#include "Library.hpp"
#include <iostream>
#include <string>

using namespace std;

Library::Library(){}

Library::~Library(){
   for (size_t i = 0; i < books.size(); i++){
        delete books[i];
   } 
}

Library::Library(const Library &other){
    for (size_t i = 0; i < other.books.size(); i++){
        books.push_back(new Book(*other.books[i]));
    }   
}

Library &Library::operator=(const Library &other){
    if (this == &other){ 
        return *this; 
       }

    for (size_t i = 0; i < books.size(); i++){
        delete books[i];
   } 
   books.clear();

   for (size_t i = 0; i < other.books.size(); i++){
        books.push_back(new Book(*other.books[i]));
    } 
    return *this;
}

void Library::read(std::istream &in){
    string title;

    while (in >> title) {
        books.push_back(new Book(title.c_str()));
    }
    
}

char *Library::get_title(int book_idx) const {
    return books[book_idx]->get_title(); 
}