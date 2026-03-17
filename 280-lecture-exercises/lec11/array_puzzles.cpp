
#include <cassert>

// REQUIRES: size > 0
// EFFECTS: returns true if and only if the elements in arr
//  are in ascending order. Equality counts as ascending.
bool is_sorted(int *arr, int size) {
    for (int i = 0; i < size - 1; i++){
        if (arr[i] > arr[i + 1]){
            return false;
        }
    }
    return true;
}

// REQUIRES: size is even, size > 0
// EFFECTS: returns true if and only if arr is the same forward
//   and backwards.
// Examples of palindromes:
//   2244554422
//   123321
// Example of a non-palindrome:
//   123311
bool is_palindrome(int *arr, int size) {
    for (int i = 0; i < size / 2; i++){
        if (arr[i] != arr[size - 1 - i]){
            return false;
        }
    }
    return true;
}

// REQUIRES: in_size > 0, less_equal and greater are arrays with
//  size at least as big as in
// EFFECTS: Places the values of in into 2 arrays:
//   less_equal: all elements less than or equal to value
//   greater:    all elements greater than value
//  less_equal_size_out and greater_size_out are set equal to the
//   number of elements placed in less_equal or greater
void partition(int value, int *in, int in_size, int *less_equal, int &less_equal_size_out, int *greater, int &greater_size_out) {
    less_equal_size_out = 0;
    greater_size_out = 0;

    for ( int i = 0; i < in_size; i++){
        if (in[i] <= value){
            less_equal[less_equal_size_out] =in[i];
            less_equal_size_out++;
        }
        else{
            greater[greater_size_out] = in[i];
            greater_size_out++;
        }
    }
}

// REQUIRES: size > 0
// EFFECTS: Returns the length of the longest consecutive sequence
//  of the same value.
// Examples:
//  longest_equal_sequence({2,3,3,2}, 4) == 2
//  longest_equal_sequence({2,3,3,3}, 4) == 3
int longest_equal_sequence(int *arr, int size) {
    int longest = 1;
    int current = 1;

    for (int i = 1; i < size; i++){
        if (arr[i] == arr[i - 1]){
            current++;
        }
        else{
            current = 1;
        }

        if (current > longest){
            longest = current;
        }
        
    }
    return longest;
    
}

// REQUIRES: arr1_size > 0, arr2_size > 0
// EFFECTS: Return true if and only if all of the values present
//   in arr2 are present in arr1
bool is_subset(int *arr1, int arr1_size, int *arr2, int arr2_size) {
    for (int i = 0; i < arr2_size; i++){
        bool found = false;

    for (int  j = 0; j < arr1_size; j++){
        if (arr2[i] == arr1[j]){
            found = true;
            break;
        }
        
    }
    if (!found){
        return false;
    }
}
    return true;
      
    
}

// REQUIRES: all the elements of arr are between 0-9 (inclusive)
//           size > 0
// EFFECTS: returns the number that occurs the most frequently in arr.
//  If there is a tie, return the one with lower value.
// Hint: you can zero-initialize an array like this:
//   int myArray[100] = {0}; // all 100 elements are set to 0
int most_frequent(int *arr, int size) {
    int count[10] = {0};

    for (int  i = 0; i < size; i++){
        count[arr[i]]++;
    }
    int max_count = 0;
    int max_value = count[0];

    for (int i = 0; i < 10; i++){
        if (count[i] > max_count){
            max_count = count[i];
            max_value = i;

        }   
    }

    return max_value;
    

}