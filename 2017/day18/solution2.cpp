/**
 * $ g++ solution.cpp && ./a.out < input.txt 
 * Day 18!
 * Part 2: 8600
 *
 * unsigned long long int
 * https://stackoverflow.com/questions/1819189/what-range-of-values-can-integer-types-store-in-c/1819236#1819236
 */

#include <iostream>
#include <queue>
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


class Program {
    private:
        int pid;
        unordered_map<char, unsigned long long int> register_values;
        int line = 0;
        unsigned long long int frequency;
        queue<unsigned long long int>* queue_send;
        queue<unsigned long long int>* queue_receive;
        int num_values_sent = 0;

    public:
        Program(int pid,
                queue<unsigned long long int>* queue_send,
                queue<unsigned long long int>* queue_receive) {
            this->pid = pid;
            this->queue_send = queue_send;
            this->queue_receive = queue_receive;
        }

        void print_registers() {
            cout << "pid=" << pid << " " << register_values.size() << " registers:" << endl;
            for (unordered_map<char, unsigned long long int>::iterator it = register_values.begin(); it != register_values.end(); it++) {
                cout << "\t" << it->first << ": " << it->second << endl;
            }
        }

        void print_queues() {
            cout << "pid=" << pid << " queues: send=" << queue_send->size() << " receive=" << queue_receive->size() << endl;
        }

        unsigned long long int get_register_value(char reg) {
            auto search = register_values.find(reg);
            if (search == register_values.end()) {
                return 0;
            }
            return search->second;
        }

        void print_line_str() {
            cout << "\n" << "pid=" << pid << " " << line << ". " << instructions[line]->line << endl;
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
                unsigned long long int value;
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


int part2() {
    queue<unsigned long long int> * queue0 = new queue<unsigned long long int>();
    queue<unsigned long long int> * queue1 = new queue<unsigned long long int>();
    Program* program0 = new Program(0, queue1, queue0);
    Program* program1 = new Program(1, queue0, queue1);
    bool result0, result1;
    while (true) {
        // program0->print_line_str();
        // program0->print_queues();
        // program0->print_registers();
        result0 = program0->step();
        // cout << "result: " << result0 << endl;
        if (result0) {
            continue;
        }
        // program1->print_line_str();
        // program1->print_queues();
        // program1->print_registers();
        result1 = program1->step();
        // cout << "result: " << result1 << endl;
        if (result1) {
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
    cout << "Part 2: \n" << part2() << endl;
}
