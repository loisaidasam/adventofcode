/**
 * $ g++ solution.cpp && ./a.out
 * Day 3!
 * 419
 * 295229
 */
#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;


enum Direction {right, up, left, down};


class Stepper {
    private:
        bool do_paint;
        int x, y, step, step_size, step_size_count;
        Direction direction;
        unordered_map<string, int> paint_map;
        void turn();
        string get_paint_key(int, int);
        int get_paint_value(int, int);
        void paint_square();
    public:
        int count;
        Stepper(bool);
        void do_step();
        int get_distance();
        int get_paint_value();
};

Stepper::Stepper(bool do_paint) {
    this->do_paint = do_paint;
    count = 1;
    x = 0;
    y = 0;
    step = 0;
    step_size = 1;
    step_size_count = 0;
    direction = Direction::right;
    if (do_paint) {
        paint_square();
    }
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

string Stepper::get_paint_key(int paint_x, int paint_y) {
    return to_string(paint_x) + " " + to_string(paint_y);
}

int Stepper::get_paint_value(int paint_x, int paint_y) {
    string paint_key = get_paint_key(paint_x, paint_y);
    auto result = paint_map.find(paint_key);
    if (result == paint_map.end()) {
        return 0;
    }
    return result->second;
}

void Stepper::paint_square() {
    string paint_key = get_paint_key(x, y);
    if (x == 0 && y == 0) {
        paint_map.insert(make_pair(paint_key, 1));
        return;
    }
    int total = 0;
    total += get_paint_value(x + 1, y);
    total += get_paint_value(x + 1, y + 1);
    total += get_paint_value(x, y + 1);
    total += get_paint_value(x - 1, y + 1);
    total += get_paint_value(x - 1, y);
    total += get_paint_value(x - 1, y - 1);
    total += get_paint_value(x, y - 1);
    total += get_paint_value(x + 1, y - 1);
    paint_map.insert(make_pair(paint_key, total));
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
    if (do_paint) {
        paint_square();
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


int Stepper::get_paint_value() {
    return get_paint_value(x, y);
}


int part1(int input) {
    Stepper stepper(false);
    while (stepper.count < input) {
        stepper.do_step();
    }
    return stepper.get_distance();
}


int part2(int input) {
    Stepper stepper(true);
    while (true) {
        stepper.do_step();
        int paint_value = stepper.get_paint_value();
        if (paint_value > input) {
            return paint_value;
        }
    }
    return 0;
}


int main() {
    cout << "Day 3!\n";
    // cout << part1(1) << endl;
    // cout << part1(12) << endl;
    // cout << part1(23) << endl;
    // cout << part1(1024) << endl;
    cout << part1(289326) << endl;
    cout << part2(289326) << endl;
}
