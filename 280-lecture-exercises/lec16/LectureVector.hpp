#pragma once

class LectureVector {
public:
    // EFFECTS: default constructor
    //   Sets size to 0, capacity to INITIAL_CAPACITY
    //   Allocates an array of size INITIAL_CAPACITY for elts
    LectureVector();

    // EFFECTS: destructor
    //   Deletes the elts array 
    ~LectureVector();

    // REQUIRES: new_capacity >= capacity()
    //  Allocates a new elts array of size new_capacity
    //   and copies all elements of the old elts array
    //   to the new. Deallocates the old elts array.
    //   Sets capacity_ to the new capacity.
    void grow(int new_capacity);

    // EFFECTS: adds value to the end of the vector.
    //  Calls grow() to add capacity if vector is currently
    //  full. Each time it grows, the vector doubles in capacity.
    void push_back(int value);

    // REQUIRES: index < size()
    // EFFECTS: returns a reference to the element at
    //  the given index.
    int &at(int index);

    int size() const { return _size; }
    int capacity() const { return _capacity; }

private:
    static const int INITIAL_CAPACITY = 2;
    int *elts;

    // These start with _ to distinguish them from the
    //  member functions size() and capacity().
    int _capacity; // size of the elts array
    int _size;     // number of elements actually in array
};
