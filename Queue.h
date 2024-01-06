//
// Created by PC on 12/11/2023.
//
#pragma once
#ifndef PROJECT_UNIVERSITY_QUEUE_H
#define PROJECT_UNIVERSITY_QUEUE_H


#include <iostream>
using namespace std;

template <typename T>
class Queue {
private:
    class Node {
    public:
        T value;
        Node* next;
        Node(T value) : value(value), next(nullptr) {}
    };
    Node* front;
    Node* rear;
    int size;
public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    ~Queue();
    int getSize() const;
    void enqueue(T item);
    T dequeue();
    bool isEmpty() const;
    T peek();
    void display();
};


#endif //PROJECT_UNIVERSITY_QUEUE_H
