#include "LinkedList.h"


template <typename T>
int LinkedList<T>::getSize() {
    return size;
}

template <typename T>
void LinkedList<T>::setSize(int size) {
    this->size = size;
}

template <typename T>
void LinkedList<T>::display() {
    auto temp = head;
    while (temp != nullptr){
        cout << temp->value << " ";
        temp = temp->next;
    }
}

template <typename T>
void LinkedList<T>::add_first(T item) {
    Node* n = new Node(item);
    if (isEmpty()) {
        head = n;
        tail = n;
    }
    else{
        n->next = head;
        head = n;
    }
    size ++;
}

template <typename T>
void LinkedList<T>::add_last(T item) {
    Node* n = new Node(item);
    if (isEmpty()){
        head = n;
        tail = n;
    }
    else{
        tail->next = n;
        tail = n;
    }
    size ++;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    auto temp = head;
    while (temp != nullptr){
        auto next = temp->next;
        delete temp;
        temp = next;
    }
}

template <typename T>
int LinkedList<T>::find(T key) {
    Node* temp = head;
    int index = 0;
    while (temp != nullptr) {
        if (temp->value == key) {
            return index;
        } else {
            index++;
            temp = temp->next;
        }
    }
    return -1;
}

template <typename T>
void LinkedList<T>::delete_first() {
    if (head == tail){
        head = tail = nullptr;
        size = 0;
        return;
    } else if (isEmpty()) {
        return;
    }else{
        Node *second = head->next;
        head->next = nullptr;
        head = second;
        size--;
    }
}

template <typename T>
void LinkedList<T>::delete_last() {
    if (head == tail) {
        head = tail = nullptr;
        size = 0;
        return;
    }else if (isEmpty()){
        return;
    } else {
        auto temp = head;
        while (true) {
            if (temp->next->next == nullptr) {
                auto before_last = temp;
                before_last->next = nullptr;
                tail = before_last;
                break;
            } else {
                temp = temp->next;
            }
        }
        size--;
    }
}

template <typename T>
bool LinkedList<T>::contains(T item) {
    return (find(item) != -1);
}

template <typename T>
T* LinkedList<T>::to_array() {
    T* linked_list_array = new T[size];
    auto temp = head;
    int index = 0;
    while (temp != nullptr) {
        linked_list_array[index++] = temp->value;
        temp = temp->next;
    }
    return linked_list_array;
}

// [10 -> 20 -> 30]

template <typename T>
void LinkedList<T>::reverse() {
    if (isEmpty()) return;
    auto previous = head;
    auto current = head->next;

    previous->next = nullptr;

    while (current != nullptr) {
        auto backup = current->next;
        current->next = previous;
        previous = current;
        current = backup;
    }
    tail = head;
    tail->next = nullptr;
    head=previous;
}

template <typename T>
T LinkedList<T>::get_kth_from_the_end(int k) {
    if (k > size || k <= 0) return -1;
    auto first = head;
    auto kth = first;
    for (int i = 1; i < k; i++) {
        kth = kth->next;
    }
    while (kth->next != nullptr) {
        first = first->next;
        kth=kth->next;
    }
    return first->value; // use T as the return type
}