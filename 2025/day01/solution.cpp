
#include <iostream>
#include <string>

using namespace std;

int solution1() {
    int zeros = 0;
    int dial = 50;
    string line;
    while (cin >> line) {
        char direction = line[0];
        int number = std::stoi(line.substr(1));
        int multiplier = 1;
        if (direction == 'L') {
            multiplier = -1;
        }
        number *= multiplier;
        dial += number;
        if ((dial % 100) == 0) {
            zeros++;
        }
    }
    return zeros;
}

int solution2() {
    int zeros = 0;
    int dial = 50;
    string line;
    while (cin >> line) {
        char direction = line[0];
        int number = std::stoi(line.substr(1));
        int tick = 1;
        if (direction == 'L') {
            tick = -1;
        }
        // cout << number << endl;
        for (int i = 0; i < number; i++) {
            dial += tick;
            if (dial == -1) {
                dial = 99;
            } else if (dial == 100) {
                dial = 0;
            }
            // cout << dial << " ";
            if (dial == 0) {
                zeros++;
                // cout << endl << "DING" << endl;
            }
        }
    }
    return zeros;
}

int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
