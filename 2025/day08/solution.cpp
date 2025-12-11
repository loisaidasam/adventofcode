
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <sstream>
// For pair
#include <utility>
#include <vector>

using namespace std;


// Test
// const int NUM_CONNECTIONS = 10;
// Run
const int NUM_CONNECTIONS = 1000;

const int NUM_LARGEST_CIRCUITS = 3;


// Usage:
// Position p1 = {10, 20, 30};
// Position p2 = {5, 15, 25};
// p1.x = 100;
struct Position {
    int x;
    int y;
    int z;
};


void print_pos(Position p) {
    cout << "(x=" << p.x << " y=" << p.y << " z=" << p.z << ")";
}


vector<Position> read_positions() {
    vector<Position> positions;
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string x, y, z;
        getline(ss, x, ',');
        getline(ss, y, ',');
        getline(ss, z, ',');
        positions.push_back({stoi(x), stoi(y), stoi(z)});
    }
    return positions;
}


// We'll skip square rooting because relative distances will be the same
long distance_squared(const Position p1, const Position p2) {
    long dx = p2.x - p1.x;
    long dy = p2.y - p1.y;
    long dz = p2.z - p1.z;
    return dx*dx + dy*dy + dz*dz;
}


struct Node {
    int i;
    set<int> edges;
    Position position;
};


set<int> traverse_circuit(Node boxes[], int i) {
    // cout << "traverse_circuit[" << i << "] ";
    set<int> seen;
    set<int> boxes_to_check;
    boxes_to_check.insert(i);
    while (boxes_to_check.size()) {
        for (auto it = boxes_to_check.begin(); it != boxes_to_check.end();) {
            i = *it;
            // cout << i << endl;
            seen.insert(i);
            for (int j : boxes[i].edges) {
                // cout << "\tedge: " << j;
                if (! seen.count(j)) {
                    // cout << " new!";
                    boxes_to_check.insert(j);
                }
                // cout << endl;
            }
            // Apparently this is how you advance the iterator?
            it = boxes_to_check.erase(it);
        }
    }
    return seen;
}


int solution1() {
    vector<Position> positions = read_positions();
    const int NUM_BOXES = positions.size();
    Node boxes[NUM_BOXES];
    vector<pair<long, pair<int, int>>> sims;
    for (int i = 0; i < NUM_BOXES; i++) {
        // cout << i << ": ";
        // print_pos(positions[i]);
        // cout << endl;
        boxes[i].i = i;
        for (int j = i+1; j < NUM_BOXES; j++) {
            long distance = distance_squared(positions[i], positions[j]);
            sims.push_back(make_pair(distance, make_pair(i, j)));
        }
    }
    sort(sims.begin(), sims.end());
    for (int i = 0; i < NUM_CONNECTIONS; i++) {
        // cout << "sim " << i << ": " << sims[i].second.first << "=";
        // print_pos(positions[sims[i].second.first]);
        // cout << ", " << sims[i].second.second << "=";
        // print_pos(positions[sims[i].second.second]);
        // cout << " sim=" << sims[i].first << endl;
        int p1 = sims[i].second.first;
        int p2 = sims[i].second.second;
        boxes[p1].edges.insert(boxes[p2].i);
        boxes[p2].edges.insert(boxes[p1].i);
    }
    set<int> seen;
    vector<int> circuit_sizes;
    for (int i = 0; i < NUM_BOXES; i++) {
        set<int> circuit = traverse_circuit(boxes, i);
        // Dereferenced w/ *
        int circuit_element = *circuit.begin();
        // cout << "circuit[" << i << "] len=" << circuit.size() << " contains {" << circuit_element << " ..." << endl;
        // Only add unseen circuits
        if (! seen.count(circuit_element)) {
            int num_circuit_boxes = circuit.size();
            // cout << num_circuit_boxes << endl;
            circuit_sizes.push_back(num_circuit_boxes);
            seen.insert(circuit.begin(), circuit.end());
        }
        // cout << "\tlen(seen)=" << seen.size() << endl;
    }
    sort(circuit_sizes.begin(), circuit_sizes.end());
    reverse(circuit_sizes.begin(), circuit_sizes.end());
    long result = circuit_sizes[0];
    for (int i = 1; i < NUM_LARGEST_CIRCUITS; i++) {
        result *= circuit_sizes[i];
    }
    return result;
}


long solution2() {
    vector<Position> positions = read_positions();
    const int NUM_BOXES = positions.size();
    Node boxes[NUM_BOXES];
    vector<pair<long, pair<int, int>>> sims;
    for (int i = 0; i < NUM_BOXES; i++) {
        // cout << i << ": ";
        // print_pos(positions[i]);
        // cout << endl;
        boxes[i].i = i;
        boxes[i].position = positions[i];
        for (int j = i+1; j < NUM_BOXES; j++) {
            long distance = distance_squared(positions[i], positions[j]);
            sims.push_back(make_pair(distance, make_pair(i, j)));
        }
    }
    sort(sims.begin(), sims.end());
    for (int i = 0; i < sims.size(); i++) {
        // cout << "sim " << i << ": " << sims[i].second.first << "=";
        // print_pos(positions[sims[i].second.first]);
        // cout << ", " << sims[i].second.second << "=";
        // print_pos(positions[sims[i].second.second]);
        // cout << " sim=" << sims[i].first << endl;
        int p1 = sims[i].second.first;
        int p2 = sims[i].second.second;
        boxes[p1].edges.insert(boxes[p2].i);
        boxes[p2].edges.insert(boxes[p1].i);
        set<int> circuit = traverse_circuit(boxes, 0);
        if (circuit.size() == NUM_BOXES) {
            long x1 = boxes[p1].position.x;
            long x2 = boxes[p2].position.x;
            return x1 * x2;
        }
    }
    // Getting here would be weird - we should never actually exhaust ALL sims...
    return -1;
}

int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
