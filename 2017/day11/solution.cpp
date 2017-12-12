/**
 */

#include <iostream>
#include <sstream>
#include <string>

using namespace std;


int count_n_s = 0;
int count_ne_sw = 0;
int count_se_nw = 0;


void step(string direction) {
    // cout << direction << endl;
    if (direction == "n") {
        count_n_s++;
    } else if (direction == "s") {
        count_n_s--;
    } else if (direction == "ne") {
        count_ne_sw++;
    } else if (direction == "sw") {
        count_ne_sw--;
    } else if (direction == "se") {
        count_se_nw++;
    } else if (direction == "nw") {
        count_se_nw--;
    } else {
        throw 199;
    }
}


int part1(string input) {
    stringstream stream(input);
    string direction;
    char buffer;
    while (stream >> buffer) {
        direction += buffer;
        if (stream.peek() == ',') {
            stream.ignore();
            step(direction);
            direction = "";
        }
    }
    step(direction);
    return abs(count_n_s) + abs(count_ne_sw) + abs(count_se_nw);
}


int main() {
    cout << "Day 11!" << endl;
    string input;
    cin >> input;
    cout << "Part 1: " << part1(input) << endl;
}
