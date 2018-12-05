/**
 * Day 3
 *
 * multidimensional arrays
 */

#include <iostream>
#include <string>

using namespace std;


const int MAX_DIMENSION = 1000;


int solution1() {
    int id, left, top, width, height;
    int counts[MAX_DIMENSION][MAX_DIMENSION];
    for (int x = 0; x < MAX_DIMENSION; x++) {
        for (int y = 0; y < MAX_DIMENSION; y++) {
            counts[x][y] = 0;
        }
    }
    while (cin >> id) {
        cin >> left;
        cin >> top;
        cin >> width;
        cin >> height;
        for (int x = left; x < left + width; x++) {
            for (int y = top; y < top + height; y++) {
                counts[x][y]++;
            }
        }
    }
    int num_overlap = 0;
    for (int x = 0; x < MAX_DIMENSION; x++) {
        for (int y = 0; y < MAX_DIMENSION; y++) {
            if (counts[x][y] > 1) {
                num_overlap++;
            }
        }
    }
    return num_overlap;
}


int main() {
    cout << solution1() << endl;
    return 0;
}
