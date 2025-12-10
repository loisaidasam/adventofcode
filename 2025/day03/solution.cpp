
#include <iostream>
#include <string>

using namespace std;

long solution1() {
    int total_joltage = 0;
    string bank;
    while (getline(cin, bank)) {
        int bat1_joltage = 0;
        int bat1_pos = 0;
        for (int i = bank.length()-2; i >= 0; i--) {
            // char c = '5';
            // int num = c - '0';  // num = 5
            int joltage = bank[i] - '0';
            if (joltage >= bat1_joltage) {
                bat1_joltage = joltage;
                bat1_pos = i;
            }
        }
        int bat2_joltage = 0;
        int bat2_pos = 0;
        for (int i = bat1_pos+1; i < bank.length(); i++) {
            int joltage = bank[i] - '0';
            if (joltage > bat2_joltage) {
                bat2_joltage = joltage;
                bat2_pos = i;
            }
        }
        total_joltage += (bat1_joltage*10) + bat2_joltage;
        // cout << bank << " " << bat1_joltage << bat2_joltage << " total=" << total_joltage << endl;
    }
    return total_joltage;
}

long long solution2() {
    long long total_joltage = 0;
    string bank;
    const int NUM_DIGITS = 12;
    while (getline(cin, bank)) {
        // cout << bank << " len=" << bank.length() << endl;
        int joltages[NUM_DIGITS] = {};  // All elements = 0;
        int positions[NUM_DIGITS];
        string joltage_str = "";
        for (int digit = 0; digit < NUM_DIGITS; digit++) {
            // Need at least pad digits to the right of the chosen digit
            int pad = NUM_DIGITS-digit-1;
            // toy ex:
            // NUM_DIGITS = 3
            // bank = "52525"
            //         01234    <- indices of bank
            // pad = 2 (num digits to the right of first digit)
            // bank.length() = 5
            // start = 5-2-1 = 2
            // end = 0
            int start = bank.length()-pad-1;
            int end = 0;
            if (digit > 0) {
                end = positions[digit-1] + 1;
            }
            // cout << "start=" << start << " end=" << end << endl;
            for (int i = start; i >= end; i--) {
                // char c = '5';
                // int num = c - '0';  // num = 5
                int joltage = bank[i] - '0';
                // cout << "bank[" << i << "]=" << joltage << endl;
                if (joltage >= joltages[digit]) {
                    joltages[digit] = joltage;
                    positions[digit] = i;
                }
            }
            // cout << " digit=" << digit << " joltages[" << digit << "]=" << joltages[digit] << " positions[" << digit << "]=" << positions[digit] << endl;
            joltage_str += to_string(joltages[digit]);
        }
        // cout << bank << " " << joltage_str << endl;
        long long joltage = stoll(joltage_str);
        total_joltage += joltage;
        // cout << bank << " " << bat1_joltage << bat2_joltage << " total=" << total_joltage << endl;
    }
    return total_joltage;
}

int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
