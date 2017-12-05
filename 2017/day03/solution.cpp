/**
 * $ g++ solution.cpp && ./a.out
 */
#include <iostream>
#include <stdlib.h>

using namespace std;


enum Direction {right, up, left, down};


class Stepper {
    private:
        int x, y, step, step_size, step_size_count;
        Direction direction;
        void turn();
    public:
        int count;
        Stepper();
        void do_step();
        int get_distance();
};

Stepper::Stepper() {
    count = 1;
    x = 0;
    y = 0;
    step = 0;
    step_size = 1;
    step_size_count = 0;
    direction = Direction::right;
}

void Stepper::turn() {
    switch (direction) {
        case Direction::right:
            direction = Direction::up;
            return;
        case Direction::up:
            direction = Direction::left;
            return;
        case Direction::left:
            direction = Direction::down;
            return;
        case Direction::down:
            direction = Direction::right;
            return;
        default:
            break;
    }
}

void Stepper::do_step() {
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
        default:
            break;
    }
    step++;
    if (step == step_size) {
        step = 0;
        turn();
        step_size_count++;
        if (step_size_count == 2) {
            step_size++;
            step_size_count = 0;
        }
    }
    count++;
}


int Stepper::get_distance() {
    return abs(x) + abs(y);
}


int part1(int input) {
    Stepper stepper;
    while (stepper.count < input) {
        stepper.do_step();
    }
    return stepper.get_distance();
}


int main() {
    cout << "Day 3!\n";
    // cout << part1(1) << endl;
    // cout << part1(12) << endl;
    // cout << part1(23) << endl;
    // cout << part1(1024) << endl;
    cout << part1(289326) << endl;
}
