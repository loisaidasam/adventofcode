/**
 * Day 7
 *
 *
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


class Step {
    private:
        vector<char> requirements;
    public:
        char id;
        Step(char id) {
            this->id = id;
        }
        void add_requirement(char requirement) {
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
        string to_string() {
            string result = "";
            result += this->id;
            result += " / requirements: ";
            for (int i = 0; i < this->requirements.size(); i++) {
                result += this->requirements[i];
            }
            return result;
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

void print_steps(unordered_map<char, Step*> steps) {
    cout << steps.size() << " steps:" << endl;
    unordered_map<char, Step*>::iterator it;
    for (it = steps.begin(); it != steps.end(); it++) {
        cout << it->second->to_string() << endl;
    }
}


void print_steps_finished(unordered_set<char> steps_finished) {
    cout << "Steps finished: ";
    unordered_set<char>::iterator it;
    for (it = steps_finished.begin(); it != steps_finished.end(); it++) {
        cout << *it;
    }
    cout << endl;
}


string solution1() {
    unordered_map<char, Step*> steps = read_input();
    // print_steps(steps);
    unordered_set<char> steps_finished;
    char step_id;
    string result = "";
    while (steps_finished.size() < steps.size()) {
        // print_steps_finished(steps_finished);
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
            return result;
        }
        sort(steps_ready.begin(), steps_ready.end());
        step_id = steps_ready[0];
        result += step_id;
        steps_finished.insert(step_id);
    }
    return result;
}


int main() {
    cout << solution1() << endl;
}
