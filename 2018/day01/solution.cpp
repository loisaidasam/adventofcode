
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;


int get_frequency_delta(string input) {
    int delta = stoi(input.substr(1, input.length() - 1));
    if (input[0] == '+') {
        return delta;
    }
    return delta * -1;
}


int solution1() {
    int frequency = 0;
    string input;
    while (cin >> input) {
        // cout << input << endl;
        frequency += get_frequency_delta(input);
    }
    return frequency;
}

vector<int> read_input() {
    vector<int> deltas;
    string input;
    int delta;
    while (cin >> input) {
        delta = get_frequency_delta(input);
        deltas.push_back(delta);
    }
    return deltas;
}

int solution2() {
    vector<int> deltas  = read_input();
    int frequency = 0;
    set<int> frequencies_seen;
    frequencies_seen.insert(frequency);
    while (true) {
        for (int i = 0; i < deltas.size(); i++) {
            frequency += deltas[i];
            set<int>::iterator it = frequencies_seen.find(frequency);
            if (it != frequencies_seen.end()){
                return frequency;
            }
            frequencies_seen.insert(frequency);
        }
    }
}


int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}