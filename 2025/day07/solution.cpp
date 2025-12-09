
#include <iostream>
#include <map>
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

long get_num_timelines(vector<set<int>> row_splitters, string path_so_far,
        map<pair<int, int>, long>& from_splitter_cache, int row, int col) {
    pair<int, int> cache_key = make_pair(row, col);
    if (from_splitter_cache.count(cache_key)) {
        return from_splitter_cache[cache_key];
    }
    // cout << path_so_far << "\t" << row << "," << col << endl;
    for (; row < row_splitters.size(); row++) {
        // Hit
        if (row_splitters[row].count(col)) {
            from_splitter_cache[cache_key] = get_num_timelines(row_splitters, path_so_far + "L", from_splitter_cache, row+1, col-1) +
                get_num_timelines(row_splitters, path_so_far + "R", from_splitter_cache, row+1, col+1);
            return from_splitter_cache[cache_key];
        }
    }
    // No more hits from this starting path, this is the end for this timeline
    from_splitter_cache[cache_key] = 1;
    return from_splitter_cache[cache_key];
}

long solution2() {
    // First read in the whole thing
    pair<int, vector<set<int>>> input = read_input();
    int start = input.first;
    vector<set<int>> row_splitters = input.second;
    map<pair<int, int>, long> from_splitter_cache;
    return get_num_timelines(row_splitters, "", from_splitter_cache, 0, start);
}

int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
