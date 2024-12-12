
#include <iostream>
#include <set>

using namespace std;

class Node {
public:
    long long int value;
    Node* prev;
    Node* next;
    
    Node(long long int val) : value(val), prev(nullptr), next(nullptr) {}

    int getDigitCount() const {
        return to_string(value).length();
    }

    void setValue(long long int newValue) {
        value = newValue;
    }

    long long int firstHalfValue() const {
        string numStr = to_string(value);
        string firstHalf = numStr.substr(0, numStr.length() / 2);
        if (firstHalf.empty()) {
            return 0;
        }
        long long int newValue = stoll(firstHalf);
        return newValue;
    }

    long long int secondHalfValue() const {
        string numStr = to_string(value);
        string secondHalf = numStr.substr(numStr.length() / 2);
        if (secondHalf.empty()) {
            return 0;
        }
        long long int newValue = stoll(secondHalf);
        return newValue;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void swapOneForTwo(Node* targetNode, Node* replacement1, Node* replacement2) {
        // Link the replacement nodes to each other
        replacement1->next = replacement2;
        replacement2->prev = replacement1;
        
        // Link with previous node
        replacement1->prev = targetNode->prev;
        if (targetNode->prev != nullptr) {
            targetNode->prev->next = replacement1;
        } else {
            head = replacement1;  // If replacing first node
        }
        
        // Link with next node
        replacement2->next = targetNode->next;
        if (targetNode->next != nullptr) {
            targetNode->next->prev = replacement2;
        } else {
            tail = replacement2;  // If replacing last node
        }
        
        // Clear the old node's connections
        targetNode->prev = nullptr;
        targetNode->next = nullptr;
        
        size++;  // Size increases by 1 (replacing 1 with 2)
    }
    
    void pushBack(long long int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    void pushFront(long long int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void blink() {
        Node* current = head;
        
        while (current != nullptr) {
            // Change to 1
            if (current->value == 0) {
                current->setValue(1);
            }
            // Split into two nodes
            else if (current->getDigitCount() % 2 == 0) {
                Node* node1 = new Node(current->firstHalfValue());
                Node* node2 = new Node(current->secondHalfValue());
                swapOneForTwo(current, node1, node2);
                delete current;
                current = node2;
            }
            // Multiply by 2024
            else {
                current->setValue(current->value * 2024);
            }
            current = current->next;
        }
    }
    
    int getSize() const {
        return size;
    }
    
    void printForward() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->value;
            if (current->next != nullptr) cout << " <-> ";
            current = current->next;
        }
        cout << endl << "Size=" << getSize() << endl << endl;
    }
    
    void printBackward() const {
        Node* current = tail;
        while (current != nullptr) {
            cout << current->value;
            if (current->prev != nullptr) cout << " <-> ";
            current = current->prev;
        }
        cout << endl;
    }
};

DoublyLinkedList prepList() {
    DoublyLinkedList list;

    long long int input;

    while (cin >> input) {
        list.pushBack(input);
    }

    return list;
}

int run(int numBlinks) {
    DoublyLinkedList list = prepList();
    
    // list.pushBack(1);
    // list.pushBack(2);
    // list.pushFront(0);
    
    // list.printForward();  // Outputs: 0 <-> 1 <-> 2
    // list.printBackward(); // Outputs: 2 <-> 1 <-> 0
    
    // list.remove(1);
    // list.printForward();  // Outputs: 0 <-> 2

    // list.printForward();

    for (int i = 1; i <= numBlinks; i++) {
        cout << "blink " << i << endl;
        list.blink();
        list.printForward();
    }
    
    return list.getSize();
}

int solution1() {
    return run(25);
}

int solution2() {
    return run(75);
}

int testSequence(int steps, bool firstHalf) {
    Node* node = new Node(0);

    cout << "Start\t" << node->value << endl;

    for (int step = 1; step <= steps; step++) {
        // Change to 1
        if (node->value == 0) {
            node->setValue(1);
        }
        // Split into two nodes
        else if (node->getDigitCount() % 2 == 0) {
            node->setValue(firstHalf ? node->firstHalfValue() : node->secondHalfValue());
        }
        // Multiply by 2024
        else {
            node->setValue(node->value * 2024);
        }
        cout << "Step " << step << "\t" << node->value << endl;
    }
    return node->value;
}

int testAllValues() {
    // set<int> values;
    // set<int> values = {5, 2, 8, 2};  // Will contain {2, 5, 8}
    // set<long long int> values = {0};
    // set<long long int> values = {125, 17};
    // set<long long int> values = {8069LL, 87014LL, 98LL, 809367LL, 525LL, 0LL, 9494914LL, 5LL};
    set<long long int> values = {8069, 87014, 98, 809367, 525, 0, 9494914, 5};

    int size = values.size();

    int loop = 1;
    while (true) {
        cout << "loop " << loop << ": " << values.size() << " values" << endl;
        // Range doesn't work if we're modifying the set within the loop
        // for (const int& value : values) {
        // Need to iterate like this:
        for (auto it = values.begin(); it != values.end(); ++it) {
            long long int value = *it;
            // cout << "\t" << value << endl;
            // Change to 1
            if (value == 0) {
                values.insert(1);
            } else {
                Node node(value);
                // Split into two nodes
                if (node.getDigitCount() % 2 == 0) {
                    // cout << "splitskis: " << endl;
                    // cout << "\t\t" << node.firstHalfValue() << endl;
                    // cout << "\t\t" << node.secondHalfValue() << endl;
                    long long int newValue = node.firstHalfValue();
                    values.insert(newValue);
                    newValue = node.secondHalfValue();
                    values.insert(newValue);
                }
                // Multiply by 2024
                else {
                    // cout << "mult: " << endl;
                    long long int newValue = value * 2024LL;
                    // cout << "\t\t" << newValue << endl;
                    values.insert(newValue);
                }
            }
        }
        if (values.size() == size) { 
            break;
        }
        size = values.size();
        loop++;
    }
    cout << "done" << endl;
    return size;
}

int main() {
    // cout << solution1() << endl;
    // cout << solution2() << endl;
    // testSequence(100, true);
    // testSequence(100, false);
    cout << testAllValues() << endl;
    return 0;
}
