/**
 * $ g++ solution.cpp && echo '{}' |  ./a.out 
 * Day 9!
 * Part 1: 1
 * Part 2: 0
 *
 * $ g++ solution.cpp && echo '{<some-gahhbage>}' |  ./a.out 
 * Day 9!
 * Part 1: 1
 * Part 2: 13
 *
 * $ g++ solution.cpp &&  ./a.out < input.txt 
 * Day 9!
 * Part 1: 8337
 * Part 2: 4330
 */

#include <iostream>
#include <string>

using namespace std;


bool verbose = false;

int score = 0;
int score_garbage = 0;

/**
 * {}, score of 1.
 * {{{}}}, score of 1 + 2 + 3 = 6.
 * {{},{}}, score of 1 + 2 + 2 = 5.
 * {{{},{},{{}}}}, score of 1 + 2 + 3 + 3 + 3 + 4 = 16.
 * {<a>,<a>,<a>,<a>}, score of 1.
 * {{<ab>},{<ab>},{<ab>},{<ab>}}, score of 1 + 2 + 2 + 2 + 2 = 9.
 * {{<!!>},{<!!>},{<!!>},{<!!>}}, score of 1 + 2 + 2 + 2 + 2 = 9.
 * {{<a!>},{<a!>},{<a!>},{<ab>}}, score of 1 + 2 = 3.
 */
void parse_line(string line) {
    if (verbose) {
        cout << "line: " << line << endl;
    }
    bool garbage = false;
    int group = 0;
    bool canceled = false;
    for (int i = 0; i < line.length(); i++) {
        char item = line[i];
        if (verbose) {
            cout << item << " ";
        }
        if (canceled) {
            if (verbose) {
                cout << "canceled finished" << endl;
            }
            canceled = false;
            continue;
        }
        if (item == '!') {
            if (verbose) {
                cout << "canceled" << endl;
            }
            canceled = true;
            continue;
        }
        if (garbage) {
            if (verbose) {
                cout << "garbage";
            }
            if (item == '>') {
                if (verbose) {
                    cout << " - OVER!";
                }
                garbage = false;
            } else {
                score_garbage++;
                if (verbose) {
                    cout << " (score_garbage " << score_garbage << ")";
                }
            }
            if (verbose) {
                cout << endl;
            }
            continue;
        }
        if (item == '<') {
            if (verbose) {
                cout << "start garbage" << endl;
            }
            garbage = true;
            continue;
        }
        if (item == '{') {
            group++;
            score += group;
            if (verbose) {
                cout << "start group " << group << " (score " << score << ")" << endl;
            }
            continue;
        }
        if (item == '}') {
            if (verbose) {
                cout << "end group " << group << endl;
            }
            group--;
            continue;
        }
        if (verbose) {
            cout << "no op" << endl;
        }
    }
}

int part1() {
    return score;
}

int part2() {
    return score_garbage;
}

int main() {
    cout << "Day 9!" << endl;
    string line;
    cin >> line;
    parse_line(line);
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}
