
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

bool is_invalid(string num_str) {
    // num_str is something like "123123123"
    // cout << num_str << endl;
    // For each value from 2 to the len(num_str)
    for (int i = 2; i <= num_str.length(); i++) {
        // If num_str is divisible by this number
        if (num_str.length() % i == 0) {
            // cout << "\t" << i << endl;
            bool invalid = true;
            // The pattern is the first i chars,
            // so if i is 3, the pattern is "123"
            string pattern = num_str.substr(0, num_str.length() / i);
            // For each value from the start of where the next pattern should start to where it should end
            // So for example start at index 3 (for len("123")):
            // 123123123
            //    ^ here
            //       ^ then here
            int pattern_len = pattern.length();
            for (int j = pattern_len; invalid && j < num_str.length(); j += pattern_len) {
                string next_pattern = num_str.substr(j, pattern_len);
                // cout << "\t\tnext pattern start=" << j << " pattern_len=" << pattern_len << ": " << next_pattern << endl;
                if (pattern != next_pattern) {
                    invalid = false;
                    // cout << "\t\t\tno go" << endl;
                }
            }
            // If any of these i values are invalid all the way through, the number is invalid
            if (invalid) {
                return true;
            }
        }
    }
    return false;
}

long solution2() {
    long invalid_sum = 0;
    string group;
    while (getline(cin, group, ',')) {
        // cout << group << endl;
        stringstream ss(group);
        string str_start, str_stop;
        getline(ss, str_start, '-');
        getline(ss, str_stop, '-');
        long start, stop;
        start = stol(str_start);
        stop = stol(str_stop);
        for (long num = start; num <= stop; num++) {
            string num_str = to_string(num);
            if (is_invalid(num_str)) {
                invalid_sum += num;
                // cout << "\tinvalid: " << num << " sum=" << invalid_sum << endl;
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
