
#include <iostream>
#include <set>
#include <string>
#include <sstream>

using namespace std;

int solution1() {
    bool has_start = false;
    set<int> beam_cols;
    string line;
    int beam_splits = 0;
    while (getline(cin, line)) {
        // cout << group << endl;
        if (! has_start) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == 'S') {
                    beam_cols.insert(i);
                    break;
                }
            }
            has_start = true;
        } else {
            for (int i = 0; i < line.length(); i++) {
                // If there's a splitter and an active beam in that col
                if (line[i] == '^' && beam_cols.count(i)) {
                    beam_splits++;
                    beam_cols.erase(i);
                    if (i > 0) {
                        beam_cols.insert(i-1);
                    }
                    if (i < line.length() - 1) {
                        beam_cols.insert(i+1);
                    }
                }
            }
        }
    }
    return beam_splits;
}

int solution2() {
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
