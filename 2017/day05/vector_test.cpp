
#include <iostream>
#include <vector>

using namespace std;


int main() {
    vector<int> numbers;
    numbers.push_back(2);
    numbers.push_back(4);
    numbers.push_back(6);
    cout << numbers[0] << endl;
    cout << numbers[1] << endl;
    cout << numbers[2] << endl;
    numbers[1] = 5;
    cout << numbers[1] << endl;
    numbers[2] += 10;
    cout << numbers[2] << endl;

    // For BW:

    int max = numeric_limits<int>::max() - 1;
    cout << max;
    numbers.push_back(max);
    cout << numbers[4] << endl;

    max = numeric_limits<int>::max();
    cout << max;
    numbers.push_back(max);
    cout << numbers[5] << endl;

    max = numeric_limits<int>::max() + 1;
    cout << max;
    numbers.push_back(max);
    cout << numbers[6] << endl;
}

