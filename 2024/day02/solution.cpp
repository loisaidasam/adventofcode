
#include <iostream>
#include <sstream>

using namespace std;

bool is_safe(string line) {
    istringstream iss(line); // Create a stringstream for parsing the line
    int num;
    int last;
    int count = 0;
    bool increasing;

    // Read integers from the line
    while (iss >> num) {
        cout << num << " ";
        if (count == 1) {
            increasing = last > num;
        }
        if (count >= 1) {
            int diff;
            if (increasing) {
                if (last < num) {
                    cout << "Unsafe, decr" << endl;
                    return false;
                }
                diff = last - num;
            } else {
                if (last > num) {
                    cout << "Unsafe, incr" << endl;
                    return false;
                }
                diff = num - last;
            }
            if (diff < 1 || diff > 3) {
                cout << "Unsafe, diff (" << diff << ")" << endl;
                return false;
            }
        }
        last = num;
        count++;
    }
    cout << "Safe" << endl;
    return true;
}

int solution1() {
    string line;
    int num_safe = 0;

    while (getline(cin, line)) { // Read one line at a time
        if (is_safe(line)) {
            num_safe++;
        }
    }

    return num_safe;
}

int solution2() {
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
