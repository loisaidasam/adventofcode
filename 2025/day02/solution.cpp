
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

int solution2() {
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
