/**
 * $ g++ solution.cpp && ./a.out
 * Day 15!
 * Part 1: 631
 */

#include <iostream>
#include <string>
#include <stdint.h>


using namespace std;


const uint64_t FACTOR_A = 16807;
const uint64_t FACTOR_B = 48271;

const uint64_t DIVISOR = 2147483647;

// Generator A starts with 873
// Generator B starts with 583
const uint64_t START_A = 873;
const uint64_t START_B = 583;
const int NUM_ROUNDS = 40000000;

// TESTING:
// const uint64_t START_A = 65;
// const uint64_t START_B = 8921;
// const int NUM_ROUNDS = 5;


/**
 * via http://avidinsight.uk/2015/02/convert-a-number-to-a-binary-string-and-back-in-cpp/
 */
string dec_to_binary(int input) {
    return std::bitset<32>(input).to_string();
}


int part1() {
    int count = 0;
    uint64_t a = START_A;
    uint64_t b = START_B;
    string str_a;
    string str_b;
    for (int round = 1; round <= NUM_ROUNDS; round++) {
        // if (round % 100000 == 0) {
        //     cout << "round " << round << endl;
        // }
        a = (a * FACTOR_A) % DIVISOR;
        b = (b * FACTOR_B) % DIVISOR;
        // cout << a << "\t" << b << endl;
        str_a = dec_to_binary(a);
        str_b = dec_to_binary(b);
        // cout << str_a << endl;
        // cout << str_b << "\n" << endl;
        if (str_a.substr(16, 16) == str_b.substr(16, 16)) {
            count++;
        }
    }
    return count;
}


int main() {
    cout << "Day 15!" << endl;
    cout << "Part 1: " << part1() << endl;
}
