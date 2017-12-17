/**
 * $ g++ solution.cpp &&  ./a.out < input.txt 
 * Day 16!
 * Part 1: giadhmkpcnbfjelo
 * Part 2: njfgilbkcoemhpad
 */

#include <iostream>
#include <string>


using namespace std;


string do_the_dance(string programs, string input) {
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


/**
 * s1, a spin of size 1: eabcd.
 * x3/4, swapping the last two programs: eabdc.
 * pe/b, swapping programs e and b: baedc.
 */
string part1(string input) {
    // string programs = "abcde";
    string programs = "abcdefghijklmnop";
    return do_the_dance(programs, input);
}


string part2(string input) {
    // const int NUM_DANCES = 5;
    // const int NUM_DANCES = 40;
    const int NUM_DANCES = 1000000000;
    string programs = "abcdefghijklmnop";
    // The naive/slow way:
    // for (int i = 0; i < NUM_DANCES; i++) {
    //     programs = do_the_dance(programs, input);
    //     cout << i << ".\t" << programs << endl;
    // }
    // return programs;
    // Optimization: Look for repeats!
    int repeat = -1;
    for (int i = 1; i <= NUM_DANCES; i++) {
        programs = do_the_dance(programs, input);
        if ("abcdefghijklmnop" == programs) {
            repeat = i;
            break;
        }
        // cout << i << ".\t" << programs << endl;
    }
    if (repeat == -1) {
        return programs;
    }
    // cout << "Repeat! " << repeat << " " << programs << endl;

    /* This won't work b/c of letter swaps:
    // // Optimization: Get a map of the ending places of each position
    // string programsA = do_the_dance(programs, input);
    // // cout << programsA << endl;
    // if (programs.length() != programsA.length()) {
    //     throw 199;
    // }
    // int indexMap[programs.length()];
    // for (int i = 0; i < programs.length(); i++) {
    //     for (int j = 0; j < programsA.length(); j++) {
    //         if (programs[i] == programsA[j]) {
    //             indexMap[j] = i;
    //             break;
    //         }
    //     }
    // }
    // // Run this swap a BILLION times!
    // int repeat = NUM_DANCES;
    // for (int i = 0; i < NUM_DANCES; i++) {
    //     if (i % 10000000 == 0) {
    //         cout << "count " << i << endl;
    //     }
    //     programsA = "";
    //     for (int j = 0; j < programs.length(); j++) {
    //         programsA += programs[indexMap[j]];
    //     }
    //     programs = programsA;
    //     cout << i << ".\t" << programs << endl;
    //     if ("abcdefghijklmnop" == programs) {
    //         cout << "Repeat! " << i << " " << programs << endl;
    //         repeat = i;
    //         break;
    //     }
    // }
    */

    int num_non_repeat_dances = NUM_DANCES % repeat;
    // cout << "num_non_repeat_dances: " << num_non_repeat_dances << endl;
    programs = "abcdefghijklmnop";
    for (int i = 0; i < num_non_repeat_dances; i++) {
        programs = do_the_dance(programs, input);
        // cout << i << ".\t" << programs << endl;
    }
    return programs;
}


int main() {
    cout << "Day 16!" << endl;
    string input;
    cin >> input;
    cout << "Part 1: " << part1(input) << endl;
    cout << "Part 2: " << part2(input) << endl;
}
