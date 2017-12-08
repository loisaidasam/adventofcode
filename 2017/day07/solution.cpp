/**
 */
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Map of child to its parent
unordered_map<string, string> parents;

// Map of each parent to a vector of its children
unordered_map<string, vector<string>> children;

// Map of each item to its weight
unordered_map<string, int> weights;


/**
 * ktlj (57)
 * fwft (72) -> ktlj, cntj, xhth
 */
void handle_line(string line) {
    stringstream stream(line);
    string word, parent, child;
    vector<string> parent_children;
    for (int counter = 0; stream >> word; counter++) {
        switch (counter) {
            case 0: {
                // Parent: fwft
                parent = word;
                // cout << "Parent " << parent << endl;
                break;
            }
            case 1: {
                // Weight: (72)
                word = word.substr(1, word.length() - 2);
                int weight = stoi(word);
                weights.insert(make_pair(parent, weight));
                break;
            }
            case 2: {
                // Arrow: ->
                break;
            }
            default: {
                // Child, potentially with trailing comma
                //   ktlj, cntj, xhth
                child = word;
                if (child[word.length() - 1] == ',') {
                    child = child.substr(0, child.length() - 1);
                }
                // cout << "Child " << child << endl;
                parents.insert(make_pair(child, parent));
                parent_children.push_back(child);
                break;
            }
        }
    }
    children.insert(make_pair(parent, parent_children));
}


string get_root() {
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


string part1() {
    return get_root();
}


int get_item_weight(string item) {
    // All items should have a weight
    auto search = weights.find(item);
    return search->second;
}


/**
 * Recursively get weight of node plus all subnode weights
 */
int get_item_tree_weight(string item) {
    int weight = get_item_weight(item);
    auto children_search = children.find(item);
    if (children_search == children.end()) {
        // No children, just return our weight
        return weight;
    }
    for (int i = 0; i < children_search->second.size(); i++) {
        string child = children_search->second[i];
        weight += get_item_tree_weight(child);
    }
    return weight;
}


void print_tree(string item, int depth) {
    for (int i = 0; i < depth; i++) {
        cout << " ";
    }
    int weight_item = get_item_weight(item);
    int weight_item_tree = get_item_tree_weight(item);
    cout << item << " / " << weight_item << " / " << weight_item_tree << endl;
    auto children_search = children.find(item);
    // No children
    if (children_search == children.end()) {
        return;
    }
    string child;
    for (int i = 0; i < children_search->second.size(); i++) {
        child = children_search->second[i];
        print_tree(child, depth + 1);
    }
}


/**
 * Return empty if all children have the same weight, otherwise return the child
 * with the different weight
 */
string find_children_tree_weights_mismatch(string item) {
    string child_mismatch;
    auto children_search = children.find(item);
    // No children
    if (children_search == children.end()) {
        return child_mismatch;
    }
    // Find which child has the mismatch
    int value0 = -1;
    int value0_matches = 0;
    int value1 = -1;
    int value1_matches = 0;
    string value0_child, value1_child;
    for (int i = 0; i < children_search->second.size(); i++) {
        string child = children_search->second[i];
        int child_weight = get_item_weight(child);
        // Nothing initialized yet
        if (value0 == -1 && value1 == -1) {
            value0 = child_weight;
            value0_matches++;
            value0_child = child;
            continue;
        }
        // value0 initialized, value1 not initialized
        if (value1 == -1) {
            // value0 dupe
            if (child_weight == value0) {
                value0_matches++;
            } else {
                value1 = child_weight;
                value1_matches++;
                value1_child = child;
            }
            continue;
        }
        // value0 and value1 are both initialized
        // whichever one matches, the other one is the mismatch
        if (child_weight == value0) {
            return value1_child;
        } else {
            return value0_child;
        }
    }
    // value1 set, which means there was a mismatch
    if (value1 != -1) {
        // More value0 matches than value1 matches, value1 is the odd man out
        if (value0_matches > value1_matches) {
            return value1_child;
        }
        // More value1 matches than value0 matches, value0 is the odd man out
        return value0_child;
    }
    // Otherwise there was no mismatch
    return child_mismatch;
}


string part2() {
    string item = get_root();
    string item_mismatch;
    while (true) {
        item_mismatch = find_children_tree_weights_mismatch(item);
        cout << "Node: " << item << " mismatch: " << item_mismatch << endl;
        if (item_mismatch.empty()) {
            return item;
        }
        item = item_mismatch;
    }
}


int main() {
    cout << "Day 7!" << endl;
    string line;
    while (getline(cin, line)) {
        handle_line(line);
    }
    cout << part1() << endl;
    print_tree(get_root(), 0);
    cout << part2() << endl;
}
