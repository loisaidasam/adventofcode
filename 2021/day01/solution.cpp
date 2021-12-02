
#include <iostream>

using namespace std;

int solution1() {
    int next;
    int last = -1;
    int num_increases = 0;
    while (cin >> next) {
        if (last != -1 && next > last) {
            num_increases++;
        }
        last = next;
    }
    return num_increases;
}

int solution2() {
    int a, b, c;
    int count = 0;
    int sum;
    int last = -1;
    int num_increases = 0;
    while (cin >> c) {
        sum = a + b + c;
        // cout << a << " " << b << " " << c << " (" << sum << ")" << endl;
        if (count >= 2) {
            if (last != -1 && sum > last) {
                // cout << "\tincrease " << a + b + c << " > " << last << endl;
                num_increases++;
            }
            last = sum;
        }
        a = b;
        b = c;
        count++;
    }
    // cout << "count: " << count << endl;
    return num_increases;
}

int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
