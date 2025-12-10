
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

int solution2() {
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
