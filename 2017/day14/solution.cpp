/**
 * g++ solution.cpp && ./a.out < input.txt
 * Day 14!
 * Part 1: 8316
 */

#include <iostream>
#include "knot_hash.cpp"

using namespace std;


int binary_values[128][128];


string hex_to_binary(char c) {
    switch(toupper(c)) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
    throw 150;
}


void set_values(string input) {
    for (int row = 0; row < 128; row++) {
        string hash_input = input + "-" + to_string(row);
        // cout << "hash_input " << hash_input << endl;
        string hash = knot_hash(hash_input);
        // cout << "hash " << hash << endl;
        for (int hash_letter_num = 0; hash_letter_num < hash.length(); hash_letter_num++) {
            string binary = hex_to_binary(hash[hash_letter_num]);
            // cout << "\t" << hash_letter_num << ".\t" << binary << endl;
            if (binary.length() != 4) {
                cout << "Unknown binary length (not 4): " << binary << endl;
                throw 150;
            }
            for (int binary_col_num = 0; binary_col_num < 4; binary_col_num++) {
                int col = (hash_letter_num * 4) + binary_col_num;
                if (binary[binary_col_num] == '0') {
                    binary_values[row][col] = 0;
                } else if (binary[binary_col_num] == '1') {
                    binary_values[row][col] = 1;
                } else {
                    cout << "Unknown binary value: " << binary[binary_col_num] << endl;
                    throw 400;
                }
            }
        }
    }
}


int part1() {
    int used = 0;
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j++) {
            if (binary_values[i][j] == 1) {
                used++;
            }
        }
    }
    return used;
}


int part2(string input) {
    return 0;
}


int main() {
    cout << "Day 14!" << endl;
    string input;
    cin >> input;
    set_values(input);
    cout << "Part 1: " << part1() << endl;
}
