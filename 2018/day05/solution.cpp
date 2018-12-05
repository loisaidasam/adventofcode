/**
 * Day 1
 *
 * sets, vectors
 */

#include <ctype.h>
#include <iostream>
#include <string>

using namespace std;


/**
 *
 * 0000000000111111
 * 0123456789012345
 * dabAcCaCBAcCcaDA
 */
string reduce_polymer(string polymer) {
    // cout << "reduce_polymer(" << polymer << ")" << endl;
    if (polymer.empty()) {
        return polymer;
    }
    char a, b;
    for (int i = 0; i < polymer.length() - 1; i++) {
        a = polymer[i];
        b = polymer[i + 1];
        if (! ((isupper(a) && tolower(a) == b) || (islower(a) && toupper(a) == b))) {
            continue;
        }
        // cout << "Match at " << i << " polymer length " << polymer.length() << endl;
        string result = "";
        if (i > 0) {
            result = polymer.substr(0, i);
        }
        if (i < polymer.length() - 2) {
            result += polymer.substr(i + 2, polymer.length() - i - 2);
        }
        if (result.empty()) {
            return "";
        }
        // Recursion results in segfault, stack goes too deep. 
        // return reduce_polymer(result);
        // Using iterative approach instead ...
        return result;
    }
    return polymer;
}


int fully_reduce_polymer(string polymer) {
    int polymer_length;
    int loop = 0;
    do {
        // cout << "loop #" << ++loop << ": " << polymer << " (" << polymer.length() << ")" << endl;
        polymer_length = polymer.length();
        // cout << "polymer_length=" << polymer_length << endl;
        polymer = reduce_polymer(polymer);
    }
    while (polymer.length() != polymer_length);
    return polymer_length;
}


int solution1() {
    string polymer;
    cin >> polymer;
    return fully_reduce_polymer(polymer);
}


string remove_unit_from_polymer(string polymer, char unit) {
    // Optimization?
    // if (polymer.find(unit) == string::npos && polymer.find(toupper(unit)) == string::npos) {
    //     return polymer;
    // }
    string result = "";
    for (int i = 0; i < polymer.length(); i++) {
        if (tolower(polymer[i]) == unit) {
            continue;
        }
        result += polymer[i];
    }
    return result;
}


int solution2() {
    string polymer, test_polymer;
    int polymer_length;
    cin >> polymer;
    int min_polymer_length = fully_reduce_polymer(polymer);
    for (char unit = 'a'; unit <= 'z'; unit++) {
        // For tracking progress
        cout << unit << endl;
        test_polymer = remove_unit_from_polymer(polymer, unit);
        if (test_polymer == polymer) {
            continue;
        }
        polymer_length = fully_reduce_polymer(test_polymer);
        if (polymer_length < min_polymer_length) {
            min_polymer_length = polymer_length;
        }
    }
    cout << endl;
    return min_polymer_length;
}


int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
