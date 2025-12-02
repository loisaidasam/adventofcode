
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
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
