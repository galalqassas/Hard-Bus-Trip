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
public:
    PriorityQueue() { head = nullptr; }
    ~PriorityQueue();
    void enqueuePQ(T item, int priority);
    void dequeuePQ();
    bool isEmpty();
    T peek();
    void display();
};


#endif //PROJECT_UNIVERSITY_PRIORITYQUEUE_H
