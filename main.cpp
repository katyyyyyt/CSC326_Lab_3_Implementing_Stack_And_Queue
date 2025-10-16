#include <iostream>
//#include <stack> //Adding stack library
//#include <queue> //Adding queue library

using namespace std;
//Lab 3 Implementing Queue and Stack
//Kateryna Taranenko

class Node {
public:
    int data;
    Node* next;
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList() {
        head = nullptr;
    }
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
    // Iterate to a given position (0-based index)
    Node* iterate(int position) {
        if (position < 0) return nullptr;
        Node* current = head;
        int index = 0;
        while (current != nullptr && index < position) {
            current = current->next;
            index++;
        }
        return current; // nullptr if not found
    }
    // Insert at positions
    void insertAt(int position, int value) {
        Node* newNode = new Node(value);
        if (position <= 0 || head == nullptr) { // Insert at beginning
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* prev = iterate(position - 1);
        if (prev == nullptr) { // Position too big, append at end
            append(value);
            delete newNode; // already appended, avoid memory leak
            return;
        }
        newNode->next = prev->next;
        prev->next = newNode;
    }
    // Prepend (beginning)
    void prepend(int value) {
        insertAt(0, value);
    }
    // Append (end)
    void append(int value) {
        if (head == nullptr) {
            head = new Node(value);
            return;
        }
        Node* last = iterate(size() - 1);
        last->next = new Node(value);
    }
    // Find node by value
    Node* find(int value) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == value)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }
    // Contains (true/false)
    bool contains(int value) {
        return find(value) != nullptr;
    }
    // Remove by value
    bool remove(int value) {
        if (head == nullptr) return false;
        // Special case: head
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        // Find previous node of the target
        int index = 0;
        Node* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->next->data == value) {
                Node* target = current->next;
                current->next = target->next;
                delete target;
                return true;
            }
            current = current->next;
            index++;
        }
        return false; // Not found
    }
    //*** My implementation

    // Remove from position
    //The best option to use the queue here
    bool removeAtPos(int value) {
    // Check if list is empty
        if (head == nullptr) 
        {
            return false;
        }
        
        // If removing first element (position 0)
        if (position == 0) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        
        // Find the node before the one we want to remove
        Node* prev = iterate(position - 1);
        
        // If position is out of bounds
        if (prev == nullptr || prev->next == nullptr) {
            return false;
        }
        
        // Remove the node at position
        Node* toDelete = prev->next;
        prev->next = toDelete->next;
        delete toDelete;
        return true;
    }

    //****
    

    //Remove from position
    bool removeFirst() {
       removeAtPos(0);

    }
    //****


    // Remove from last position
    // The best option here is to use Stack implementation

    bool removeLast() {
        //head here is our top
        // Check if list is empty
        if (head == nullptr) {
            return false;
        }
        
        // If only one element
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return true;
        }
        
        // Find second to last node
        Node* current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        
        // Delete last node
        delete current->next;
        current->next = nullptr;
        return true;
    }


    //***********
    // 
    // Get size
    int size() {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    // Display
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};
int main() {
    LinkedList list;
    list.append(10);
    list.append(20);
    list.append(30);
    list.prepend(5);
    list.insertAt(2, 15);
    cout << "Linked List: ";
    list.display();
    cout << "Contains 20? " << (list.contains(20) ? "Yes" : "No") << endl;
    list.remove(20);
    cout << "After removing 20: ";
    list.display();
    return 0;
}



