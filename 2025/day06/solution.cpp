
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


// Equation e = {'+' {}}
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
 * 123 328  51 64 
 *  45 64  387 23 
 *   6 98  215 314
 * *   +   *   +
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

long solve_equation(Equation e) {
    long total = 0;
    if (e.type == '*') {
        total = 1;
    }
    for (long input : e.inputs) {
        // cout << input;
        if (e.type == '*') {
            total *= input;
            // cout << " * ";
        } else {
            total += input;
            // cout << " + ";
        }
    }
    // cout << "= " << total << endl;
    return total;
}


long solution1() {
    vector<Equation> equations = read_equations();
    long total = 0;
    for (Equation e : equations) {
        // print_equation(e);
        total += solve_equation(e);
    }
    return total;
}

int solution2() {
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
