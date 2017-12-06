/**
 * $ g++ solution.cpp && ./a.out < input.txt
 * Day 5!
 * part 1: 375042
 * part 2: 28707598
 *
 * Learning about vectors
 */

#include <iostream>
#include <vector>

using namespace std;


int part1(vector<int> instructions) {
    int step = 0;
    int index = 0;
    int next_index;
    while(index >= 0 && index < instructions.size()) {
        next_index = index + instructions[index];
        instructions[index]++;
        step++;
        index = next_index;
    }
    return step;
}


int part2(vector<int> instructions) {
    int step = 0;
    int index = 0;
    int next_index;
    while(index >= 0 && index < instructions.size()) {
        next_index = index + instructions[index];
        if (instructions[index] >= 3) {
            instructions[index]--;
        } else {
            instructions[index]++;
        }
        step++;
        index = next_index;
    }
    return step;
}


int main() {
    cout << "Day 5!" << endl;
    vector<int> instructions;
    int instruction;
    while (cin >> instruction) {
        instructions.push_back(instruction);
    }
    cout << "part 1: " << part1(instructions) << endl;
    cout << "part 2: " << part2(instructions) << endl;
}
