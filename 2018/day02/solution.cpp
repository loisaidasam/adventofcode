/**
 * Day 2
 *
 * vectors, maps
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

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


vector<string> read_input() {
    vector<string> ids;
    string input;
    while (cin >> input) {
        ids.push_back(input);
    }
    return ids;
}


int check_difference(string str1, string str2) {
    int num_wrong = 0;
    int num_chars = min(str1.length(), str2.length());
    for (int i = 0; i < num_chars; i++) {
        if (str1[i] != str2[i]) {
            num_wrong++;
        }
    }
    return num_wrong;
}


string get_common_letters(string str1, string str2) {
    string result = "";
    int num_chars = min(str1.length(), str2.length());
    for (int i = 0; i < num_chars; i++) {
        if (str1[i] == str2[i]) {
            result += str1[i];
        }
    }
    return result;
}


string solution2() {
    vector<string> ids = read_input();
    for (int i = 0; i < ids.size(); i++) {
        for (int j = 0; j < ids.size(); j++) {
            if (i == j) {
                continue;
            }
            if (check_difference(ids[i], ids[j]) == 1) {
                return get_common_letters(ids[i], ids[j]);
            }
        }
    }
    return "No solution!";
}


int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
