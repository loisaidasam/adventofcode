
#include <iostream>

using namespace std;

int solution1() {
    // Example:
    // int positionA = 4;
    // int positionB = 8;
    // Real
    int positionA = 3;
    int positionB = 7;

    int scoreA = 0;
    int scoreB = 0;
    int diceCount = 0;
    int roll;
    while (true) {
        // Player A
        roll = 0;
        for (int i = 0; i < 3; i++) {
            diceCount++;
            roll += diceCount;
        }
        positionA += roll;
        while (positionA > 10) {
            positionA -= 10;
        }
        scoreA += positionA;
        if (scoreA >= 1000) {
            return scoreB * diceCount;
        }
        // Player B
        roll = 0;
        for (int i = 0; i < 3; i++) {
            diceCount++;
            roll += diceCount;
        }
        positionB += roll;
        while (positionB > 10) {
            positionB -= 10;
        }
        scoreB += positionB;
        if (scoreB >= 1000) {
            return scoreA * diceCount;
        }
    }
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
