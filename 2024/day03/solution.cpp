
#include <iostream>
#include <regex>
#include <string>
#include <sstream>

using namespace std;

int solution1() {
    // Read all lines from stdin into a single string
    ostringstream buffer;
    buffer << cin.rdbuf();
    string input = buffer.str();

    // Define the regex pattern with capturing groups
    regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");

    // Iterator for finding matches
    auto matches_begin = sregex_iterator(input.begin(), input.end(), pattern);
    auto matches_end = sregex_iterator();

    int total = 0;

    // Iterate over all matches
    for (auto it = matches_begin; it != matches_end; ++it) {
        smatch match = *it;

        // Extract the full match and the capturing groups
        string full_match = match.str(0);
        string group1 = match.str(1); // First group: digits before the comma
        string group2 = match.str(2); // Second group: digits after the comma

        // cout << "Full match: " << full_match << endl;
        // cout << "Group 1: " << group1 << ", Group 2: " << group2 << endl;

        // Convert strings to integers
        int num1 = stoi(group1);
        int num2 = stoi(group2);
        total += num1 * num2;
    }

    return total;
}

int solution2() {
    // Read all lines from stdin into a single string
    ostringstream buffer;
    buffer << cin.rdbuf();
    string input = buffer.str();

    // cout << input << endl;

    // Define the regex pattern with capturing groups
    regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");

    // Iterator for finding matches
    auto matches_begin = sregex_iterator(input.begin(), input.end(), pattern);
    auto matches_end = sregex_iterator();

    int total = 0;
    bool enabled = true;

    // Iterate over all matches
    for (auto it = matches_begin; it != matches_end; ++it) {
        smatch match = *it;

        // Check which part of the regex matched
        if (match[1].matched && match[2].matched) {
            // `mul()` pattern matched
            int num1 = stoi(match.str(1)); // First group: digits before the comma
            int num2 = stoi(match.str(2)); // Second group: digits after the comma
            if (enabled) {
                total += num1 * num2;
            }
            // cout << "Matched mul(): Group 1 (int): " << num1 << ", Group 2 (int): " << num2 << endl;
        } else if (match.str(0) == "do()") {
            // cout << "Matched literal: do()" << endl;
            enabled = true;
        } else if (match.str(0) == "don't()") {
            // cout << "Matched literal: don't()" << endl;
            enabled = false;
        }
    }

    return total;
}

int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
