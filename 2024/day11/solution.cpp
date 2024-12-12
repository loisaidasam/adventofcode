
#include <iostream>

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
        return firstHalf.empty() ? 0 : stoll(firstHalf);
    }

    long long int secondHalfValue() const {
        string numStr = to_string(value);
        string secondHalf = numStr.substr(numStr.length() / 2);
        return secondHalf.empty() ? 0 : stoll(secondHalf);
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
    
    // void remove(int value) {
    //     Node* current = head;
        
    //     while (current != nullptr) {
    //         if (current->value == value) {
    //             if (current->prev != nullptr) {
    //                 current->prev->next = current->next;
    //             } else {
    //                 head = current->next;
    //             }
                
    //             if (current->next != nullptr) {
    //                 current->next->prev = current->prev;
    //             } else {
    //                 tail = current->prev;
    //             }
                
    //             delete current;
    //             size--;
    //             return;
    //         }
    //         current = current->next;
    //     }
    // }
    
    // bool contains(int value) const {
    //     Node* current = head;
    //     while (current != nullptr) {
    //         if (current->value == value) return true;
    //         current = current->next;
    //     }
    //     return false;
    // }
    
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

long long int solution1() {
    DoublyLinkedList list;

    long long int input;

    while (cin >> input) {
        list.pushBack(input);
    }
    
    // list.pushBack(1);
    // list.pushBack(2);
    // list.pushFront(0);
    
    // list.printForward();  // Outputs: 0 <-> 1 <-> 2
    // list.printBackward(); // Outputs: 2 <-> 1 <-> 0
    
    // list.remove(1);
    // list.printForward();  // Outputs: 0 <-> 2

    // list.printForward();

    for (int i = 1; i <= 25; i++) {
        // cout << "blink " << i << endl;
        list.blink();
        // list.printForward();
    }
    
    return list.getSize();
}

int solution2() {
    return 0;
}

int main() {
    cout << solution1() << endl;
    // cout << solution2() << endl;
    return 0;
}
