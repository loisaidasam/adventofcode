
#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;


int MAX_DIMENSION = 50;


enum class AcreType {NOTHING, OPEN_GROUND, TREE, LUMBERYARD};


AcreType get_acre_type(char input) {
    if (input == '.') {
        return AcreType::OPEN_GROUND;
    }
    if (input == '|') {
        return AcreType::TREE;
    }
    if (input == '#') {
        return AcreType::LUMBERYARD;
    }
    return AcreType::NOTHING;
}


AcreType** read_input () {
    AcreType** area = new AcreType*[MAX_DIMENSION];
    string line;
    for (int row = 0; getline(cin, line); row++) {
        area[row] = new AcreType[MAX_DIMENSION];
        for (int i = 0; i < line.length(); i++) {
            area[row][i] = get_acre_type(line[i]);
        }
    }
    return area;
}


vector<AcreType> get_surrounding_acres(AcreType** area, int x, int y) {
    vector<AcreType> surrounding;
    for (int x_prime = x - 1; x_prime <= x + 1; x_prime++) {
        if (x_prime < 0) {
            continue;
        }
        if (x_prime >= MAX_DIMENSION) {
            break;
        }
        for (int y_prime = y - 1; y_prime <= y + 1; y_prime++) {
            if (y_prime < 0) {
                continue;
            }
            if (y_prime >= MAX_DIMENSION) {
                break;
            }
            if (x == x_prime && y == y_prime) {
                continue;
            }
            surrounding.push_back(area[x_prime][y_prime]);
        }
    }
    return surrounding;
}


AcreType get_next_acre_type(AcreType** area, int x, int y) {
    vector<AcreType> surrounding = get_surrounding_acres(area, x, y);
    AcreType acre_type = area[x][y];
    int found = 0;
    int found_lumberyards = 0;
    int found_trees = 0;
    switch(acre_type) {
        case AcreType::OPEN_GROUND:
            for (int i = 0; i < surrounding.size(); i++) {
                if (surrounding[i] == AcreType::TREE) {
                    found++;
                }
                if (found >= 3) {
                    return AcreType::TREE;
                }
            }
            return AcreType::OPEN_GROUND;
        case AcreType::TREE:
            for (int i = 0; i < surrounding.size(); i++) {
                if (surrounding[i] == AcreType::LUMBERYARD) {
                    found++;
                }
                if (found >= 3) {
                    return AcreType::LUMBERYARD;
                }
            }
            return AcreType::TREE;
        case AcreType::LUMBERYARD:
            for (int i = 0; i < surrounding.size(); i++) {
                if (surrounding[i] == AcreType::LUMBERYARD) {
                    found_lumberyards++;
                } else if (surrounding[i] == AcreType::TREE) {
                    found_trees++;
                }
                if (found_lumberyards > 0 && found_trees > 0) {
                    return AcreType::LUMBERYARD;
                }
            }
            return AcreType::OPEN_GROUND;
        case AcreType::NOTHING:
            return AcreType::NOTHING;
    }
}


AcreType** transition(AcreType** area) {
    AcreType** area_next = new AcreType*[MAX_DIMENSION];
    for (int x = 0; x < MAX_DIMENSION; x++) {
        area_next[x] = new AcreType[MAX_DIMENSION];
        for (int y = 0; y < MAX_DIMENSION; y++) {
            area_next[x][y] = get_next_acre_type(area, x, y);
        }
    }
    return area_next;
}


int get_num_of_type(AcreType** area, AcreType type) {
    int num = 0;
    for (int x = 0; x < MAX_DIMENSION; x++) {
        for (int y = 0; y < MAX_DIMENSION; y++) {
            if (area[x][y] == type) {
                num++;
            }
        }
    }
    return num;
}


int solution1() {
    AcreType** area = read_input();
    for (int minutes = 1; minutes <= 10; minutes++) {
        area = transition(area);
    }
    int num_wood = get_num_of_type(area, AcreType::TREE);
    int num_lumberyards = get_num_of_type(area, AcreType::LUMBERYARD);
    return num_wood * num_lumberyards;
}


/**
 * Using this loop, we found that the value repeats every 28 cycles
 *
 * minute 3853: 191760
 * minute 3854:    191520
 * minute 3855:    189501
 * minute 3856:    189720
 * minute 3857:    187040
 * minute 3858:    189057
 * minute 3859:    189044
 * minute 3860:    190046
 * minute 3861:    189001
 * minute 3862:    192764
 * minute 3863:    192192
 * minute 3864:    194029
 * minute 3865:    193688
 * minute 3866:    195836
 * minute 3867:    193795
 * Cycle found! Size: 15
 * minute 3868:    194256
 * minute 3869:    194820
 * minute 3870:    195160
 * minute 3871:    195702
 * minute 3872:    198702
 * minute 3873:    200208
 * minute 3874:    201492
 * minute 3875:    201722
 * minute 3876:    198950
 * minute 3877:    196308
 * minute 3878:    196196
 * minute 3879:    194598
 * minute 3880:    193795
 * Cycle found! Size: 13
 *
 * So if we were looking for minute 3881, we'd find the value by saying:
 * 3881 - 3880 = 1
 * 1 % 28 = 1
 * the first element of the cycle is 191760
 *
 * So...
 * 1000000000 - 3880 = 999996120
 * 999996120 % 28 = 4
 * The 4th element of the cycle is 189720, which is the correct answer!
 */
int solution2() {
    AcreType** area = read_input();
    int num_wood, num_lumberyards, value;
    unordered_set<int> values_seen;
    vector<int> pattern;
    for (int minutes = 1; minutes <= 1000000000; minutes++) {
        area = transition(area);
        num_wood = get_num_of_type(area, AcreType::TREE);
        num_lumberyards = get_num_of_type(area, AcreType::LUMBERYARD);
        value = num_wood * num_lumberyards;
        // First look for repeat entries
        if (pattern.size() == 0) {
            if (values_seen.find(value) == values_seen.end()) {
                values_seen.insert(value);
                continue;
            }
            cout << "First repeat value of " << value << " found at minute " << minutes << endl;
            pattern.push_back(value);
            continue;
        }
        // Now find the cycle
        cout << "minute " << minutes << ":\t" << value << endl;
        for (int i = 0; i < pattern.size(); i++) {
            if (pattern[i] == value) {
                cout << "Cycle found! Size: " << pattern.size() << endl;
                pattern.clear();
                break;
            }
        }
        pattern.push_back(value);
    }
    return 0;
}


int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
}
