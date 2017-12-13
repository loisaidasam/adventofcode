/**
 * $ g++ solution.cpp && ./a.out < input.txt 
 * Day 12!
 * Part 1: 288
 * Part 2: 211
 */

#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>

using namespace std;

deque<unordered_set<int>> sets;


/**
 * 0 <-> 2
 * 1 <-> 1
 * 2 <-> 0, 3, 4
 * 3 <-> 2, 4
 * 4 <-> 2, 3, 6
 * 5 <-> 6
 * 6 <-> 4, 5
 */
void handle_line(string line) {
    unordered_set<int> set;
    stringstream stream(line);
    string word;
    for (int i = 0; stream >> word; i++) {
        switch(i) {
            case 0: {
                set.insert(stoi(word));
                break;
            }
            case 1: {
                // <->
                break;
            }
            default: {
                if (word[word.length()-1] == ',') {
                    word = word.substr(0, word.length() - 1);
                }
                set.insert(stoi(word));
            }
        }
    }
    sets.push_back(set);
}


/**
 * Look for another set with overlapping elements and merge this set in.
 * Returns whether a merge occured;
 */
bool merge_set(unordered_set<int> set) {
    for (int i = 0; i < sets.size(); i++) {
        for (auto item_search = set.begin(); item_search != set.end(); item_search++) {
            auto search = sets[i].find(*item_search);
            // Found it, merge this set in
            if (search != sets[i].end()) {
                // https://stackoverflow.com/questions/7089494/merge-multiple-sets-elements-in-a-single-set/7089564#7089564
                sets[i].insert(set.begin(), set.end());
                return true;
            }
        }
    }
    // Didn't merge. Push onto back of sets.
    sets.push_back(set);
    return false;
}


/**
 * http://www.cplusplus.com/reference/deque/deque/
 */
void build_groups() {
    unordered_set<int> set;
    int num_merge_fails = 0;
    while (num_merge_fails < sets.size()) {
        set = sets[0];
        sets.pop_front();
        // Only one set left!
        if (sets.size() == 0) {
            sets.push_back(set);
            return;
        }
        if (merge_set(set)) {
            num_merge_fails = 0;
        } else {
            num_merge_fails++;
        }
    }
}


int part1() {
    for (int i = 0; i < sets.size(); i++) {
        auto search = sets[i].find(0);
        // Found it, merge this set in
        if (search != sets[i].end()) {
            return sets[i].size();
        }
    }
    return 0;
}


int part2() {
    return sets.size();
}


int main() {
    cout << "Day 12!" << endl;
    string line;
    while (getline(cin, line)) {
        handle_line(line);
    }
    build_groups();
    cout << "Part 1: " << part1() << endl;
    cout << "Part 2: " << part2() << endl;
}
