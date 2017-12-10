/**
 * $ g++ solution.cpp &&  ./a.out < input.txt
 * Day 10!
 * Part 1: 19591
 * Part 2: 62e2204d2ca4f4924f6e7a80f1288786
 */

#include <iostream>
#include <sstream>
#include <string>

using namespace std;


// const int NUM_ELEMENTS = 5;
const int NUM_ELEMENTS = 256;


int values [NUM_ELEMENTS];
int current_position;
int skip_size;


void initialize_values() {
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        values[i] = i;
    }
    current_position = 0;
    skip_size = 0;
}


void print_values() {
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        if (current_position == i) {
            cout << "[";
        }
        cout << values[i];
        if (current_position == i) {
            cout << "]";
        }
        cout << " ";
    }
    cout << endl;
}


void handle_length(int length) {
    // print_values();
    // cout << "length " << length << endl;
    int i = current_position;
    int j = (current_position + length - 1) % NUM_ELEMENTS;
    for (int num_swaps = 0; num_swaps < length / 2; num_swaps++) {
        // cout << "i=" << i << " j=" << j << endl;
        int temp = values[i];
        values[i] = values[j];
        values[j] = temp;
        i = (i + 1) % NUM_ELEMENTS;
        // Apparently -1 % 5 == -1, not 4
        if (j == 0) {
            j = NUM_ELEMENTS - 1;
        } else {
            j--;
        }
    }
    current_position = (current_position + length + skip_size) % NUM_ELEMENTS;
    skip_size++;
}


int part1(string input) {
    initialize_values();
    // https://stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring/1894955#1894955
    stringstream stream(input);
    int length;
    while (stream >> length) {
        handle_length(length);
        if (stream.peek() == ',') {
            stream.ignore();
        }
    }
    // cout << "Final values:" << endl;
    // print_values();
    return values[0] * values[1];
}


int char_to_ascii(char input) {
    return int(input);
}


string int_to_hex(int input) {
    char buffer [2];
    // no itoa() :\
    // return itoa(input, buffer, 16);
    sprintf(buffer, "%02x", input);
    return buffer;
}


string part2(string input) {
    initialize_values();
    int EXTRA_LENGTHS [5] = {17, 31, 73, 47, 23};
    int length;
    for (int round = 0; round < 64; round++) {
        for (int i = 0; i < input.length(); i++) {
            length = char_to_ascii(input[i]);
            // cout << input[i] << " " << length << endl;
            handle_length(length);
        }
        for (int i = 0; i < 5; i++) {
            length = EXTRA_LENGTHS[i];
            handle_length(length);
        }
    }
    string result = "";
    for (int block = 0; block < 16; block++) {
        int index = block * 16;
        int xor_result = values[index];
        for (int i = 1; i < 16; i++) {
            xor_result ^= values[index + i];
        }
        result += int_to_hex(xor_result);
    }
    return result;
}


int main() {
    cout << "Day 10!" << endl;
    string input;
    cin >> input;
    cout << "Part 1: " << part1(input) << endl;
    // cout << int_to_hex(64) << " " << int_to_hex(7) << " " << int_to_hex(255) << " " << endl;
    cout << "Part 2: " << part2(input) << endl;
}
