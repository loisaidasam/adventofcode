/**
 * $ g++ solution2.cpp && ./a.out < input.txt 
 * Day 18!
 * Part 2: 7239
 *
 * long long int
 * https://stackoverflow.com/questions/1819189/what-range-of-values-can-integer-types-store-in-c/1819236#1819236
 *
 * My hiccup was the `jgz 1 3` line - I didn't know `jgz` could use value for
 * its first operand!
 */

#include <iostream>
#include <queue>
#include <stdint.h>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


bool VERBOSE = false;
int MAX_TOTAL_STEPS = -1;


struct Instruction {
    string line;
    string instruction;
    bool use_reg1;
    char reg1;
    long long int value1;
    bool use_reg2;
    char reg2;
    long long int value2;
};


vector<Instruction*> instructions;


bool use_reg(string word) {
    return word >= "a" && word <= "z";
}


void handle_line(string line) {
    stringstream stream(line);
    Instruction* instruction = new Instruction;
    instruction->line = line;
    stream >> instruction->instruction;
    string word;
    stream >> word;
    if (use_reg(word)) {
        instruction->use_reg1 = true;
        instruction->reg1 = word[0];
    } else {
        instruction->use_reg1 = false;
        instruction->value1 = stoi(word);
    }
    if (instruction->instruction != "snd" && instruction->instruction != "rcv") {
        stream >> word;
        if (use_reg(word)) {
            instruction->use_reg2 = true;
            instruction->reg2 = word[0];
        } else {
            instruction->use_reg2 = false;
            instruction->value2 = stoi(word);
        }
    }
    instructions.push_back(instruction);
}


class Program {
    private:
        int pid;
        unordered_map<char, long long int> register_values;
        int line = 0;
        long long int frequency;
        queue<long long int>* queue_send;
        queue<long long int>* queue_receive;
        int num_values_sent = 0;

    public:
        Program(int pid,
                queue<long long int>* queue_send,
                queue<long long int>* queue_receive) {
            register_values['p'] = pid;
            this->pid = pid;
            this->queue_send = queue_send;
            this->queue_receive = queue_receive;
        }

        void print_registers() {
            cout << register_values.size() << " registers:" << endl;
            for (unordered_map<char, long long int>::iterator it = register_values.begin(); it != register_values.end(); it++) {
                cout << "\t" << it->first << ": " << it->second << endl;
            }
        }

        void print_queues() {
            cout << "queues: send=" << queue_send->size() << " receive=" << queue_receive->size() << endl;
        }

        long long int get_register_value(char reg) {
            auto search = register_values.find(reg);
            if (search == register_values.end()) {
                return 0;
            }
            return search->second;
        }

        void print_line_str() {
            cout << "step " << line << ". " << instructions[line]->line << endl;
        }

        /**
         * set X Y sets register X to the value of Y.
         * add X Y increases register X by the value of Y.
         * mul X Y sets register X to the result of multiplying the value contained in
         *   register X by the value of Y.
         * mod X Y sets register X to the remainder of dividing the value contained in
         *   register X by the value of Y (that is, it sets X to the result of X modulo
         *   Y).
         * jgz X Y jumps with an offset of the value of Y, but only if the value of X is
         *   greater than zero. (An offset of 2 skips the next instruction, an offset of
         *   -1 jumps to the previous instruction, and so on.)
         *
         * snd X sends the value of X to the other program. These values wait in
         *   a queue until that program is ready to receive them. Each program
         *   has its own message queue, so a program can never receive a message
         *   it sent.
         * rcv X receives the next value and stores it in register X. If no
         *   values are in the queue, the program waits for a value to be sent
         *   to it. Programs do not continue to the next instruction until they
         *   have received a value. Values are received in the order they are
         *   sent.
         */
        bool step() {
            if (line >= instructions.size()) {
                cout << "pid=" << pid << " Instructions overflow! (line=" << line << ")" << endl;
                return false;
            }
            Instruction* instruction = instructions[line];
            if (instruction->instruction == "snd") {
                queue_send->push(get_register_value(instruction->reg1));
                num_values_sent++;
            } else if (instruction->instruction == "rcv") {
                if (queue_receive->size() == 0) {
                    return false;
                }
                register_values[instruction->reg1] = queue_receive->front();
                queue_receive->pop();
            } else {
                long long int value1, value2;
                if (instruction->use_reg1) {
                    value1 = get_register_value(instruction->reg1);
                } else {
                    value1 = instruction->value1;
                }
                if (instruction->use_reg2) {
                    value2 = get_register_value(instruction->reg2);
                } else {
                    value2 = instruction->value2;
                }
                if (instruction->instruction == "set") {
                    register_values[instruction->reg1] = value2;
                } else if (instruction->instruction == "add") {
                    register_values[instruction->reg1] = get_register_value(instruction->reg1) + value2;
                } else if (instruction->instruction == "mul") {
                    register_values[instruction->reg1] = get_register_value(instruction->reg1) * value2;
                } else if (instruction->instruction == "mod") {
                    register_values[instruction->reg1] = get_register_value(instruction->reg1) % value2;
                } else if (instruction->instruction == "jgz") {
                    if (value1 > 0) {
                        line += value2;
                        return true;
                    }
                } else {
                    throw 404;
                }
            }
            line++;
            return true;
        }

        int get_num_values_sent() {
            return num_values_sent;
        }
};

queue<long long int> * queue0 = new queue<long long int>();
queue<long long int> * queue1 = new queue<long long int>();
Program* program0 = new Program(0, queue1, queue0);
Program* program1 = new Program(1, queue0, queue1);


bool step_program(int pid, int total_steps) {
    if (VERBOSE) {
        cout << "\nPID " << pid << " (total steps: " << total_steps << ")" << endl;
    }
    Program* program;
    if (pid == 0) {
        program = program0;
    } else {
        program = program1;
    }
    if (VERBOSE) {
        program->print_line_str();
    }
    bool result = program->step();
    if (VERBOSE) {
        cout << "result: " << result << endl;
        program->print_queues();
        program->print_registers();
    }
    return result;
}


int part2() {
    int total_steps = 0;
    while (true) {
        while (step_program(0, total_steps)) {
            total_steps++;
            if (MAX_TOTAL_STEPS != -1 && total_steps >= MAX_TOTAL_STEPS) {
                return -1;
            }
        }
        while (step_program(1, total_steps)) {
            total_steps++;
            if (MAX_TOTAL_STEPS != -1 && total_steps >= MAX_TOTAL_STEPS) {
                return -1;
            }
        }
        if (step_program(0, total_steps)) {
            total_steps++;
            if (MAX_TOTAL_STEPS != -1 && total_steps >= MAX_TOTAL_STEPS) {
                return -1;
            }
            continue;
        }
        if (step_program(1, total_steps)) {
            total_steps++;
            if (MAX_TOTAL_STEPS != -1 && total_steps >= MAX_TOTAL_STEPS) {
                return -1;
            }
            continue;
        }
        return program1->get_num_values_sent();
    }
}

int main() {
    cout << "Day 18!" << endl;
    string line;
    while (getline(cin, line)) {
        handle_line(line);
    }
    cout << "Part 2: " << part2() << endl;
}
