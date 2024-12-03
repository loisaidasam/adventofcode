
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int solution1(int num) {
    vector<int> list1(num);
    vector<int> list2(num);

    for (int i = 0; i < num; ++i) {
        cin >> list1[i];
        cin >> list2[i];
    }

    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    int diff = 0;

    for (int i = 0; i < num; ++i) {
        diff += abs(list1[i] - list2[i]);
    }
    return diff;
}

int solution2() {
    return 0;
}

int main() {
    // For testing:
    // cout << solution1(6) << endl;
    cout << solution1(1000) << endl;
    // cout << solution2() << endl;
    return 0;
}
