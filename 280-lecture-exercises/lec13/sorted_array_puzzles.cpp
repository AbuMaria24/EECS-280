#include <cassert>

// REQUIRES: arr is sorted and has no duplicates
// EFFECTS: returns a pointer to the element of arr that is
//  equal to value, or nullptr if not found.
int *find(int value, int *arr, int size) {
    int left = 0;
    int right = size;

    while (left < right) {
        int size = right - left;
        int middle = left + (size / 2);

        if (arr[middle] == value) {
            return &arr[middle];
        } else if (value < arr[middle]) {
            right = middle;
        } else {
            left = middle + 1;
        }
    }
    return nullptr;
}

// REQUIRES: value is in arr, arr has no duplicate elements
// EFFECTS: returns the number of elements of arr that
//  have a value less than than the given value.
// This function must run in O(log n) time.
// Hint: use find() to do the hard work for you.
// Hint 2: use pointer subtraction.
int count_below(int value, int *arr, int size) {
    int *ptr = find(value, arr, size);
    assert(ptr != nullptr);
    return ptr - arr;

}

// EFFECTS: same as count_below but number of elements
//  with a value greater than given value.
int count_above(int value, int *arr, int size) {
    int *ptr = find(value, arr, size);
    assert(ptr != nullptr);
    return size - (ptr - arr) - 1;
    

}

// REQUIRES: arr1 and arr2 are sorted, out has enough
//  capacity to hold all elements of arr1 and arr2
// EFFECTS: Merges arr1 and arr2 into one larger sorted list
//  At the end of the function, out_size wil hold the size of the
//  output list.
//  arr1, arr2, and out may all contain duplicates.
// Draw out the test cases in sorted_array_puzzles_test on paper
//  to work out an algorithm before you start programming.
// This function is simple to code once you develop an algorithm, but
//  too difficult to solve by coding first.
void merge(int *arr1, int arr1_size, int *arr2, int arr2_size, int *out, int &out_size) {
    int i = 0;
    int j = 0;
    int k = 0;
    
    while (i < arr1_size && j < arr2_size){
        if (arr1[i] <= arr2[j]){
            out[k] = arr1[i];
            i++;
        }else
        {
            out[k] = arr2[j];
            j++;
        }
        k++;
    }
    while (i < arr1_size) {
        out[k] = arr1[i];
        i++;
        k++;
    }
        while (j < arr2_size) {
        out[k] = arr2[j];
        j++;
        k++;
    }
    out_size = k;
}

