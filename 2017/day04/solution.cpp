/**
 * $ g++ solution.cpp && ./a.out < input.txt
 */
#include <algorithm>
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


/**
 * Like part1_validate(), but with sorting of chars in word prior to comparisons
 *
 * via: https://stackoverflow.com/questions/9107516/sorting-characters-of-a-c-string/9107552#9107552
 */
bool part2_validate(string line) {
    string input1, input2;
    stringstream stream1(line);
    int counter1 = 0;
    while (stream1 >> input1) {
        sort(input1.begin(), input1.end());
        stringstream stream2(line);
        int counter2 = 0;
        while (stream2 >> input2) {
            if (counter1 == counter2) {
                counter2++;
                continue;
            }
            sort(input2.begin(), input2.end());
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
    int part2_total = 0;
    string line;
    while (getline(cin, line)) {
        if (part1_validate(line)) {
            part1_total++;
        }
        if (part2_validate(line)) {
            part2_total++;
        }
    }
    cout << "Part 1: " << part1_total << "\n";
    cout << "Part 2: " << part2_total << "\n";
}
