/**
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;


enum Direction {NORTH, SOUTH, NORTHEAST, NORTHWEST, SOUTHEAST, SOUTHWEST};


Direction string_to_direction(string direction) {
    if (direction == "n") {
        return Direction::NORTH;
    }
    if (direction == "s") {
        return Direction::SOUTH;
    }
    if (direction == "ne") {
        return Direction::NORTHEAST;
    }
    if (direction == "nw") {
        return Direction::NORTHWEST;
    }
    if (direction == "se") {
        return Direction::SOUTHEAST;
    }
    if (direction == "sw") {
        return Direction::SOUTHWEST;
    }
    throw 1099;
}


string get_direction_str(Direction direction) {
    switch (direction) {
        case Direction::NORTH:
            return "NORTH";
        case Direction::SOUTH:
            return "SOUTH";
        case Direction::NORTHEAST:
            return "NORTHEAST";
        case Direction::NORTHWEST:
            return "NORTHWEST";
        case Direction::SOUTHEAST:
            return "SOUTHEAST";
        case Direction::SOUTHWEST:
            return "SOUTHWEST";
    }
}


Direction get_direction_opposite(Direction direction) {
    switch (direction) {
        case Direction::NORTH:
            return Direction::SOUTH;
        case Direction::SOUTH:
            return Direction::NORTH;
        case Direction::NORTHEAST:
            return Direction::SOUTHWEST;
        case Direction::NORTHWEST:
            return Direction::SOUTHEAST;
        case Direction::SOUTHEAST:
            return Direction::NORTHWEST;
        case Direction::SOUTHWEST:
            return Direction::NORTHEAST;
    }
}


class Node {
    private:
        int depth;
        string name;
        Node* north = NULL;
        Node* south = NULL;
        Node* northeast = NULL;
        Node* northwest = NULL;
        Node* southeast = NULL;
        Node* southwest = NULL;
    public:
        Node(int depth, string name) {
            this->depth = depth;
            this->name = name;
        }
        int get_depth() {
            return depth;
        }
        string get_name() {
            return "[" + name + "]";
        }
        Node* get_relationship(Direction direction) {
            switch (direction) {
                case Direction::NORTH:
                    return north;
                case Direction::SOUTH:
                    return south;
                case Direction::NORTHEAST:
                    return northeast;
                case Direction::NORTHWEST:
                    return northwest;
                case Direction::SOUTHEAST:
                    return southeast;
                case Direction::SOUTHWEST:
                    return southwest;
            }
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
                case Direction::NORTHEAST: {
                    northeast = new_node;
                    break;
                }
                case Direction::NORTHWEST: {
                    northwest = new_node;
                    break;
                }
                case Direction::SOUTHEAST: {
                    southeast = new_node;
                    break;
                }
                case Direction::SOUTHWEST: {
                    southwest = new_node;
                    break;
                }
            }
        }
        Node* add_direction(Direction direction) {
            // cout << get_name() << " adding direction: " << get_direction_str(direction) << endl;
            string new_node_name = name + " -> " + get_direction_str(direction);
            Node* new_node = new Node(depth + 1, new_node_name);
            // cout << "new node depth: " << new_node.get_depth() << endl;
            add_relationship(new_node, direction);
            new_node->add_relationship(this, get_direction_opposite(direction));
            return new_node;
        }
        vector<Node*> expand() {
            // cout << get_name() << " expand()" << endl;
            vector<Node*> new_nodes;
            if (north == NULL) {
                new_nodes.push_back(add_direction(Direction::NORTH));
            }
            if (south == NULL) {
                new_nodes.push_back(add_direction(Direction::SOUTH));
            }
            if (northeast == NULL) {
                new_nodes.push_back(add_direction(Direction::NORTHEAST));
            }
            if (northwest == NULL) {
                new_nodes.push_back(add_direction(Direction::NORTHWEST));
            }
            if (southeast == NULL) {
                new_nodes.push_back(add_direction(Direction::SOUTHEAST));
            }
            if (southwest == NULL) {
                new_nodes.push_back(add_direction(Direction::SOUTHWEST));
            }
            // North/Northeast
            if (north->get_relationship(SOUTHEAST) == NULL) {
                north->add_relationship(northeast, SOUTHEAST);
            }
            if (northeast->get_relationship(NORTHWEST) == NULL) {
                northeast->add_relationship(north, NORTHWEST);
            }
            // Northeast/Southeast
            if (northeast->get_relationship(SOUTH) == NULL) {
                northeast->add_relationship(southeast, SOUTH);
            }
            if (southeast->get_relationship(NORTH) == NULL) {
                southeast->add_relationship(northeast, NORTH);
            }
            // Southeast/South
            if (southeast->get_relationship(SOUTHWEST) == NULL) {
                southeast->add_relationship(south, SOUTHWEST);
            }
            if (south->get_relationship(NORTHEAST) == NULL) {
                south->add_relationship(southeast, NORTHEAST);
            }
            // South/Southwest
            if (south->get_relationship(NORTHWEST) == NULL) {
                south->add_relationship(southwest, NORTHWEST);
            }
            if (southwest->get_relationship(SOUTHEAST) == NULL) {
                southwest->add_relationship(south, SOUTHEAST);
            }
            // Southwest/Northwest
            if (southwest->get_relationship(NORTH) == NULL) {
                southwest->add_relationship(northwest, NORTH);
            }
            if (northwest->get_relationship(SOUTH) == NULL) {
                northwest->add_relationship(southwest, SOUTH);
            }
            // Northwest/North
            if (northwest->get_relationship(NORTHEAST) == NULL) {
                northwest->add_relationship(north, NORTHEAST);
            }
            if (north->get_relationship(SOUTHWEST) == NULL) {
                north->add_relationship(northwest, SOUTHWEST);
            }
            // cout << get_name() << " added " << new_nodes.size() << " in expand()" << endl;
            return new_nodes;
        }
};


class Hive {
    private:
        Node* current_node;
        Node* next_node;
        vector<Node*> known_nodes;
        int num_steps = 0;
        void expand_hive() {
            cout << "Expanding hive from " << known_nodes.size() << " ..." << endl;
            vector<Node*> new_nodes;
            for (int i = 0; i < known_nodes.size(); i++) {
                vector<Node*> new_nodes_node = known_nodes[i]->expand();
                for (int j = 0; j < new_nodes_node.size(); j++) {
                    new_nodes.push_back(new_nodes_node[j]);
                }
            }
            for (int i = 0; i < new_nodes.size(); i++) {
                known_nodes.push_back(new_nodes[i]);
            }
            cout << "Expanded hive to " << known_nodes.size() << endl;
        }
    public:
        Hive() {
            current_node = new Node(0, "ROOT");
            known_nodes.push_back(current_node);
        }
        string get_current_node_name() {
            return current_node->get_name();
        }
        void step(Direction direction) {
            num_steps++;
            cout << num_steps << ". step(" << get_direction_str(direction) << ")" << endl;
            next_node = current_node->get_relationship(direction);
            // cout << "next_node: " << next_node << endl;
            if (next_node == NULL) {
                // cout << "next_node is NULL" << endl;
                expand_hive();
                next_node = current_node->get_relationship(direction);
            }
            current_node = next_node;
        }
        int get_distance_from_home() {
            return current_node->get_depth();
        }
        int get_deepest_depth() {
            int deepest_depth = 0;
            for (int i = 0; i < known_nodes.size(); i++) {
                int depth = known_nodes[i]->get_depth();
                if (depth > deepest_depth) {
                    deepest_depth = depth;
                }
            }
            return deepest_depth;
        }
};


int part1(Hive* hive) {
    return hive->get_distance_from_home();
}


int part2(Hive* hive) {
    return hive->get_deepest_depth();
}


int main() {
    cout << "Day 11!" << endl;
    string input;
    cin >> input;
    Hive* hive = new Hive();
    stringstream stream(input);
    string direction;
    char buffer;
    while (stream >> buffer) {
        direction += buffer;
        if (stream.peek() == ',') {
            stream.ignore();
            hive->step(string_to_direction(direction));
            direction = "";
        }
    }
    hive->step(string_to_direction(direction));
    cout << "Part 1: " << part1(hive) << endl;
    cout << "Part 2: " << part2(hive) << endl;
}
