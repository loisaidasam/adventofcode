
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

long solution1() {
    long invalid_sum = 0;
    string group;
    while (getline(cin, group, ',')) {
        stringstream ss(group);
        string str_start, str_stop;
        getline(ss, str_start, '-');
        getline(ss, str_stop, '-');
        long start, stop;
        start = stol(str_start);
        stop = stol(str_stop);
        for (long num = start; num <= stop; num++) {
            string num_str = to_string(num);
            if (num_str.length() % 2 == 0) {
                if (num_str.substr(0, num_str.length() / 2) == num_str.substr((num_str.length() / 2))) {
                    invalid_sum += num;
                }
            }
        }
    }
    return invalid_sum;
}

long solution2() {
    long invalid_sum = 0;
    string group;
    while (getline(cin, group, ',')) {
        stringstream ss(group);
        string str_start, str_stop;
        getline(ss, str_start, '-');
        getline(ss, str_stop, '-');
        long start, stop;
        start = stol(str_start);
        stop = stol(str_stop);
        for (long num = start; num <= stop; num++) {
            string num_str = to_string(num);
            bool valid = true;
            // "abcabcabc"
            for (int i = 2; valid && i <= num_str.length(); i++) {
                if (num_str.length() % i == 0) {
                    string pattern = num_str.substr(0, num_str.length() / i);
                    for (int j = pattern.length(); j < num_str.length(); j += pattern.length()) {
                        if (pattern != num_str.substr(j, j+pattern.length())) {
                            valid = false;
                        }
                    }
                }
            }
            if (!valid) {
                invalid_sum += num;
                // cout << invalid_sum << endl;
            }
        }
    }
    return invalid_sum;
}

int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
