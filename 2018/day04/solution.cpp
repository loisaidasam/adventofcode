/**
 * Day 4
 *
 * getline() via http://www.cplusplus.com/doc/tutorial/basic_io/
 * sorting via http://www.cplusplus.com/articles/NhA0RXSz/
 * stringstream via http://www.cplusplus.com/reference/sstream/stringstream/str/
 */

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


vector<string> read_input() {
    vector<string> records;
    string record;
    while (getline(cin, record)) {
        records.push_back(record);
    }
    sort(records.begin(), records.end());
    return records;
}


/**
 *
 * [1518-02-23 00:03] Guard #751 begins shift
 * [1518-02-23 00:10] falls asleep
 * [1518-02-23 00:15] wakes up
 * [1518-02-23 00:21] falls asleep
 * [1518-02-23 00:29] wakes up
 */
int get_sleepiest_guard(vector<string> records) {
    map<int, int> guard_sleeptimes;
    string record, word;
    int guard_id, minute, sleep_start, sleeptime;
    for (int i = 0; i < records.size(); i++) {
        record = records[i];
        stringstream ss;
        ss << record;
        ss >> word >> word;
        // word now has something like "00:03]"
        minute = stoi(word.substr(3, 2));
        ss >> word;
        if (word == "Guard") {
            ss >> word;
            guard_id = stoi(word.substr(1, word.length() - 1));
            continue;
        }
        if (word == "falls") {
            sleep_start = minute;
            continue;
        }
        if (word == "wakes") {
            sleeptime = minute - sleep_start;
            if (guard_sleeptimes.find(guard_id) == guard_sleeptimes.end()) {
                guard_sleeptimes[guard_id] = 0;
            }
            guard_sleeptimes[guard_id] += sleeptime;
        }
    }
    int max_sleeptime = 0;
    map<int, int>::iterator it;
    for (it = guard_sleeptimes.begin(); it != guard_sleeptimes.end(); it++) {
        if (it->second > max_sleeptime) {
            guard_id = it->first;
            max_sleeptime = it->second;
        }
    }
    return guard_id;
}


int get_sleepiest_minute(vector<string> records, int sleepy_guard_id) {
    map<int, int> minute_counts;
    string record, word;
    int guard_id, minute, sleep_start;
    for (int i = 0; i < records.size(); i++) {
        record = records[i];
        stringstream ss;
        ss << record;
        ss >> word >> word;
        // word now has something like "00:03]"
        minute = stoi(word.substr(3, 2));
        ss >> word;
        if (word == "Guard") {
            ss >> word;
            guard_id = stoi(word.substr(1, word.length() - 1));
            continue;
        }
        // No need to spin our wheels on guards we don't care about!
        if (guard_id != sleepy_guard_id) {
            continue;
        }
        if (word == "falls") {
            sleep_start = minute;
            continue;
        }
        if (word == "wakes") {
            for (int i = sleep_start; i < minute; i++) {
                if (minute_counts.find(i) == minute_counts.end()) {
                    minute_counts[i] = 0;
                }
                minute_counts[i]++;
            }
        }
    }
    int max_minute;
    int max_minute_count = 0;
    map<int, int>::iterator it;
    for (it = minute_counts.begin(); it != minute_counts.end(); it++) {
        if (it->second > max_minute_count) {
            max_minute = it->first;
            max_minute_count = it->second;
        }
    }
    return max_minute;
}


int solution1() {
    vector<string> records = read_input();
    // for (int i = 0; i < 5; i++) {
    //     cout << input[i] << endl;
    // }
    int guard_id = get_sleepiest_guard(records);
    int sleepiest_minute = get_sleepiest_minute(records, guard_id);
    return guard_id * sleepiest_minute;
}


int solution2() {
    vector<string> records = read_input();
    map<int, int*> guard_minute_counts;
    string record, word;
    int guard_id, minute, sleep_start, max_sleep_guard_id, max_sleep_minute;
    int max_sleeptime = 0;
    for (int i = 0; i < records.size(); i++) {
        record = records[i];
        stringstream ss;
        ss << record;
        ss >> word >> word;
        // word now has something like "00:03]"
        minute = stoi(word.substr(3, 2));
        ss >> word;
        if (word == "Guard") {
            ss >> word;
            guard_id = stoi(word.substr(1, word.length() - 1));
            continue;
        }
        if (word == "falls") {
            sleep_start = minute;
            continue;
        }
        if (word == "wakes") {
            if (guard_minute_counts.find(guard_id) == guard_minute_counts.end()) {
                guard_minute_counts[guard_id] = new int[60];
                for (int i = 0; i < 60; i++) {
                    guard_minute_counts[guard_id][i] = 0;
                }
            }
            for (int i = sleep_start; i < minute; i++) {
                guard_minute_counts[guard_id][i]++;
                if (guard_minute_counts[guard_id][i] > max_sleeptime) {
                    max_sleep_guard_id = guard_id;
                    max_sleep_minute = i;
                    max_sleeptime = guard_minute_counts[guard_id][i];
                }
            }
        }
    }
    return max_sleep_guard_id * max_sleep_minute;
}


int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
