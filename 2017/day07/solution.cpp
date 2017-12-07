/**
 */
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>

using namespace std;

// Map of child to its parent
unordered_map<string, string> parents;


/**
 * ktlj (57)
 * fwft (72) -> ktlj, cntj, xhth
 */
void handle_line(string line) {
    stringstream stream(line);
    string word, parent, child;
    for (int counter = 0; stream >> word; counter++) {
        switch (counter) {
            case 0:
                // Parent: fwft
                parent = word;
                // cout << "Parent " << parent << endl;
                break;
            case 1:
                // Weight: (72)
            case 2:
                // Arrow: ->
                break;
            default:
                // Child, potentially with trailing comma
                //   ktlj, cntj, xhth
                if (word[word.length() - 1] == ',') {
                    word = word.substr(0, word.length() - 1);
                }
                // cout << "Child " << word << endl;
                parents.insert(make_pair(word, parent));
        }
    }
}


string part1() {
    // Grab any item's parent to start
    string item = parents.begin()->second;
    while (true) {
        // Search for that parent's parent
        auto search = parents.find(item);
        // Once an item doesn't have a parent, we're at the root
        if (search == parents.end()) {
            return item;
        }
        // Otherwise keep going up the tree
        item = search->second;
    }
}


int main() {
    cout << "Day 7!" << endl;
    string line;
    while (getline(cin, line)) {
        handle_line(line);
    }
    cout << part1() << endl;
}
