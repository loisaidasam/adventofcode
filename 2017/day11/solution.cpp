/**
 */

#include <iostream>
#include <sstream>
#include <string>

using namespace std;


enum Direction {NORTH, SOUTH, NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST};


Direction get_direction_opposite(Direction direction) {
    switch (direction) {
        case Direction::NORTH:
            return Direction::SOUTH;
        case Direction::SOUTH:
            return Direction::NORTH;
    }
    throw 200;
}


class Node {
    private:
        int depth;
        Node* north;
        Node* south;
        // , s, ne, nw, se, sw;
    public:
        Node(int depth) {
            this->depth = depth;
        }
        int get_depth() {
            return depth;
        }
        void add_direction(Direction direction) {
            Node* new_node = new Node(depth + 1);
            // cout << "new node depth: " << new_node.get_depth() << endl;
            add_relationship(new_node, direction);
            new_node->add_relationship(this, get_direction_opposite(direction));
        }
        void add_relationship(Node* new_node, Direction direction) {
            switch (direction) {
                case Direction::NORTH: {
                    north = new_node;
                    break;
                }
                case Direction::SOUTH: {
                    south = new_node;
                    break;
                }
            }
        }
        Node* get_relationship(Direction direction) {
            switch (direction) {
                case Direction::NORTH:
                    return north;
                case Direction::SOUTH:
                    return south;
            }
            throw 100;
        }
};


int main() {
    cout << "Day 11!" << endl;
    // string input;
    // cin >> input;
    // cout << "Part 1: " << part1(input) << endl;

    Node* root = new Node(0);
    cout << "root depth: " << root->get_depth() << endl;
    root->add_direction(Direction::NORTH);
    Node* north = root->get_relationship(Direction::NORTH);
    cout << "north depth: " << north->get_depth() << endl;
    Node* south = north->get_relationship(Direction::SOUTH);
    cout << "north's south depth: " << south->get_depth() << endl;
}


/*
void step(string direction) {
    // cout << direction << endl;
    // if (direction == "n") {
    //     count_n_s++;
    // } else if (direction == "s") {
    //     count_n_s--;
    // } else if (direction == "ne") {
    //     count_ne_sw++;
    // } else if (direction == "sw") {
    //     count_ne_sw--;
    // } else if (direction == "se") {
    //     count_se_nw++;
    // } else if (direction == "nw") {
    //     count_se_nw--;
    // } else {
    //     throw 199;
    // }
}


int part1(string input) {
    stringstream stream(input);
    string direction;
    char buffer;
    while (stream >> buffer) {
        direction += buffer;
        if (stream.peek() == ',') {
            stream.ignore();
            step(direction);
            direction = "";
        }
    }
    step(direction);
    return 0;
}
*/