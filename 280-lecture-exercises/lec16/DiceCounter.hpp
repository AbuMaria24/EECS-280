#pragma once

class DiceCounter {
public:
    // REQUIRES: sides > 0
    // EFFECTS: construct a DiceCounter for a die with
    //  the given number of sides. The lowest number
    //  on the die is 1, and the highest is the same as sides.
    DiceCounter(int sides);
    ~DiceCounter();

    // REQUIRES: value > 0, value <= sides
    // EFFECTS: record that the die had this value
    //  when rolled.
    void record(int value);

    // EFFECTS: return the value that was rolled the
    //  most often. If tied, return the lowest tied value.
    int mostCommon();

private:
    int *counts;
    int sides;
};