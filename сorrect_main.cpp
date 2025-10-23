#include <iostream>
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

// Forward declaration
class LinkedList;

///Stack implementation using LinkedList
class Stack {
private:
    LinkedList* list;

public:
    Stack();
    ~Stack();
    void push(int x);
    int pop();
    int peek();
    bool isEmpty();
};

///Queue implementation using LinkedList
class Queue {
private:
    LinkedList* list;

public:
    Queue();
    ~Queue();
    void enqueue(int new_data);
    int dequeue();
    int getfront();
    bool isEmpty();
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

    // Remove at position using Queue
    // Strategy: Use queue to store all elements except the one at position
    bool removeAtPos(int position) {
        if (head == nullptr || position < 0) {
            return false;
        }

        Queue q;
        Node* current = head;
        int index = 0;
        bool found = false;

        // Enqueue all elements into the queue
        while (current != nullptr) {
            if (index == position) {
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

    // Remove first element
    bool removeFirst() {
        return removeAtPos(0);
    }
    //****

    // Remove last element using Stack
    // Strategy: Use stack to count size, then remove at (size-1) position
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

// Stack implementation
Stack::Stack() {
    list = new LinkedList();
}

Stack::~Stack() {
    delete list;
}

void Stack::push(int x) {
    list->prepend(x); // Add to beginning (top of stack)
}  // Big-O notation : O(1)

int Stack::pop() {
    if (isEmpty()) {
        return -1;
    }
    Node* first = list->iterate(0);
    if (first == nullptr) return -1;
    int val = first->data;
    list->removeFirst(); // Remove first element
    return val;
} // Big-O notation : O(1)

int Stack::peek() {
    if (isEmpty()) {
        cout << "Stack is Empty" << endl;
        return -1;
    }
    Node* first = list->iterate(0);
    return first ? first->data : -1;
} // Big-O notation : O(1)

bool Stack::isEmpty() {
    return list->size() == 0;
}

// Queue implementation
Queue::Queue() {
    list = new LinkedList();
}

Queue::~Queue() {
    delete list;
}

void Queue::enqueue(int new_data) {
    list->append(new_data); // Add to end (rear of queue)
}

int Queue::dequeue() {
    if (isEmpty()) {
        return -1;
    }

    Node* first = list->iterate(0);

    if (first == nullptr) {
        return -1;
    }

    int val = first->data;
    list->removeFirst(); // Remove first element
    return val;
}

int Queue::getfront() {
    if (isEmpty()) {
        cout << "Empty" << endl;
        return -1;
    }

    Node* first = list->iterate(0);

    if (first != nullptr) {
        return first->data;
    }
    else {
        return -1;
    }
}

bool Queue::isEmpty() {
    return list->size() == 0;
}

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
Terminal display :

Linked List: 5 -> 10 -> 15 -> 20 -> 30 -> NULL
Contains 20? Yes
After removing 20: 5 -> 10 -> 15 -> 30 -> NULL



*/
