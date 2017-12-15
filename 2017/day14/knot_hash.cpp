
#include <iostream>
#include <string>

using namespace std;


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


string knot_hash(string input) {
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
