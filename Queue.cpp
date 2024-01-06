//
// Created by PC on 12/11/2023.
//

#include "Queue.h"
#include "Event.h"
#include "PriorityQueue.h"

template
class Queue<Event *>;

template
class Queue<Passenger *>;

template
class Queue<Bus *>;

template<typename T>
Queue<T>::~Queue() {
    Node *temp = front;
    while (temp != nullptr) {
        Node *next = temp->next;
        delete temp;
        temp = next;
    }
}

template<typename T>
void Queue<T>::enqueue(T item) {
    Node *n = new Node(item);
    if (isEmpty()) {
        front = rear = n;
    } else {
        rear->next = n;
        rear = n;
    }
    size++;
}

template<typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
         return nullptr;
    }

    Node *temp = front;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    T dequeuedValue = temp->value;
    delete temp;
    size--;

    return dequeuedValue;
}

template<typename T>
int Queue<T>::getSize() const {
    return size;
}


template<typename T>
bool Queue<T>::isEmpty() const {
    return (front == nullptr && rear == nullptr);
}

template<typename T>
T Queue<T>::peek() {
    if (isEmpty()) {
        // Return a special value for an empty queue (nullptr for pointers)
        return nullptr;  // Assuming T is a pointer type
    }

    return front->value;
}

template<typename T>
void Queue<T>::display() {
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
        return;
    }

    cout << "Queue elements are: ";
    Node *temp = front;
    while (temp != nullptr) {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << endl;
}