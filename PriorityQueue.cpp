//
// Created by PC on 12/11/2023.
//

#include "PriorityQueue.h"
#include "Station.h"
#include "Queue.cpp"
#include "Passenger.h"
#include "Bus.h"
template class PriorityQueue<Passenger*>;
template class PriorityQueue<Bus*>;
template <typename T>
PriorityQueue<T>::~PriorityQueue() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
}

template <typename T>
void PriorityQueue<T>::enqueuePQ(T item, int priority) {
    Node* n = new Node(item, priority);
    if (isEmpty() || n->priority > head->priority) {
        n->next = head;
        head = n;
        size++;
    }
    else {
        Node* temp = head;
        while (temp->next != nullptr && temp->next->priority >= n->priority) {
            temp = temp->next;
        }
        n->next = temp->next;
        temp->next = n;
        size++;
    }
}

template <typename T>
T PriorityQueue<T>::dequeuePQ() {
    if (isEmpty()) {
        cout << "Empty Queue";
    }
    Node* temp = head;
    T dequeuedItem = head->value;
    head = head->next;
    delete temp;
    size--;
    return dequeuedItem;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const {
    return (head == nullptr);
}

template <typename T>
T PriorityQueue<T>::peek() {
    if (isEmpty()) {
        cout << "Empty Queue";
    }
    return head->value;
}

template <typename T>
void PriorityQueue<T>::display() {
    if (isEmpty()) {
        cout << "Queue is empty" << endl;
        return;
    }
    cout << "Queue elements are: ";
    Node* temp = head;
    while (temp != nullptr) {
        cout << "(" << temp->value << ", " << temp->priority << ") ";
        temp = temp->next;
    }
    cout << endl;
}

template <typename T>
int PriorityQueue<T>::getSize() const {
    return size;
}

template <typename T>
void PriorityQueue<T>::removeItem(T item) {
    Node* temp = head;
    Node* prev = nullptr;

    while (temp != nullptr) {
        if (temp->value == item) {
            if (prev == nullptr) {
                // Item is at the head
                head = head->next;
            } else {
                // Item is in the middle or end
                prev->next = temp->next;
            }

            delete temp;
            size--;

            if (prev == nullptr) {
                // If we removed the head, update temp to new head
                temp = head;
            } else {
                // Otherwise, continue from the next node
                temp = prev->next;
            }
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}