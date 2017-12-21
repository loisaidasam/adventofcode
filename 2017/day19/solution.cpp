
#include <iostream>
#include <vector>

using namespace std;


enum Direction {DOWN, RIGHT, UP, LEFT};


vector<string> lines;


void handle_line(string line) {
    lines.push_back(line);
}


string part1() {
    const int ROWS = lines.size();
    // cout << ROWS << " lines" << endl;
    const int COLS = lines[0].length();
    // cout << COLS << " width" << endl;

    char grid[ROWS][COLS];
    int row, col;
    for (row = 0; row < lines.size(); row++) {
        for (col = 0; col < lines[0].length(); col++) {
            grid[row][col] = lines[row][col];
            // cout << row << "," << col << " square: '" << grid[row][col] << "'" << endl;
        }
    }

    row = 0;
    for (col = 0; col < COLS; col++) {
        if (grid[row][col] == '|') {
            // cout << "Starting on col " << col << endl;
            break;
        }
    }

    Direction direction = Direction::DOWN;
    char square = grid[row][col];
    string letters = "";

    while (true) {
        // cout << row << "," << col << " square: '" << square << "' / Direction: " << direction << endl;
        switch (direction) {
            case (Direction::DOWN): {
                row++;
                break;
            }
            case (Direction::RIGHT): {
                col++;
                break;
            }
            case (Direction::UP): {
                row--;
                break;
            }
            case (Direction::LEFT): {
                col--;
                break;
            }
        }
        square = grid[row][col];
        if (square == ' ') {
            // cout << "Done!" << endl;
            return letters;
        }
        if (square >= 'A' && square <= 'Z') {
            // cout << "Letter" << endl;
            letters += square;
            continue;
        }
        if (square != '+') {
            continue;
        }
        if (direction == Direction::UP || direction == Direction::DOWN) {
            if (col > 0 && grid[row][col-1] != ' ') {
                direction = Direction::LEFT;
            } else if (col < COLS-1 && grid[row][col+1] != ' ') {
                direction = Direction::RIGHT;
            } else {
                cout << "Not sure what to do!" << endl;
                throw 400;
            }
            continue;
        }
        if (direction == Direction::LEFT || direction == Direction::RIGHT) {
            if (row > 0 && grid[row-1][col] != ' ') {
                direction = Direction::UP;
            } else if (row < ROWS-1 && grid[row+1][col] != ' ') {
                direction = Direction::DOWN;
            } else {
                cout << "Not sure what to do!" << endl;
                throw 401;
            }
            continue;
        }
        cout << "WAT!?" << endl;
    }
    return letters;
}


int part2() {
    const int ROWS = lines.size();
    // cout << ROWS << " lines" << endl;
    const int COLS = lines[0].length();
    // cout << COLS << " width" << endl;

    char grid[ROWS][COLS];
    int row, col;
    for (row = 0; row < lines.size(); row++) {
        for (col = 0; col < lines[0].length(); col++) {
            grid[row][col] = lines[row][col];
            // cout << row << "," << col << " square: '" << grid[row][col] << "'" << endl;
        }
    }

    row = 0;
    for (col = 0; col < COLS; col++) {
        if (grid[row][col] == '|') {
            // cout << "Starting on col " << col << endl;
            break;
        }
    }

    Direction direction = Direction::DOWN;
    char square = grid[row][col];
    int steps = 1;

    while (true) {
        // cout << row << "," << col << " square: '" << square << "' / Direction: " << direction << endl;
        switch (direction) {
            case (Direction::DOWN): {
                row++;
                break;
            }
            case (Direction::RIGHT): {
                col++;
                break;
            }
            case (Direction::UP): {
                row--;
                break;
            }
            case (Direction::LEFT): {
                col--;
                break;
            }
        }
        square = grid[row][col];
        if (square == ' ') {
            // cout << "Done!" << endl;
            return steps;
        }
        steps++;
        if (square >= 'A' && square <= 'Z') {
            // cout << "Letter" << endl;
            continue;
        }
        if (square != '+') {
            continue;
        }
        if (direction == Direction::UP || direction == Direction::DOWN) {
            if (col > 0 && grid[row][col-1] != ' ') {
                direction = Direction::LEFT;
            } else if (col < COLS-1 && grid[row][col+1] != ' ') {
                direction = Direction::RIGHT;
            } else {
                cout << "Not sure what to do!" << endl;
                throw 400;
            }
            continue;
        }
        if (direction == Direction::LEFT || direction == Direction::RIGHT) {
            if (row > 0 && grid[row-1][col] != ' ') {
                direction = Direction::UP;
            } else if (row < ROWS-1 && grid[row+1][col] != ' ') {
                direction = Direction::DOWN;
            } else {
                cout << "Not sure what to do!" << endl;
                throw 401;
            }
            continue;
        }
        cout << "WAT!?" << endl;
    }
    return steps;
}


int main() {
    cout << "Day 19!" << endl;
    string line;
    while (getline(cin, line)) {
        handle_line(line);
    }
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}
