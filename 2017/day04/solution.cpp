/**
 * $ g++ solution.cpp && ./a.out < input.txt
 */
#include <iostream>
#include <string>
#include <sstream>

using namespace std;


/**
 * O(n^2) word-by-word comparison
 */
bool part1_validate(string line) {
    string input1, input2;
    stringstream stream1(line);
    int counter1 = 0;
    while (stream1 >> input1) {
        stringstream stream2(line);
        int counter2 = 0;
        while (stream2 >> input2) {
            if (counter1 == counter2) {
                counter2++;
                continue;
            }
            if (input1 == input2) {
                return false;
            }
            counter2++;
        }
        counter1++;
    }
    return true;
}


int main() {
    cout << "Day 4!\n";
    int part1_total = 0;
    string line;
    while (getline(cin, line)) {
        if (part1_validate(line)) {
            part1_total++;
        }
    }
    cout << "Part 1: " << part1_total << "\n";
}
