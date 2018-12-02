/**
 * Day 2
 *
 * 
 */

#include <iostream>
#include <map>
#include <string>

using namespace std;


int solution1() {
    string input;
    int counts2 = 0;
    int counts3 = 0;
    bool found2;
    bool found3;
    while (cin >> input) {
        // cout << "New word: " << input << endl;
        found2 = found3 = false;
        map<char, int> counts;
        for (int i = 0; i < input.length(); i++) {
            char letter = input[i];
            if (counts.find(letter) == counts.end()) {
                counts[letter] = 0;
            }
            counts[letter]++;
            // cout << letter << " current count: " << counts[letter] << endl;
        }
        for (map<char, int>::iterator it=counts.begin(); it != counts.end(); it++) {
            // cout << "counts[" << it->first << "] = " << it->second << endl;
            if (it->second == 2 && ! found2) {
                counts2++;
                found2 = true;
            } else if (it->second == 3 && ! found3) {
                counts3++;
                found3 = true;
            }
        }
        // cout << "counts2=" << counts2 << " counts3=" << counts3 << endl;
    }
    return counts2 * counts3;
}


int main() {
    cout << solution1() << endl;
    return 0;
}
