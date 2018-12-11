/**
 * Day 8
 *
 * iteration vs. recursion, enums
 */

#include <iostream>
#include <stack>

using namespace std;


// https://stackoverflow.com/questions/12581064/enum-vs-strongly-typed-enum/12581154#12581154
enum class Instruction {CHILD_NODE, METADATA};


string print_instruction(Instruction instruction) {
    switch(instruction) {
        case Instruction::CHILD_NODE:
            return "CHILD_NODE";
        case Instruction::METADATA:
            return "METADATA";
    }
}


int solution1() {
    int sum = 0;
    stack<Instruction> instructions;
    // Initial instructions
    instructions.push(Instruction::CHILD_NODE);
    Instruction instruction;
    int data, num_children, num_metadata;
    while (instructions.size() > 0) {
        // cout << "Instructions size: " << instructions.size() << " sum=" << sum << endl;
        instruction = instructions.top();
        instructions.pop();
        // cout << "Instruction: " << print_instruction(instruction) << endl;
        switch(instruction) {
            case Instruction::CHILD_NODE:
                cin >> num_children >> num_metadata;
                // cout << num_children << "x CHILD_NODE / " << num_metadata << "x METADATA" << endl;
                for (int i = 0; i < num_metadata; i++) {
                    instructions.push(Instruction::METADATA);
                }
                for (int i = 0; i < num_children; i++) {
                    instructions.push(Instruction::CHILD_NODE);
                }
                break;
            case Instruction::METADATA:
                cin >> data;
                sum += data;
                break;
            default:
                cout << "Unknown instruction type!" << endl;
        }
    }
    return sum;
}


int main() {
    cout << solution1() << endl;
    return 0;
}
