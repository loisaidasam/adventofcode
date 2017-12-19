/**
 * $ g++ solution.cpp && ./a.out < input.txt 
 * Day 18!
 * Part 1: 8600
 *
 * unsigned long long int
 * https://stackoverflow.com/questions/1819189/what-range-of-values-can-integer-types-store-in-c/1819236#1819236
 */

#include <iostream>
#include <stdint.h>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


struct Instruction {
    string line;
    string instruction;
    char reg1;
    bool use_reg2;
    char reg2;
    unsigned long long int value;
};


vector<Instruction*> instructions;

unordered_map<char, unsigned long long int> register_values;


unsigned long long int get_register_value(char reg) {
    auto search = register_values.find(reg);
    if (search == register_values.end()) {
        return 0;
    }
    return search->second;
}


void print_registers() {
    cout << register_values.size() << " registers:" << endl;
    for (unordered_map<char, unsigned long long int>::iterator it = register_values.begin(); it != register_values.end(); it++) {
        cout << "\t" << it->first << ": " << it->second << endl;
    }
}


void handle_line(string line) {
    stringstream stream(line);
    Instruction* instruction = new Instruction;
    instruction->line = line;
    stream >> instruction->instruction;
    stream >> instruction->reg1;
    if (instruction->instruction != "snd" && instruction->instruction != "rcv") {
        string word;
        stream >> word;
        if (word >= "a" && word <= "z") {
            instruction->use_reg2 = true;
            instruction->reg2 = word[0];
        } else {
            instruction->value = stoi(word);
        }
    }
    instructions.push_back(instruction);
}


/**
 * snd X plays a sound with a frequency equal to the value of X.
 * set X Y sets register X to the value of Y.
 * add X Y increases register X by the value of Y.
 * mul X Y sets register X to the result of multiplying the value contained in
 *   register X by the value of Y.
 * mod X Y sets register X to the remainder of dividing the value contained in
 *   register X by the value of Y (that is, it sets X to the result of X modulo
 *   Y).
 * rcv X recovers the frequency of the last sound played, but only when the
 *   value of X is not zero. (If it is zero, the command does nothing.)
 * jgz X Y jumps with an offset of the value of Y, but only if the value of X is
 *   greater than zero. (An offset of 2 skips the next instruction, an offset of
 *   -1 jumps to the previous instruction, and so on.)
 */
int part1() {
    int line = 0;
    unsigned long long int frequency;
    unsigned long long int value;
    while (true) {
        Instruction* instruction = instructions[line];
        // print_registers();
        // cout << "line " << line << ".\t" << instruction->line << endl;
        if (instruction->instruction == "snd") {
            frequency = get_register_value(instruction->reg1);
            line++;
            continue;
        }
        if (instruction->instruction == "rcv") {
            if (get_register_value(instruction->reg1) != 0) {
                return frequency;
            }
            line++;
            continue;
        }
        if (instruction->use_reg2) {
            value = get_register_value(instruction->reg2);
        } else {
            value = instruction->value;
        }
        if (instruction->instruction == "set") {
            register_values[instruction->reg1] = value;
        } else if (instruction->instruction == "add") {
            register_values[instruction->reg1] = get_register_value(instruction->reg1) + value;
        } else if (instruction->instruction == "mul") {
            register_values[instruction->reg1] = get_register_value(instruction->reg1) * value;
        } else if (instruction->instruction == "mod") {
            register_values[instruction->reg1] = get_register_value(instruction->reg1) % value;
        } else if (instruction->instruction == "jgz") {
            if (get_register_value(instruction->reg1) > 0) {
                line += value;
                continue;
            }
        } else {
            throw 404;
        }
        line++;
    }
}

int main() {
    cout << "Day 18!" << endl;
    string line;
    while (getline(cin, line)) {
        handle_line(line);
    }
    cout << "Part 1: " << part1() << endl;
}
