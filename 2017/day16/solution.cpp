/**
 * $ g++ solution.cpp &&  ./a.out < input.txt 
 * Day 16!
 * Part 1: giadhmkpcnbfjelo
 */

#include <iostream>
#include <string>


using namespace std;


/**
 * s1, a spin of size 1: eabcd.
 * x3/4, swapping the last two programs: eabdc.
 * pe/b, swapping programs e and b: baedc.
 */
string part1(string input) {
    // string programs = "abcde";
    string programs = "abcdefghijklmnop";
    string buffer;
    for (int i = 0; i < input.length(); i++) {
        buffer = "";

        // Spin, written sX, makes X programs move from the end to the front,
        // but maintain their order otherwise. (For example, s3 on abcde
        // produces cdeab).
        if (input[i] == 's') {
            i++;
            while (i < input.length() && input[i] != ',') {
                buffer += input[i];
                i++;
            }
            int spin_num = stoi(buffer);
            int pivot_index = programs.length() - spin_num;
            string result = "";
            for (int j = pivot_index; j < programs.length(); j++) {
                result += programs[j];
            }
            for (int j = 0; j < pivot_index; j++) {
                result += programs[j];
            }
            // cout << "s" << buffer << ": " << programs << " to " << result << endl;
            programs = result;
            continue;
        }

        // Exchange, written xA/B, makes the programs at positions A and B swap
        // places.
        if (input[i] == 'x') {
            i++;
            while (input[i] != '/') {
                buffer += input[i];
                i++;
            }
            i++;
            int positionA = stoi(buffer);
            buffer = "";
            while (i < input.length() && input[i] != ',') {
                buffer += input[i];
                i++;
            }
            int positionB = stoi(buffer);
            // cout << "x" << positionA << "/" << positionB << ": " << programs << " to ";
            char temp = programs[positionA];
            programs[positionA] = programs[positionB];
            programs[positionB] = temp;
            // cout << programs << endl;
            continue;
        }
        // Partner, written pA/B, makes the programs named A and B swap places.
        if (input[i] == 'p') {
            i++;
            char programA = input[i];
            i += 2;
            char programB = input[i];
            i++;
            int positionA, positionB;
            for (int j = 0; j < programs.length(); j++) {
                if (programs[j] == programA) {
                    positionA = j;
                } else if (programs[j] == programB) {
                    positionB = j;
                }
            }
            // cout << "p" << programA << "/" << programB << ": " << programs << " to ";
            char temp = programs[positionA];
            programs[positionA] = programs[positionB];
            programs[positionB] = temp;
            // cout << programs << endl;
            continue;
        }
        throw 159;
    }
    return programs;
}


int main() {
    cout << "Day 16!" << endl;
    string input;
    cin >> input;
    cout << "Part 1: " << part1(input) << endl;
}
