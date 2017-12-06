/**
 * g++ vector_test.cpp && ./a.out 
 * 2
 * 4
 * 6
 * 5
 * 16
 * 2147483646
 * -2146959360
 * 2147483647
 * 32767
 * -2147483648
 * -1760552747
 */
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
    // http://en.cppreference.com/w/cpp/container/vector/push_back
    // http://en.cppreference.com/w/cpp/types/numeric_limits/max

    int max = numeric_limits<int>::max() - 1;
    cout << max << endl;
    numbers.push_back(max);
    cout << numbers[4] << endl;

    max = numeric_limits<int>::max();
    cout << max << endl;
    numbers.push_back(max);
    cout << numbers[5] << endl;

    max = numeric_limits<int>::max() + 1;
    cout << max << endl;
    numbers.push_back(max);
    cout << numbers[6] << endl;
}

