/**
 * Day 9
 *
 * Doubly-linked lists, big numbers (int vs. long)
 */

#include <iostream>
#include <sstream>
#include <string>

using namespace std;


class Marble {
    public:
        int number;
        Marble* left;
        Marble* right;
        Marble(int number) {
            this->number = number;
        }
};

class Circle {
    private:
        Marble* marble_zero;
        Marble* current_marble;
        void add_marble_non_23(int number) {
            Marble* new_marble = new Marble(number);
            new_marble->left = this->current_marble->right;
            new_marble->right = this->current_marble->right->right;
            new_marble->left->right = new_marble;
            new_marble->right->left = new_marble;
            this->current_marble = new_marble;
        }
        int add_marble_23(int number) {
            Marble* marble = this->current_marble;
            for (int i = 0; i < 7; i++) {
                marble = marble->left;
            }
            number += marble->number;
            marble->left->right = marble->right;
            marble->right->left = marble->left;
            this->current_marble = marble->right;
            return number;
        }
    public:
        Circle() {
            this->marble_zero = this->current_marble = new Marble(0);
            this->current_marble->left = this->current_marble;
            this->current_marble->right = this->current_marble;
        }
        int add_marble(int number) {
            if (number % 23 == 0) {
                return this->add_marble_23(number);
            }
            this->add_marble_non_23(number);
            return 0;
        }
        string to_string() {
            stringstream ss;
            Marble* marble = this->marble_zero;
            do {
                if (marble->number == this->current_marble->number) {
                    ss << "(";
                }
                ss << marble->number;
                if (marble->number == this->current_marble->number) {
                    ss << ")";
                }
                ss << " ";
                marble = marble->right;
            } while (marble->number != 0);
            return ss.str();
        }
};


long solution1(int num_players, int last_marble) {
    long scores[num_players];
    for (int i = 0; i < num_players; i++) {
        scores[i] = 0;
    }
    Circle* circle = new Circle();
    // cout << circle->to_string() << endl;
    int player_number = 0;
    for (int number = 1; number <= last_marble; number++) {
        scores[player_number] += circle->add_marble(number);
        // if (number % 1000000 == 0) {
        //     cout << number << endl;
        // }
        // cout << "[" << (player_number + 1) << "]\t" << circle->to_string() << endl;
        player_number = (player_number + 1) % num_players;
    }
    long max_score = 0;
    for (int i = 0; i < num_players; i++) {
        if (scores[i] > max_score) {
            max_score = scores[i];
        }
    }
    return max_score;
}


long solution2(int num_players, int last_marble) {
    return solution1(num_players, last_marble * 100);
}


int main() {
    int num_players, last_marble;
    cin >> num_players >> last_marble;
    // cout << solution1(num_players, last_marble) << endl;
    cout << solution2(num_players, last_marble) << endl;
}
