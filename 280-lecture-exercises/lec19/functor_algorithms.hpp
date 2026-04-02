#pragma once
#include <cassert>

// Note: all coding will be done in .hpp files for this lecture.
// You do not need to create any .cpp files.

class MultipleOfTenMatcher {
public:
    // EFFECTS: returns true if and only if val is
    //  a multiple of 10.
    bool operator()(int val) {
        return val % 10 == 0;
    }
};

class GreaterThanMatcher {
public:
    GreaterThanMatcher(int target) : target(target) {
        // your code here. You may add an initializer list too.
    }
    // EFFECTS: returns true if and only if val is
    //  greater than target.
    bool operator()(int val) {
        return val > target;
    }
private:
    int target;
};

// EFFECTS: returns the number of elements between
//  begin and end for which the matcher returns true
template<typename Iter_type, typename Functor_type>
int count_matches(Iter_type begin, Iter_type end, Functor_type &matcher) {
    int count = 0;

    for (Iter_type it = begin; it != end; ++it){
        if (matcher(*it)){
            ++count;
        }
    }
    return count;
}

// EFFECTS: returns the number of items between begin and end
//  that are a multiple of 10.
template<typename Iter_type>
int count_multiples_10(Iter_type begin, Iter_type end) {
    MultipleOfTenMatcher matcher;
    return count_matches(begin, end, matcher);
}

// EFFECTS: returns the number of items between begin and end
//  that are greater than val.
template<typename Iter_type>
int count_greater_than(Iter_type begin, Iter_type end, int val) {
    GreaterThanMatcher matcher(val);
    return count_matches(begin, end, matcher);
}
