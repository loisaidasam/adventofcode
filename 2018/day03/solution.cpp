/**
 * Day 3
 *
 * multidimensional arrays, classes
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;


const int MAX_DIMENSION = 1000;


class Claim {
    public:
        int id, left, top, width, height;
        Claim(int id, int left, int top, int width, int height) {
            this->id = id;
            this->left = left;
            this->top = top;
            this->width = width;
            this->height = height;
        }
};


vector<Claim*> read_claims() {
    int id, left, top, width, height;
    Claim* claim;
    vector<Claim*> claims;
    while (cin >> id) {
        cin >> left;
        cin >> top;
        cin >> width;
        cin >> height;
        claim = new Claim(id, left, top, width, height);
        claims.push_back(claim);
    }
    return claims;
}


int** initialize_matrix () {
    int** counts = new int*[MAX_DIMENSION];
    for (int x = 0; x < MAX_DIMENSION; x++) {
        counts[x] = new int[MAX_DIMENSION];
        for (int y = 0; y < MAX_DIMENSION; y++) {
            counts[x][y] = 0;
        }
    }
    return counts;
}


void set_counts(int** counts, vector<Claim*> claims) {
    for (int i = 0; i < claims.size(); i++) {
        Claim* claim = claims[i];
        for (int x = claim->left; x < claim->left + claim->width; x++) {
            for (int y = claim->top; y < claim->top + claim->height; y++) {
                counts[x][y]++;
            }
        }
    }
}


int solution1() {
    vector<Claim*> claims = read_claims();
    int** counts = initialize_matrix();
    set_counts(counts, claims);
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


bool has_overlap(int** counts, Claim* claim) {
    for (int x = claim->left; x < claim->left + claim->width; x++) {
        for (int y = claim->top; y < claim->top + claim->height; y++) {
            if (counts[x][y] > 1) {
                return true;
            }
        }
    }
    return false;
}


int solution2() {
    vector<Claim*> claims = read_claims();
    int** counts = initialize_matrix();
    set_counts(counts, claims);
    for (int i = 0; i < claims.size(); i++) {
        Claim* claim = claims[i];
        if (! has_overlap(counts, claim)) {
            return claim->id;
        }
    }
    return -1;
}


int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
