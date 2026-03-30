#include "DiceCounter.hpp"

using namespace std;

DiceCounter::DiceCounter(int side_in){
    sides = side_in;
    counts = new int[sides];

    for (int i = 0; i < sides; i++){
        counts[i] = 0;
    }
}

DiceCounter::~DiceCounter(){
    delete[] counts;
}

void DiceCounter::record(int value){
    counts[value - 1]++;
}

int DiceCounter::mostCommon() {
    int max_index = 0;

    for (int i = 1; i < sides; i++) {
        if (counts[i] > counts[max_index]) {
            max_index = i;
        }
    }

    return max_index + 1; 
}