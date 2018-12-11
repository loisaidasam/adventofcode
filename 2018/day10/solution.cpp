
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


class Point {
    public:
        int x, y;
        Point(int x, int y) {
            this->x = x;
            this->y = y;
        }
};


class State {
    public:
        int step_num = 0;
        vector<Point*> points;
        vector<Point*> velocities;
        void read_input() {
            int x, y;
            while (cin >> x >> y) {
                this->points.push_back(new Point(x, y));
                cin >> x >> y;
                this->velocities.push_back(new Point(x, y));
            }
        }
        int get_min_x() {
            int min_x = this->points[0]->x;
            for (int i = 1; i < this->points.size(); i++) {
                if (this->points[i]->x < min_x) {
                    min_x = this->points[i]->x;
                }
            }
            return min_x;
        }
        int get_max_x() {
            int max_x = this->points[0]->x;
            for (int i = 1; i < this->points.size(); i++) {
                if (this->points[i]->x > max_x) {
                    max_x = this->points[i]->x;
                }
            }
            return max_x;
        }
        int get_min_y() {
            int min_y = this->points[0]->y;
            for (int i = 1; i < this->points.size(); i++) {
                if (this->points[i]->y < min_y) {
                    min_y = this->points[i]->y;
                }
            }
            return min_y;
        }
        int get_max_y() {
            int max_y = this->points[0]->y;
            for (int i = 1; i < this->points.size(); i++) {
                if (this->points[i]->y > max_y) {
                    max_y = this->points[i]->y;
                }
            }
            return max_y;
        }
        int get_x_range() {
            return this->get_max_x() - this->get_min_x();
        }
        int get_y_range() {
            return this->get_max_y() - this->get_min_y();
        }
        void step() {
            this->step_num++;
            for (int i = 0; i < this->points.size(); i++) {
                Point* point = this->points[i];
                Point* velocity = this->velocities[i];
                point->x += velocity->x;
                point->y += velocity->y;
            }
        }
        string to_string_verbose() {
            stringstream ss;
            ss << "Step " << this->step_num << endl;
            ss << "Min X: " << this->get_min_x() << endl;
            ss << "Max X: " << this->get_max_x() << endl;
            ss << "X range: " << this->get_x_range() << endl;
            ss << "Min Y: " << this->get_min_y() << endl;
            ss << "Max Y: " << this->get_max_y() << endl;
            ss << "Y range: " << this->get_y_range() << endl;
            return ss.str();
        }
        string to_string_ranges() {
            stringstream ss;
            ss << "X: " << this->get_x_range() << " Y: " << this->get_y_range();
            return ss.str();
        }
        string to_string_grid() {
            int x_range = this->get_x_range() + 1;
            int y_range = this->get_y_range() + 1;
            char grid[x_range][y_range];
            for (int x = 0; x < x_range; x++) {
                for (int y = 0; y < y_range; y++) {
                    grid[x][y] = '.';
                }
            }
            int min_x = this->get_min_x();
            int min_y = this->get_min_y();
            Point* point;
            int x, y;
            for (int i = 0; i < this->points.size(); i++) {
                point = this->points[i];
                x = point->x - min_x;
                y = point->y - min_y;
                // cout << x << " " << y << endl;
                grid[x][y] = '#';
                // break;
            }
            stringstream ss;
            for (int y = 0; y < y_range; y++) {
            // Reverse the Y's?
            // for (int y = y_range; y >= 0; y--) {
                for (int x = 0; x < x_range; x++) {
                    ss << grid[x][y];
                }
                ss << endl;
            }
            return ss.str();
        }
};


void solution1() {
    State* state = new State();
    state->read_input();

    // Confirm test input
    // cout << "Step " << state->step_num << ": " << state->to_string_ranges() << endl;
    // cout << state->to_string_verbose() << endl;
    // cout << state->to_string_grid() << endl;
    // for (int i = 0; i < 5; i++) {
    //     state->step();
    //     cout << "Step " << state->step_num << ": " << state->to_string_ranges() << endl;
    //     cout << state->to_string_grid() << endl;
    // }

    // Discovery, look for smallest range:
    // while (true) {
    //     state->step();
    //     cout << state->step_num << ": " << state->to_string_ranges() << endl;
    // }

    // Range is smallest at step 10831
    for (int i = 0; i < 10831; i++) {
        state->step();
    }
    cout << "Step " << state->step_num << ": " << state->to_string_ranges() << endl;
    cout << state->to_string_grid() << endl;
}


int main() {
    solution1();
}
