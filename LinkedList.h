#ifndef FOR_TRYING_LINKEDLIST_H
#define FOR_TRYING_LINKEDLIST_H
#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
private:
    class Node{
    public:
        T value;
        Node* next;
        Node(T value): value(value), next(nullptr){}
    };
    Node* head;
    Node* tail;
    bool isEmpty(){
        return (head == nullptr);
    }
    int size;
public:
    int getSize();
    void setSize(int size);
    LinkedList(){head = nullptr; tail = nullptr; size = 0;} // initialize size to 0
    ~LinkedList();
    void add_first(T item);
    void add_last(T item);
    void display();
    void delete_first();
    void delete_last();
    bool contains(T item);
    int find(T key);
    T* to_array();
    void reverse();
    T get_kth_from_the_end(int k);
};

#endif //FOR_TRYING_LINKEDLIST_H