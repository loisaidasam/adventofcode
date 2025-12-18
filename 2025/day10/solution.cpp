
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


struct Machine {
    string line;
    int num_digits;
    int target;
    vector<int> buttons;
};

int parse_target(string piece) {
    int target = 0;
    for (int i = 0; i < piece.length(); i++) {
        int digit;
        if (piece[i] == '#') {
            digit = 1;
        } else {
            // Is this default init behavior anyway?
            digit = 0;
        }
        target = (target << 1) | digit;
    }
    return target;
}

/**
 * Bitwise cheat sheet ..
 * 0001 1
 * 0010 2
 * 0011 3
 * 0100 4
 * 0101 5
 * 0110 6
 * 0111 7
 * 1000 8
 * 1001 9
 * 1010 10
 * 1011 11
 * 1100 12
 * 1101 13
 * 1110 14
 * 1111 15
 */
int parse_button(int num_digits, string piece) {
    string bits_str = "";
    for (int i = 0; i < num_digits; i++) {
        bits_str += ".";
    }
    stringstream ss(piece);
    string digit_str;
    while (getline(ss, digit_str, ',')) {
        bits_str[stoi(digit_str)] = '#';
    }
    // cout << bits_str << endl;
    return parse_target(bits_str);
}

/**
 * Example:
 * [.##.] (3) (1,3) (2) (2,3) (0,2) (0,1) {3,5,4,7}
 * [...#.] (0,2,3,4) (2,3) (0,4) (0,1,2) (1,2,3,4) {7,5,12,7,2}
 * [.###.#] (0,1,2,3,4) (0,3,4) (0,1,2,4,5) (1,2) {10,11,11,5,10,5}
 * 
 * Simplified (no brackets):
 * .##. 3 1,3 2 2,3 0,2 0,1 3,5,4,7
 * ...#. 0,2,3,4 2,3 0,4 0,1,2 1,2,3,4 7,5,12,7,2
 * .###.# 0,1,2,3,4 0,3,4 0,1,2,4,5 1,2 10,11,11,5,10,5
 */
Machine parse_machine(string line) {
    string piece, piece_last;
    stringstream ss(line);
    // Parse target
    getline(ss, piece, ' ');
    int num_digits = piece.length();
    int target = parse_target(piece);
    Machine m = {line, num_digits, target, {}};
    getline(ss, piece_last, ' ');
    while (getline(ss, piece, ' ')) {
        int button = parse_button(num_digits, piece_last);
        m.buttons.push_back(button);
        piece_last = piece;
    }
    // TODO: joltage from piece
    return m;
}

void print_machine(Machine m) {
    cout << m.line << endl << "num_digits=" << m.num_digits << " target=" << m.target << " buttons={";
    for (int button : m.buttons) {
        cout << button << ",";
    }
    cout << "}" << endl;
}

// Toggling:
// int a = 5;     // Binary: 101
// int b = 3;     // Binary: 011
// int c = a ^ b; // Binary: 110 = 6

// Bit-by-bit:
// 101
// 011
// ---
// 110
int press_button(int state, int button) {
    return state ^ button;
}

void print_state(int target, int state, vector<int> buttons) {
    cout << "\ttarget=" << target << " state=" << state << " buttons pressed: ";
    for (int button_pressed : buttons) {
        cout << button_pressed << " ";
    }
    cout << endl;
}

bool solve_in_num_presses(Machine m, int num_presses, int state, vector<int> buttons) {
    if (num_presses == 0) {
        // print_state(m.target, state, buttons);
        if (m.target == state) {
            // cout << "solved!" << endl;
            return true;
        }
        return false;
    }
    for (int button : m.buttons) {
        int new_state = press_button(state, button);
        vector<int> new_buttons = buttons;
        new_buttons.push_back(button);
        if (solve_in_num_presses(m, num_presses-1, new_state, new_buttons)) {
            return true;
        }
    }
    return false;
}

int solution1() {
    int total_presses = 0;
    string line;
    while (getline(cin, line)) {
        Machine m = parse_machine(line);
        print_machine(m);
        for (int num_presses = 0; ; num_presses++) {
            cout << "attempting to solve in " << num_presses << " presses ..." << endl;
            vector<int> buttons;
            if (solve_in_num_presses(m, num_presses, 0, buttons)) {
                total_presses += num_presses;
                break;
            }
        }
    }
    return total_presses;
}


int solution2() {
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
