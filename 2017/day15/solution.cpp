/**
 * $ g++ solution.cpp && ./a.out
 * Day 15!
 * Part 1: 631
 * Part 2: 279
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

// TESTING:
// const uint64_t START_A = 65;
// const uint64_t START_B = 8921;


int part1() {
    const int NUM_ROUNDS = 40000000;
    int count = 0;
    uint64_t a = START_A;
    uint64_t b = START_B;
    for (int round = 1; round <= NUM_ROUNDS; round++) {
        a = (a * FACTOR_A) % DIVISOR;
        b = (b * FACTOR_B) % DIVISOR;
        if (bitset<16>(a) == bitset<16>(b)) {
            count++;
        }
    }
    return count;
}


int part2() {
    const int NUM_ROUNDS = 5000000;
    int count = 0;
    uint64_t a = START_A;
    uint64_t b = START_B;
    for (int round = 1; round <= NUM_ROUNDS; round++) {
        // Divisible by 4
        do {
            a = (a * FACTOR_A) % DIVISOR;
        } while (bitset<2>(a) != 0);

        // Divisible by 8
        do {
            b = (b * FACTOR_B) % DIVISOR;
        } while (bitset<3>(b) != 0);

        if (bitset<16>(a) == bitset<16>(b)) {
            count++;
        }
    }
    return count;
}


int main() {
    cout << "Day 15!" << endl;
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}
