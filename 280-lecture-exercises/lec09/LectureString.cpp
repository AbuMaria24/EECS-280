#include "LectureString.hpp"
#include <cassert>
using namespace std;

// your code here
LectureString::LectureString(){
    data = {};
}

LectureString::LectureString(const string &in){
    for (char  c : in){
       data.push_back(c);
    }   
}

int LectureString::length()const{
    return data.size();
}
// REQUIRES: idx < this->length()
    // EFFECTS: returns the character at index idx
char LectureString::at(int idx) const{
    assert(idx < length());
    return data[idx];
}

bool LectureString::equalAtPosition(const LectureString &other, int start_position) const{
    assert(other.length() + start_position <= length());

    for (int  i = 0; i < other.length(); i++){
        if (data[start_position + i] != other.at(i)){
            return false;
        }
        
    }
    return true;
}

void LectureString::append(char c) {
    data.push_back(c);
}

void LectureString::append(const LectureString &to_append) {
    for (int i = 0; i < to_append.length(); i++) {
        data.push_back(to_append.at(i));
    }
}

void LectureString::replace(char find, char replacement){
    for (int i = 0; i < length(); i++){
        if (data[i] == find){
            data[i] = replacement;
        }
    }
}

void LectureString::replace(char find, const LectureString &replacement){
    vector<char>new_data;

    for (int i = 0; i < length(); i++){
       if (data[i] == find){
        for (int j = 0; j < replacement.length(); j++){
            new_data.push_back(replacement.at(j));
        }
       }
       else
            new_data.push_back(data[i]);
    }
    data = new_data;
}

bool operator==(const LectureString &lhs, const LectureString &rhs){
    if (lhs.length() !=rhs.length()){
        return false;
    }
    return lhs.equalAtPosition(rhs, 0);
}    
