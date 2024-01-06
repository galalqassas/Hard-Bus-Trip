//
// Created by PC on 12/11/2023.
//
#pragma once
#ifndef PROJECT_UNIVERSITY_PRIORITYQUEUE_H
#define PROJECT_UNIVERSITY_PRIORITYQUEUE_H


#include <iostream>
using namespace std;

template <typename T>
class PriorityQueue {
private:
    class Node {
    public:
        T value;
        Node* next;
        int priority;
        Node(T value, int priority): value(value), next(nullptr), priority(priority) {}
    };
    Node* head;
    int size;
public:
    PriorityQueue() : head(nullptr), size(0) {}
    ~PriorityQueue();
    void enqueuePQ(T item, int priority);
    T dequeuePQ();
    bool isEmpty() const;
    T peek();
    void display();
    int getSize() const;
};


#endif //PROJECT_UNIVERSITY_PRIORITYQUEUE_H
