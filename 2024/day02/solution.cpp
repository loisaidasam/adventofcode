
#include <iostream>
#include <sstream>

using namespace std;

bool test_levels(bool increasing, int last, int num) {
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
    return true;
}

bool is_safe(string line, int levels_removable) {
    istringstream iss(line); // Create a stringstream for parsing the line
    int num;
    int last;
    int count = 0;
    bool increasing;
    int levels_removed = 0;

    // Read integers from the line
    while (iss >> num) {
        cout << num << " ";
        if (count == 1) {
            increasing = last > num;
        }
        if (count >= 1) {
            if (! test_levels(increasing, last, num)) {
                if (levels_removed < levels_removable) {
                    cout << "Removing level.. ";
                    levels_removed++;
                } else {
                    return false;
                }
            }
        }
        last = num;
        count++;
    }
    cout << "Safe" << endl;
    return true;
}

int test(int levels_removable) {
    string line;
    int num_safe = 0;

    while (getline(cin, line)) { // Read one line at a time
        if (is_safe(line, levels_removable)) {
            num_safe++;
        }
    }

    return num_safe;
}

int solution1() {
    int levels_removable = 0;
    return test(levels_removable);
}

int solution2() {
    int levels_removable = 1;
    return test(levels_removable);
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
