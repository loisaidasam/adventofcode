/**
 * $ g++ solution.cpp && ./a.out < input.txt
 * Day 2!
 * Part 1
 * 45158
 * Part 2
 * 294
 */
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int part1_line(string line) {
    stringstream stream(line);
    string input;
    int min = -1;
    int max = -1;
    while (stream >> input) {
        int input_int = stoi(input);
        if (min == -1 || input_int < min) {
            min = input_int;
        }
        if (max == -1 || input_int > max) {
            max = input_int;
        }
    }
    return max - min;
}

int part2_line(string line) {
    string input1, input2;
    stringstream stream1(line);
    int counter1 = 0;
    while (stream1 >> input1) {
        int input1_int = stoi(input1);
        stringstream stream2(line);
        int counter2 = 0;
        while (stream2 >> input2) {
            if (counter1 == counter2) {
                counter2++;
                continue;
            }
            int input2_int = stoi(input2);
            if (input1_int > input2_int) {
                if (input1_int % input2_int == 0) {
                    return input1_int / input2_int;
                }
            } else {
                if (input2_int % input1_int == 0) {
                    return input2_int / input1_int;
                }
            }
            counter2++;
        }
        counter1++;
    }
    return 0;
}


int main() {
    cout << "Day 2!\n";
    int part1_total = 0;
    int part2_total = 0;
    string line;
    while (getline(cin, line)) {
        part1_total += part1_line(line);
        part2_total += part2_line(line);
    }
    cout << "Part 1\n" << part1_total << "\n";
    cout << "Part 2\n" << part2_total << "\n";
}
