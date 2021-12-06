
#include <iostream>
#include <string>

using namespace std;

int solution1() {
    int position, depth;
    string direction;
    int value;
    while (cin >> direction >> value) {
        // cout << direction << endl;
        // cout << value << endl;
        if (direction == "up") {
            depth -= value;
        } else if (direction == "down") {
            depth += value;
        } else if (direction == "forward") {
            position += value;
        } else {
            cout << "unknown direction: " << direction << endl;
        }
    }
    return depth * position;
}

int solution2() {
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
