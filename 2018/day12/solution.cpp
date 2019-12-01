

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;


/**
 * via https://stackoverflow.com/questions/23596988/binary-string-to-integer-with-atoi/23597029#23597029
 *
 * Example:
 * int i = std::stoi("01000101", nullptr, 2);
 */
int convert_state_to_binary(string input) {
    stringstream ss;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '#') {
            ss << '1';
        } else if (input[i] == '.') {
            ss << '0';
        } else {
            cout << "Unknown state input char! " << input[i] << endl;
        }
    }
    return stoi(ss.str(), nullptr, 2);
}


int solution1() {
    string text;
    cin >> text;
    int state = convert_state_to_binary(text);
    int rule, rule_result;
    unordered_map<int, int> rules;
    while (cin >> text) {
        rule = convert_state_to_binary(text);
        cin >> text;
        rule_result = convert_state_to_binary(text);
        rules[rule] = rule_result;
    }
    cout << "Got " << rule.size() << " rules" << endl;
}


int main() {

}