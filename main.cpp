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

///My implementation

class Stack {
private:
    Node* top;
    int count;

public :
    Stack() { //stack constructor 

        // initially stack is empty
        top = nullptr;
        count = 0; //size of the stack
    }

    //***

    void push(int x) {
        Node* temp = new Node(x);
        temp->next = top;
        top = temp;
        count++;
    }  // Big-O notation : O(1)


    //***

    int pop() {

        if (top == NULL) {
            return -1;
        }

        Node* temp = top;
        top = top->next;
        int val = temp->data;

        count--;
        delete temp;
        return val;
        // Big-O notation : O(1)
    }

    //***

    int peek() {

        if (top == NULL) {
            cout << "Stack is Empty" << endl;
            return -1;
        }

        return top->data;
    }
    //Big-O notation : O(1)

    bool isEmpty() {
        return top == nullptr;
    }
};


/************/
class Queue {
private:
    Node* front;
    Node* rear;
    int count;

public:
    Queue() {
        front = rear = nullptr;
        count = 0;
    }

    //***

    void enqueue(int new_data) {
        Node* node = new Node(new_data);

        if (front == nullptr) {
            front = rear = node;
        }
        else {
            rear->next = node;
            rear = node;
        }
        count++;
    }

    //***

    int dequeue() {

        if (front == nullptr) {
            return -1;
        }

        Node* temp = front;
        int removedData = temp->data;
        front = front->next;

        if (front == nullptr)
        rear = nullptr;
        delete temp;
        return removedData;
    }
    
    //***

    int getfront() {
        if (front == nullptr) {
            cout << "Empty" << endl;
            return -1;
        }
        return front->data;
    }

    bool isEmpty() {
        return front == nullptr;
    }

};



//////////
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
    //The best option to use queue here
    bool removeAtPos(int value) {
            if (head == nullptr || value < 0) {
                return false;
            }

            Queue q;
            Node* current = head;
            int index = 0;
            bool found = false;

            // Enqueue all elements into the queue
            while (current != nullptr) {
                if (index == value) {
                    // Skip this element (don't enqueue it)
                    found = true;
                }
                else {
                    q.enqueue(current->data);
                }
                current = current->next;
                index++;
            }

            if (!found) {
                return false; // Position out of bounds
            }

            // Clear the original list
            while (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }

            // Rebuild the list from queue
            while (!q.isEmpty()) {
                append(q.dequeue());
            }

            return true;
            
        }
        



    //****
    

    //Remove from position
    bool removeFirst(){
        removeAtPos(0);
        
    }
    //****


    // Remove from last position
    // The best option here is to use Stack implementation

    bool removeLast() {
        if (head == nullptr) {
            return false;
        }

        // Use stack to count the size
        Stack s;
        Node* current = head;

        while (current != nullptr) {
            s.push(current->data);
            current = current->next;
        }

        // Count how many elements we pushed
        int count = 0;
        while (!s.isEmpty()) {
            s.pop();
            count++;
        }

        // Remove at position (count - 1)
        return removeAtPos(count - 1);
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

/*
*

Linked List: 5 -> 10 -> 15 -> 20 -> 30 -> NULL
Contains 20? Yes
After removing 20: 5 -> 10 -> 15 -> 30 -> NULL


*/
