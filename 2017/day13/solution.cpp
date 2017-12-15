/**
 * Day 13!
 * Part 1: 1612
 */

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;


class Layer {
    private:
        int depth;
        int range;
        int scanner_position = 0;
        int direction = 1;
    public:
        Layer(int depth, int range) {
            this->depth = depth;
            this->range = range;
        }
        int get_depth() {
            return depth;
        }
        int get_scanner_position() {
            return scanner_position;
        }
        void step() {
            if (scanner_position + direction >= range || scanner_position + direction < 0) {
                direction *= -1;
            }
            scanner_position += direction;
        }
        bool is_caught() {
            return scanner_position == 0;
        }
        int get_severity() {
            return depth * range;
        }
};


unordered_map<int, Layer*> depth_layers;


/**
 * 0: 3
 * 1: 2
 * 4: 4
 * 6: 4
 */
int handle_line(string line) {
    stringstream stream(line);
    int depth, range;
    string buffer;
    stream >> buffer;
    buffer = buffer.substr(0, buffer.length()-1);
    depth = stoi(buffer);
    stream >> buffer;
    range = stoi(buffer);
    Layer* layer = new Layer(depth, range);
    depth_layers.insert(make_pair(depth, layer));
    return depth;
}


int part1(int max_depth) {
    int severity = 0;
    Layer* layer;
    for (int current_depth = 0; current_depth <= max_depth; current_depth++) {
        // cout << "current_depth " << current_depth << endl;
        auto result = depth_layers.find(current_depth);
        if (result != depth_layers.end()) {
            layer = result->second;
            // cout << "\tHit layer! Scanner position: " << layer->get_scanner_position() << endl;
            if (layer->is_caught()) {
                severity += layer->get_severity();
                // cout << "\t\tCaught! Total severity: " << severity << endl;
            }
        } else {
            // cout << "\tMissed layer" << endl;
        }
        // Step all the layers
        unordered_map<int, Layer*>::iterator it = depth_layers.begin();
        while (it != depth_layers.end()) {
            layer = it->second;
            // cout << "Stepping layer at depth " << layer->get_depth() << " - scanner position " << layer->get_scanner_position() << endl;
            layer->step();
            it++;
        }
    }
    return severity;
}


int main() {
    cout << "Day 13!" << endl;
    string line;
    int max_depth = 0;
    while (getline(cin, line)) {
        max_depth = handle_line(line);
    }
    // cout << "max_depth " << max_depth << endl;
    cout << "Part 1: " << part1(max_depth) << endl;
}
