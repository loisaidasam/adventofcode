/**
 * g++ solution.cpp && ./a.out < input.txt
 * Day 14!
 * Part 1: 8316
 */

#include <iostream>
#include "knot_hash.cpp"

using namespace std;


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


int part1(string input) {
    int used = 0;
    for (int i = 0; i < 128; i++) {
        string hash_input = input + "-" + to_string(i);
        // cout << "hash_input " << hash_input << endl;
        string hash = knot_hash(hash_input);
        // cout << "hash " << hash << endl;
        for (int i = 0; i < hash.length(); i++) {
            string binary = hex_to_binary(hash[i]);
            // cout << "\t" << i << ".\t" << binary << endl;
            for (int j = 0; j < binary.length(); j++) {
                if (binary[j] == '1') {
                    used++;
                }
            }
        }
    }
    return used;
}


int main() {
    string input;
    cin >> input;
    cout << "Day 14!" << endl;
    cout << "Part 1: " << part1(input) << endl;
}
