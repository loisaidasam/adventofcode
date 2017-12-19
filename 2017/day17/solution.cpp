/**
 * $ g++ solution.cpp && echo '355' | ./a.out 
 * Day 17!
 * Part 1: 1912
 * Part 2: 21066990
 */

#include <iostream>
#include <list>
#include <string>


using namespace std;


void print_buffer(int value, list<int> buffer) {
    cout << value << ".\t";
    list<int>::iterator it = buffer.begin();
    while (it != buffer.end()) {
        cout << *it << " ";
        it++;
    }
    cout << endl;
}


/**
 * http://www.cplusplus.com/reference/list/list/
 * http://www.cplusplus.com/reference/list/list/insert/
 * 
 * (0), the initial state before any insertions.
 * 0 (1): the spinlock steps forward three times (0, 0, 0), and then inserts the first value, 1, after it. 1 becomes the current position.
 * 0 (2) 1: the spinlock steps forward three times (0, 1, 0), and then inserts the second value, 2, after it. 2 becomes the current position.
 * 0  2 (3) 1: the spinlock steps forward three times (1, 0, 2), and then inserts the third value, 3, after it. 3 becomes the current position.
 *
 * And so on:
 * 0  2 (4) 3  1
 * 0 (5) 2  4  3  1
 * 0  5  2  4  3 (6) 1
 * 0  5 (7) 2  4  3  6  1
 * 0  5  7  2  4  3 (8) 6  1
 * 0 (9) 5  7  2  4  3  8  6  1
 */
int part1(int num_steps) {
    list<int> buffer;
    buffer.push_back(0);
    // print_buffer(0, buffer);
    list<int>::iterator it = buffer.begin();
    int current_position = 0;
    for (int value = 1; value <= 2017; value++) {
        current_position = ((current_position + num_steps) % buffer.size()) + 1;
        // cout << "current_position=" << current_position << endl;
        it = buffer.begin();
        for (int i = 0; i < current_position; i++) {
            it++;
        }
        buffer.insert(it, value);
        // print_buffer(value, buffer);
    }
    return *it;
}


int part2(int num_steps) {
    int zero_position = 0;
    int current_position = 0;
    int size = 1;
    int value_after_zero;
    for (int value = 1; value <= 50000000; value++) {
        current_position = (current_position + num_steps) % size;
        if (current_position < zero_position) {
            zero_position++;
        } else if (current_position == zero_position) {
            value_after_zero = value;
        }
        current_position++;
        size++;
    }
    return value_after_zero;
}


int main() {
    cout << "Day 17!" << endl;
    int num_steps;
    cin >> num_steps;
    cout << "Part 1: " << part1(num_steps) << endl;
    cout << "Part 2: " << part2(num_steps) << endl;
}
