/**
 * $ g++ solution.cpp && ./a.out  < input.txt
 * Day 6!
 * part 1: 3156
 * part 2: 1610
 *
 * Learned about accumulate - basically reduce(), unordered_set
 */

#include <iostream>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


/**
 * Notes on accumulate():
 *
 * - http://en.cppreference.com/w/cpp/algorithm/accumulate
 * - http://www.cplusplus.com/reference/numeric/accumulate/
 */
string get_banks_string(vector<int> banks) {
    return accumulate(next(banks.begin()),
                      banks.end(),
                      // start with first element
                      to_string(banks[0]),
                      // [] is an anonymous function/lambda expression
                      // http://en.cppreference.com/w/cpp/language/lambda
                      // Only from C++11
                      [](string a, int b) {
                          return a + '-' + to_string(b);
                      });
}


int get_biggest_bank(vector<int> banks) {
    int maxBank, maxBankSize;
    for (int i = 0; i < banks.size(); i++) {
        if (i == 0) {
            maxBank = 0;
            maxBankSize = banks[0];
            continue;
        }
        if (banks[i] > maxBankSize) {
            maxBank = i;
            maxBankSize = banks[i];
        }
    }
    return maxBank;
}


int part1(vector<int> banks) {
    unordered_set<string> seen;
    int redistributions = 0;
    string banks_string;
    int biggest_bank, bank_value, bank_index;
    while(true) {
        banks_string = get_banks_string(banks);
        // cout << banks_string << endl;
        auto search = seen.find(banks_string);
        // Found it!
        if (search != seen.end()) {
            return redistributions;
        }
        // Not found. Redistribute.
        seen.insert(banks_string);
        biggest_bank = get_biggest_bank(banks);
        bank_value = banks[biggest_bank];
        banks[biggest_bank] = 0;
        bank_index = biggest_bank + 1;
        if (bank_index == banks.size()) {
            bank_index = 0;
        }
        while (bank_value > 0) {
            banks[bank_index]++;
            bank_value--;
            bank_index++;
            if (bank_index == banks.size()) {
                bank_index = 0;
            }
        }
        redistributions++;
    }
    return 0;
}


/**
 * `unordered_map` refs:
 * - http://en.cppreference.com/w/cpp/container/unordered_map
 * - http://en.cppreference.com/w/cpp/container/unordered_map/find
 */
int part2(vector<int> banks) {
    // banks_string <string> / redistributions <int>
    unordered_map<string, int> seen;
    int redistributions = 0;
    string banks_string;
    int biggest_bank, bank_value, bank_index;
    while(true) {
        banks_string = get_banks_string(banks);
        // cout << banks_string << endl;
        auto search = seen.find(banks_string);
        // Found it!
        if (search != seen.end()) {
            return redistributions - search->second;
        }
        // Not found. Redistribute.
        seen.insert(make_pair(banks_string, redistributions));
        biggest_bank = get_biggest_bank(banks);
        bank_value = banks[biggest_bank];
        banks[biggest_bank] = 0;
        bank_index = biggest_bank + 1;
        if (bank_index == banks.size()) {
            bank_index = 0;
        }
        while (bank_value > 0) {
            banks[bank_index]++;
            bank_value--;
            bank_index++;
            if (bank_index == banks.size()) {
                bank_index = 0;
            }
        }
        redistributions++;
    }
    return 0;
}


int main() {
    cout << "Day 6!" << endl;
    vector<int> banks;
    int blocks;
    while (cin >> blocks) {
        banks.push_back(blocks);
    }
    cout << "part 1: " << part1(banks) << endl;
    cout << "part 2: " << part2(banks) << endl;
}
