
#include <iostream>
#include <vector>

using namespace std;

class Lanternfish {
    private:
        int age;
    public:
        Lanternfish(int age) {
            this->age = age;
        }

        bool tick_spawned_new_fish() {
            if (this->age == 0) {
                this->age = 6;
                return true;
            }
            this->age--;
            return false;
        }

        int get_age() {
            return this->age;
        }
}

class State {
    private:
        vector<Lanternfish*> fishes;
        int days;
    public:
        State() {
            this->days = 0;
        }

        void add_fish(int age) {
            fish = new Lanternfish(age);
            fishes.push_back(fish);
        }

        void print_state() {
            cout << "After\t" << this->days << " days: ";
            for (int i = 0; i < fishes.size(); i++) {
                cout << fishes[i].get_age() << ",";
            }
            cout << endl;
        }

        void tick() {

        }
}

int solution1() {
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
