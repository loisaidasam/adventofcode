/**
 * $ g++ solution.cpp && ./a.out < input.txt
 * Day 1!
 * Part 1
 * 1182
 * Part 2
 * 1152
 */
#include <iostream>
#include <string>

using namespace std;

// https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c/5030086#5030086
int char_to_int(char input) {
    return input - '0';
}

int part1(string input) {
    cout << "Part 1\n";
    int total = 0;
    for (int i = 0; i < input.length(); i++) {
        int a = char_to_int(input[i]);
        int index_b = i + 1;
        if (index_b == input.length()) {
            index_b = 0;
        }
        int b = char_to_int(input[index_b]);
        if (a == b) {
            total += a;
        }
    }
    return total;
}

int part2(string input) {
    cout << "Part 2\n";
    int total = 0;
    for (int i = 0; i < input.length(); i++) {
        int a = char_to_int(input[i]);
        int index_b = i + (input.length() / 2);
        if (index_b >= input.length()) {
            index_b -= input.length();
        }
        int b = char_to_int(input[index_b]);
        if (a == b) {
            total += a;
        }
    }
    return total;
}


int main() {
    cout << "Day 1!\n";
    string input;
    cin >> input;
    cout << part1(input) << "\n";
    cout << part2(input) << "\n";
}
