
#include <iostream>
#include <set>
#include <string>
// For pair
#include <utility>
#include <vector>

using namespace std;

int solution1() {
    bool has_start = false;
    set<int> beam_cols;
    string line;
    int beam_splits = 0;
    while (getline(cin, line)) {
        // cout << group << endl;
        if (! has_start) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == 'S') {
                    beam_cols.insert(i);
                    break;
                }
            }
            has_start = true;
        } else {
            for (int i = 0; i < line.length(); i++) {
                // If there's a splitter and an active beam in that col
                if (line[i] == '^' && beam_cols.count(i)) {
                    beam_splits++;
                    beam_cols.erase(i);
                    if (i > 0) {
                        beam_cols.insert(i-1);
                    }
                    if (i < line.length() - 1) {
                        beam_cols.insert(i+1);
                    }
                }
            }
        }
    }
    return beam_splits;
}

pair<int, vector<set<int>>> read_input() {
    int start = -1;
    vector<set<int>> row_splitters;
    string line;
    while (getline(cin, line)) {
        if (start == -1) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == 'S') {
                    start = i;
                    break;
                }
            }
        } else {
            set<int> splitters;
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '^') {
                    splitters.insert(i);
                }
            }
            if (splitters.size()) {
                row_splitters.push_back(splitters);
            }
        }
    }
    return make_pair(start, row_splitters);
}

int get_num_timelines(int start, vector<set<int>> row_splitters, string path_so_far) {
    int row = 0;
    int col = start;
    for (int path_index = 0; path_index < path_so_far.length(); path_index++) {
        bool hit = false;
        for (; row < row_splitters.size(); row++) {
            if (row_splitters[row].count(col)) {
                hit = true;
                if (path_so_far[path_index] == 'L') {
                    col--;
                } else {
                    col++;
                }
                break;
            }
        }
        if (!hit) {
            cerr << "Ran out of rows without hitting any splitters, something is wrong" << endl;
            return 0;
        }
    }
    for (; row < row_splitters.size(); row++) {
        // Hit
        if (row_splitters[row].count(col)) {
            return get_num_timelines(start, row_splitters, path_so_far + "L") + 
                get_num_timelines(start, row_splitters, path_so_far + "R");
        }
    }
    // No more hits from this starting path, this is the end for this timeline
    return 1;
}

int solution2() {
    // First read in the whole thing
    pair<int, vector<set<int>>> input = read_input();
    int start = input.first;
    vector<set<int>> row_splitters = input.second;
    return get_num_timelines(start, row_splitters, "");
}

int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
