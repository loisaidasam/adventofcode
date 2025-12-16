
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


// Equation e = {'+', {}}
struct Equation {
    char type;
    vector<long> inputs;
};

void print_equation(Equation e) {
    cout << "equation " << e.type;
    for (long input : e.inputs) {
        cout << " " << input;
    }
    cout << endl;
}

/**
 * Example:
 *
 * "123 328  51 64 "
 * " 45 64  387 23 "
 * "  6 98  215 314"
 * "*   +   *   +  "
 */
vector<Equation> read_equations() {
    vector<string> lines;
    string line, item;
    while (getline(cin, line)) {
        lines.push_back(line);
    }
    vector<Equation> equations;
    bool first_row = true;
    for (int i = 0; i < lines.size()-1; i++) {
        stringstream ss(lines[i]);
        int j = 0;
        while (ss >> item) {
            if (first_row) {
                equations.push_back({' ', {}});
            }
            equations[j].inputs.push_back(stol(item));
            j++;
        }
        first_row = false;
    }
    stringstream ss(lines[lines.size()-1]);
    int j = 0;
    while (ss >> item) {
        equations[j].type = item[0];
        j++;
    }
    // for (Equation e : equations) {
    //     print_equation(e);
    // }
    return equations;
}

long solve_equation(Equation e, bool debug) {
    long total = 0;
    if (e.type == '*') {
        total = 1;
    }
    for (long input : e.inputs) {
        if (debug) {
            cout << input;
        }
        if (e.type == '*') {
            total *= input;
            if (debug) {
                cout << " * ";
            }
        } else {
            total += input;
            if (debug) {
                cout << " + ";
            }
        }
    }
    if (debug) {
        cout << "= " << total << endl;
    }
    return total;
}


long solution1() {
    vector<Equation> equations = read_equations();
    long total = 0;
    for (Equation e : equations) {
        // print_equation(e);
        total += solve_equation(e, false);
    }
    return total;
}

/**
 * Example:
 *
 * "123 328  51 64 "
 * " 45 64  387 23 "
 * "  6 98  215 314"
 * "*   +   *   +  "
 */
vector<Equation> read_equations2() {
    vector<string> lines;
    string line, item;
    while (getline(cin, line)) {
        lines.push_back(line);
    }
    vector<Equation> equations;
    Equation e = {' ', {}};
    for (int col = line.length()-1; col >= 0; col--) {
        bool seen = false;
        int input = 0;
        for (int row = 0; row < lines.size()-1; row++) {
            char value = lines[row][col];
            if (value != ' ') {
                input *= 10;
                // char to int:
                // char c = '5';
                // int num = c - '0';  // num = 5
                input += value - '0';
                seen = true;
            }
        }
        if (seen) {
            e.inputs.push_back(input);
        }
        // Move onto the next equation
        else {
            equations.push_back(e);
            e = {' ', {}};
        }
    }
    // Always write the last one
    equations.push_back(e);
    e = {' ', {}};
    stringstream ss(lines[lines.size()-1]);
    int j = equations.size() - 1;
    while (ss >> item) {
        equations[j].type = item[0];
        j--;
    }
    // for (Equation e : equations) {
    //     print_equation(e);
    // }
    return equations;
}

long solution2() {
    vector<Equation> equations = read_equations2();
    long total = 0;
    for (Equation e : equations) {
        // print_equation(e);
        total += solve_equation(e, false);
    }
    return total;
}

int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
