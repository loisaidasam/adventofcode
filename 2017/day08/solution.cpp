/**
 * $ g++ solution.cpp && ./a.out < input.txt Day 8!
 * Part 1: 4902
 * Part 2: 7037
 */

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;


unordered_map<string, int> register_values;


int get_register_value(string lookup_register) {
    auto search = register_values.find(lookup_register);
    if (search == register_values.end()) {
        return 0;
    }
    return search->second;
}

int highest_value = 0;

/**
 * ioe dec 890 if qk > -10
 * gif inc -533 if qt <= 7
 * itw dec 894 if t != 0
 * nwe inc 486 if hfh < -2
 */
void handle_line(string line) {
    string token, change_register, condition, condition_register;
    int incr_value, incr_multiplier, condition_value;
    stringstream stream(line);
    for (int counter = 0; stream >> token; counter++) {
        switch (counter) {
            case 0: {
                change_register = token;
                break;
            }
            case 1: {
                if (token == "inc") {
                    incr_multiplier = 1;
                } else if (token == "dec") {
                    incr_multiplier = -1;
                } else {
                    throw 10;
                }
                break;
            }
            case 2: {
                incr_value = stoi(token);
                break;
            }
            case 3: {
                // "if"
                break;
            }
            case 4: {
                condition_register = token;
                break;
            }
            case 5: {
                condition = token;
                break;
            }
            case 6: {
                condition_value = stoi(token);
                break;
            }
        }
    }
    int register_value = get_register_value(condition_register);
    bool condition_result;
    if (condition == ">") {
        condition_result = register_value > condition_value;
    } else if (condition == ">=") {
        condition_result = register_value >= condition_value;
    } else if (condition == "<") {
        condition_result = register_value < condition_value;
    } else if (condition == "<=") {
        condition_result = register_value <= condition_value;
    } else if (condition == "==") {
        condition_result = register_value == condition_value;
    } else if (condition == "!=") {
        condition_result = register_value != condition_value;
    } else {
        throw 20;
    }
    if (! condition_result) {
        return;
    }
    register_value = get_register_value(change_register);
    int register_value_change = incr_multiplier * incr_value;
    int register_value_new = register_value + register_value_change;
    // cout << "Increasing " << change_register << " from " << register_value << " by " << register_value_change << " to " << register_value_new << endl;
    register_values[change_register] = register_value_new;
    if (register_value_new > highest_value) {
        highest_value = register_value_new;
    }
}

int part1() {
    int max_value = 0;
    for (pair<string, int> element : register_values) {
        // cout << element.first << " " << element.second << endl;
        if (element.second > max_value) {
            max_value = element.second;
        }
    }
    return max_value;
}

int part2() {
    return highest_value;
}

int main() {
    cout << "Day 8!" << endl;
    string line;
    while (getline(cin, line)) {
        handle_line(line);
    }
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}
