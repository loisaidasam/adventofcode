/**
 * $ g++ solution.cpp && ./a.out
 */
#include <iostream>
#include <stdlib.h>

using namespace std;


enum Direction {right, up, left, down};


Direction turn(Direction direction) {
    switch (direction) {
        case Direction::right:
            return Direction::up;
        case Direction::up:
            return Direction::left;
        case Direction::left:
            return Direction::down;
        case Direction::down:
            return Direction::right;
    }
}

int get_distance(int x, int y) {
    return abs(x) + abs(y);
}


int part1(int input) {
    int x = 0;
    int y = 0;
    int count = 1;
    Direction direction = Direction::right;
    int step_size = 1;
    while (true) {
        for (int i = 0; i < 2; i++) {
            for (int step = 0; step < step_size; step++) {
                // cout << x << " " << y << " " << direction << endl;
                if (count == input) {
                    return get_distance(x, y);
                }
                switch (direction) {
                    case Direction::right:
                        x += 1;
                        break;
                    case Direction::up:
                        y += 1;
                        break;
                    case Direction::left:
                        x -= 1;
                        break;
                    case Direction::down:
                        y -= 1;
                        break;
                }
                count++;
            }
            direction = turn(direction);
        }
        step_size++;
    }
}


int main() {
    cout << "Day 3!\n";
    // cout << part1(1) << endl;
    // cout << part1(12) << endl;
    // cout << part1(23) << endl;
    // cout << part1(1024) << endl;
    cout << part1(289326) << endl;
}
