
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <unordered_map>
// TODO:
// // For pair
// #include <utility>
#include <vector>

using namespace std;


// Device d = {"device_name", {}, {}};
struct Device {
    string name;
    set<string> inputs;
    set<string> outputs;
};

/**
 * Note: duds is by reference, a shared global cache
 */
int find_paths(unordered_map<string, Device> devices, set<string> seen, set<string>& duds, string current_name) {
    // // Debugging
    // for (string seen_item : seen) {
    //     cout << seen_item << " ";
    // }
    // cout << current_name << endl;
    // cout << "\tduds: ";
    // for (string dud : duds) {
    //     cout << dud << " ";
    // }
    // cout << endl;
    Device device = devices[current_name];
    seen.insert(current_name);
    int num_paths = 0;
    for (string input : device.inputs) {
        if (input == "you") {
            // cout << "found! ";
            // for (string seen_item : seen) {
            //     cout << seen_item << " ";
            // }
            // cout << endl;
            num_paths++;
        }
        // Test the path if it hasn't been seen and it isn't a dud
        if (! seen.count(input) && ! duds.count(input)) {
            int added = find_paths(devices, seen, duds, input);
            if (added == 0) {
                // Dud
                duds.insert(input);
            } else {
                num_paths += added;
            }
        }
    }
    return num_paths;
}

/**
 * aaa you hhh
 * you bbb ccc
 * bbb ddd eee
 * ccc ddd eee fff
 * ddd ggg
 * eee out
 * fff out
 * ggg out
 * hhh ccc fff iii
 * iii out
 *
 * you bbb ddd ggg out
 * you ccc ddd ggg out
 * you bbb eee out
 * you ccc eee out
 * you ccc fff out
 */
int solution1() {
    unordered_map<string, Device> devices;
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string input, output;
        getline(ss, input, ' ');
        
        if (! devices.count(input)) {
            devices[input] = {input, {}, {}};
        }
        Device& device = devices[input];
        while (getline(ss, output, ' ')) {
            device.outputs.insert(output);
            if (! devices.count(output)) {
                devices[output] = {output, {}, {}};
            }
            Device& device_out = devices[output];
            device_out.inputs.insert(input);
        }
    }
    // Sanity, make sure we have the correct inputs/outputs persisted
    // for (auto& pair : devices) {
    //     string key = pair.first;
    //     Device& device = pair.second;
    //     cout << key << endl << "\tinputs: ";
    //     for (string input : device.inputs) {
    //         cout << input << " ";
    //     }
    //     cout << endl << "\toutputs: ";
    //     for (string output : device.outputs) {
    //         cout << output << " ";
    //     }
    //     cout << endl;
    // }
    set<string> seen, duds;
    return find_paths(devices, seen, duds, "out");
}

int solution2() {
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
