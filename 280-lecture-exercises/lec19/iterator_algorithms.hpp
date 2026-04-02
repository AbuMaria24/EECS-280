#pragma once
#include <cassert>

// Note: all coding will be done in .hpp files for this lecture.
// You do not need to create any .cpp files.

// REQUIRES: begin is dereferenceable
// EFFECTS: return an iterator to the element between begin
//  and end with the largest value
template<typename Iter_type>
Iter_type lecture_max_element(Iter_type begin, Iter_type end) {
    auto max_val = *begin;
    Iter_type max_elem = begin;
    for (Iter_type it = begin; it != end; ++it) {
        if (*it > max_val) {
            max_val = *it;
            max_elem = it;
        }
    }
    return max_elem;
}

// EFFECTS: returns true if and only if val is present
//  between begin and end
template<typename Iter_type, typename Value_type>
bool lecture_contains(Iter_type begin, Iter_type end, Value_type val) {
    for (Iter_type it = begin; it != end; ++it) {
        if (*it == val){
            return true;
        }
    }
    return false;
}

// EFFECTS: returns an iterator to the location between begin
//  and end with value equal to val. If not found, returns end.
template<typename Iter_type, typename Value_type>
Iter_type lecture_find(Iter_type begin, Iter_type end, Value_type val) {
    for (Iter_type it = begin; it != end; ++it) {
        if (*it == val){
            return it;
        }
    }
    return end;
}

// EFFECTS: returns true if and only if:
//   (1) every element of the sequences (begin1, end1)
//       and (begin2, end2) have the same value in the
//       corresponding location
//   (2) there are the same number of elements between
//       begin1 and end1 vs. begin2 and end2
template<typename Iter_type>
bool lecture_equal(Iter_type begin1, Iter_type end1, Iter_type begin2, Iter_type end2) {
    Iter_type it1 = begin1;
    Iter_type it2 = begin2;

    while (it1 != end1 && it2 != end2){
        if (*it1 != *it2){
            return false;
        }
        ++it1;
        ++it2;
    }
    return (it1 == end1 && it2 == end2);
}

template<typename Iter_type, typename Value_type>
void remove_first (Iter_type begin, Iter_type end, Value_type val){
    for (Iter_type it = begin; it != end; ++it) {
        if (*it == val){
            for (Iter_type cur = it; cur != end; ++cur){
                Iter_type next = cur;
                ++next;

                if (next != end){
                    *cur = *next;
                }
            }
            return;
        }

    }
}

template<typename Iter_type, typename Value_type>
void remove_all (Iter_type begin, Iter_type end, Value_type val){
    for (Iter_type it = begin; it != end; ++it) {
        if (*it == val){
            for (Iter_type cur = it; cur != end; ++cur){
                Iter_type next = cur;
                ++next;

                if (next != end){
                    *cur = *next;
                }
            }
            --it;
        }
    }
}