
// For abs()
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
// For pair
#include <utility>
#include <vector>

using namespace std;

vector<pair<long, long>> get_tiles() {
    vector<pair<long, long>> tiles;
    string group;
    while (getline(cin, group)) {
        stringstream ss(group);
        string str_start, str_stop;
        getline(ss, str_start, ',');
        getline(ss, str_stop, ',');
        long x, y;
        x = stol(str_start);
        y = stol(str_stop);
        tiles.push_back(make_pair(x, y));
    }
    return tiles;
}

long solution1() {
    vector<pair<long, long>> tiles = get_tiles();
    long winner = 0;
    for (const auto& a : tiles) {
        for (const auto& b : tiles) {
            long area = abs(a.first - b.first + 1) * abs(a.second - b.second + 1);
            if (area > winner) {
                // cout << a.first << "," << a.second << " " << b.first << "," << b.second << " " << area << endl;
                winner = area;
            }
        }
    }
    return winner;
}

int solution2() {
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
