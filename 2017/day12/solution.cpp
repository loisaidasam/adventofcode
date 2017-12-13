

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;


vector<unordered_set<int>> sets;


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


int part1() {
    unordered_set<int> connected;
    int set_size;
    do {
        set_size = connected.size();
        // cout << "set_size: " << set_size << endl;
        // First find the set containing `0`
        if (set_size == 0) {
            for (int i = 0; i < sets.size(); i++) {
                auto search = sets[i].find(0);
                // Found it!
                if (search != sets[i].end()) {
                    connected = sets[i];
                    break;
                }
            }
            if (connected.size() == 0) {
                // OH NOH!
                throw 100;
            }
        }
        // Otherwise look through all sets for any intersection
        for (int i = 0; i < sets.size(); i++) {
            for (auto item_search = connected.begin(); item_search != connected.end(); item_search++) {
                auto search = sets[i].find(*item_search);
                // Found it, merge this set in
                if (search != sets[i].end()) {
                    // https://stackoverflow.com/questions/7089494/merge-multiple-sets-elements-in-a-single-set/7089564#7089564
                    connected.insert(sets[i].begin(), sets[i].end());
                    break;
                }
            }
        }
    } while (set_size != connected.size());
    return set_size;
}


int main() {
    cout << "Day 12!" << endl;
    string line;
    while (getline(cin, line)) {
        handle_line(line);
    }
    cout << "Part 1: " << part1() << endl;
}
