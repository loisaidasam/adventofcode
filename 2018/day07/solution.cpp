/**
 * Day 7
 *
 *
 */

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


// const int NUM_SECONDS_REMAINING_START = 0;
const int NUM_SECONDS_REMAINING_START = 60;

// const int NUM_WORKERS = 2;
const int NUM_WORKERS = 5;


class Step {
    private:
        vector<char> requirements;
        int num_seconds_remaining;
        void set_num_seconds_remaining() {
            this->num_seconds_remaining = NUM_SECONDS_REMAINING_START;
            string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            for (int i = 0; i < alphabet.length(); i++) {
                this->num_seconds_remaining++;
                if (this->id == alphabet[i]) {
                    break;
                }
            }
        }
    public:
        char id;
        Step(char id) {
            this->id = id;
            this->set_num_seconds_remaining();
        }
        void add_requirement(char requirement) {
            if (find(requirements.begin(), requirements.end(), requirement) != requirements.end()) {
                cout << "Step " << this->id << "Found dupe requirement " << requirement << endl;
                return;
            }
            this->requirements.push_back(requirement);
        }
        bool are_requirements_fullfilled(unordered_set<char> steps_finished) {
            for (int i = 0; i < this->requirements.size(); i++) {
                char requirement = this->requirements[i];
                if (steps_finished.find(requirement) == steps_finished.end()) {
                    return false;
                }
            }
            return true;
        }
        bool needs_work() {
            return this->num_seconds_remaining > 0;
        }
        /**
         * Returns whether or not all work was completed
         */
        bool do_work() {
            if (this->num_seconds_remaining <= 0) {
                cout << "Can't do work on step " << this->id << "!";
                return true;
            }
            this->num_seconds_remaining--;
            return this->num_seconds_remaining == 0;
        }
        string to_string() {
            stringstream ss;
            ss << this->id << " (" << this->num_seconds_remaining_pretty() << ") / " << this->requirements.size() << " requirements: " << this->requirements_pretty();
            return ss.str();
        }
        string num_seconds_remaining_pretty() {
            stringstream ss;
            ss << this->num_seconds_remaining << "s remaining";
            return ss.str();
        }
        string requirements_pretty() {
            stringstream ss;
            for (int i = 0; i < this->requirements.size(); i++) {
                ss << this->requirements[i];
            }
            return ss.str();
        }
};


unordered_map<char, Step*> read_input() {
    unordered_map<char, Step*> steps;
    char step_id_requirement, step_id;
    while (cin >> step_id_requirement) {
        if (steps.find(step_id_requirement) == steps.end()) {
            steps[step_id_requirement] = new Step(step_id_requirement);
        }
        cin >> step_id;
        if (steps.find(step_id) == steps.end()) {
            steps[step_id] = new Step(step_id);
        }
        steps[step_id]->add_requirement(step_id_requirement);
    }
    return steps;
}

string steps_to_string(unordered_map<char, Step*> steps) {
    stringstream ss;
    ss << steps.size() << " steps:" << endl;
    unordered_map<char, Step*>::iterator it;
    int step_num = 1;
    for (it = steps.begin(); it != steps.end(); it++) {
        ss << step_num << ".\t" << it->second->to_string() << endl;
        step_num++;
    }
    return ss.str();
}


string steps_set_to_string(unordered_set<char> steps) {
    stringstream ss;
    unordered_set<char>::iterator it;
    for (it = steps.begin(); it != steps.end(); it++) {
        ss << *it;
    }
    return ss.str();
}


string steps_vector_to_string(vector<char> steps) {
    stringstream ss;
    for (int i = 0; i < steps.size(); i++) {
        ss << steps[i];
    }
    return ss.str();
}


string solution1() {
    unordered_map<char, Step*> steps = read_input();
    // cout << steps_to_string(steps) << endl;
    unordered_set<char> steps_finished;
    char step_id;
    stringstream ss;
    while (steps_finished.size() < steps.size()) {
        // cout << steps_set_to_string(steps_finished) << endl;
        vector<char> steps_ready;
        unordered_map<char, Step*>::iterator it;
        for (it = steps.begin(); it != steps.end(); it++) {
            if (steps_finished.find(it->first) != steps_finished.end()) {
                continue;
            }
            if (it->second->are_requirements_fullfilled(steps_finished)) {
                steps_ready.push_back(it->first);
            }
        }
        if (steps_ready.size() == 0) {
            cout << "No steps ready!" << endl;
            return ss.str();
        }
        sort(steps_ready.begin(), steps_ready.end());
        step_id = steps_ready[0];
        ss << step_id;
        steps_finished.insert(step_id);
    }
    return ss.str();
}


int solution2() {
    cout << "NUM_SECONDS_REMAINING_START=" << NUM_SECONDS_REMAINING_START << endl;
    cout << "NUM_WORKERS=" << NUM_WORKERS << endl;
    int second = -1;
    unordered_map<char, Step*> steps = read_input();
    // cout << steps_to_string(steps) << endl;
    unordered_set<char> steps_finished;
    char step_id;
    while (steps_finished.size() < steps.size()) {
        second++;
        // cout << "Second " << second << endl;
        // cout << steps_to_string(steps) << endl;
        // cout << "Steps finished: " << steps_set_to_string(steps_finished) << endl;
        vector<char> steps_ready, steps_work;
        unordered_map<char, Step*>::iterator it;
        for (it = steps.begin(); it != steps.end(); it++) {
            // Step already finished
            if (steps_finished.find(it->first) != steps_finished.end()) {
                continue;
            }
            // Step not ready
            if (! it->second->are_requirements_fullfilled(steps_finished)) {
                continue;
            }
            // Step needs work
            if (! it->second->needs_work()) {
                cout << "Step " << it->first << "doesn't need work. TODO: Can this ever happen?!" << endl;
                continue;
            }
            steps_ready.push_back(it->first);
        }
        if (steps_ready.size() == 0) {
            cout << "No steps ready! TODO: Can this happen?" << endl;
            break;
        }
        sort(steps_ready.begin(), steps_ready.end());
        // cout << "Steps ready: " << steps_vector_to_string(steps_ready) << endl;
        for (int i = 0; i < NUM_WORKERS && i < steps_ready.size(); i++) {
            step_id = steps_ready[i];
            steps_work.push_back(step_id);
            if (steps[step_id]->do_work()) {
                steps_finished.insert(step_id);
            }
        }
        // cout << "Steps worked on: " << steps_vector_to_string(steps_work) << "\n" << endl;
    }
    return second;
}


int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
