
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;


/**
 * seeds: 79 14 55 13
 *
 * seed-to-soil map:
 * 50 98 2
 * 52 50 48
 *
 * soil-to-fertilizer map:
 * 0 15 37
 * 37 52 2
 * 39 0 15
 */
int solution1() {
    unordered_set<int64_t> seeds, seeds_mapped;
    string line, word;
    int64_t seed, destination_range_start, source_range_start, range_length;
    unordered_map<int64_t, int64_t> map;

    // First get the seeds
    getline(cin, line);
    stringstream stream(line);
    stream >> word;
    while (stream >> seed) {
        seeds.insert(seed);
    }
    cout << seeds.size() << endl;

    // Get the blank line after
    getline(cin, line);

    // Next, build maps and translate to new spaces as we go

    while(getline(cin, line)) {
        // That first one is gonna be the name of the map,
        // like "seed-to-soil map:" or something. Who cares lol
        cout << "Let's build the map" << endl;
        map.clear();
        int line_num = 1;
        do {
            cout << "line=" << line_num << endl;
            getline(cin, line);
            stringstream stream(line);
            stream >> destination_range_start;
            stream >> source_range_start;
            stream >> range_length;
            for (int64_t i = 0; i < range_length; i++) {
                map.insert(make_pair(source_range_start + i, destination_range_start + i));
            }
            line_num++;
        }
        // Keep going until we hit an empty line.
        // We'll then be onto the next map
        while(line != "");

        // Translate the seeds into their new mapped values
        seeds_mapped.clear();
        unordered_set<int64_t>::iterator it;
        for (it = seeds.begin(); it != seeds.end(); it++) {
            int64_t seed;
            if (map.contains(*it)) {
                seed = map.at(*it);
            } else {
                seed = *it;
            }
            seeds_mapped.insert(seed);
        }

        // Just do the first one for now
        break;
    }

    unordered_set<int64_t>::iterator it;
    for (it = seeds.begin(); it != seeds.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}


int solution2() {
    return 0;
}


int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
