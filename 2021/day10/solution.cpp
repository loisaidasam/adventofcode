
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;


/**
 * 
 * ): 3 points.
 * ]: 57 points.
 * }: 1197 points.
 * >: 25137 points.
*/
int score_lookup(char value) {
    switch(value) {
        case ')':
            return 3;
        case ']':
            return 57;
        case '}':
            return 1197;
        case '>':
            return 25137;
    }
    return 0;
}


int get_syntax_error_score(string line) {
    stack<char> char_stack;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '(' || line[i] == '[' || line[i] == '{' || line[i] == '<') {
            char_stack.push(line[i]);
            continue;
        }
        if (char_stack.size() == 0) {
            return score_lookup(line[i]);
        }
        char value = char_stack.top();
        if (line[i] == ')' || line[i] == ']' || line[i] == '}' || line[i] == '>') {
            if (line[i] == ')' and value != '(') {
                return score_lookup(line[i]);
            }
            if (line[i] == ']' and value != '[') {
                return score_lookup(line[i]);
            }
            if (line[i] == '}' and value != '{') {
                return score_lookup(line[i]);
            }
            if (line[i] == '>' and value != '<') {
                return score_lookup(line[i]);
            }
            char_stack.pop();
            continue;
        }
        cout << "Something weird ... " << line[i] << endl;
    }
    return 0;
}


int solution1() {
    string line;
    int score = 0;
    while (getline(cin, line)) {
        score += get_syntax_error_score(line);
    }
    return score;
}

/**
 * 
 * ): 1 point.
 * ]: 2 points.
 * }: 3 points.
 * >: 4 points.
*/
int repair_lookup(char value) {
    switch(value) {
        case '(':
            return 1;
        case '[':
            return 2;
        case '{':
            return 3;
        case '<':
            return 4;
    }
    return 0;
}

/**
 * These are guaranteed to either be complete or incomplete, but not corrupted
 */
unsigned long long int get_repair_score(string line) {
    stack<char> char_stack;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == '(' || line[i] == '[' || line[i] == '{' || line[i] == '<') {
            char_stack.push(line[i]);
            continue;
        }
        char value = char_stack.top();
        if (line[i] == ')' || line[i] == ']' || line[i] == '}' || line[i] == '>') {
            char_stack.pop();
            continue;
        }
        cout << "Something weird ... " << line[i] << endl;
    }
    unsigned long long int score = 0;
    while (char_stack.size() > 0) {
        // cout << char_stack.top();
        score *= 5;
        score += repair_lookup(char_stack.top());
        char_stack.pop();
        // cout << score << endl;
    }
    // cout << endl;
    // cout << ": " << score << endl;
    return score;
}

int solution2() {
    string line;
    vector<unsigned long long int> scores;
    while (getline(cin, line)) {
        if (get_syntax_error_score(line) > 0) {
            continue;
        }
        scores.push_back(get_repair_score(line));
    }
    sort(scores.begin(), scores.end());
    return scores.at(scores.size() / 2);
}

int main() {
    // cout << solution1() << endl;
    cout << solution2() << endl;
    return 0;
}
