#include <iostream>

using namespace std;

template<typename T>
class Node {
public:
    T val;
    Node<T>* next;

    Node(T val) {
        this->val = val;
        this->next = nullptr;
    }
};

template<typename T>
class Queue {
private:
    Node<T>* front_node;
    Node<T>* rear_node;

public:
    Queue() {
        this->front_node = nullptr;
        this->rear_node = nullptr;
    }

    ~Queue() {
        while (!empty()) {
            pop();
        }
    }

    bool empty() {
        return front_node == nullptr;
    }

    void push(T val) {
        Node<T>* new_node = new Node<T>(val);

        if (empty()) {
            front_node = new_node;
            rear_node = new_node;
        }
        else {
            rear_node->next = new_node;
            rear_node = new_node;
        }
    }

    void pop() {
        if (!empty()) {
            Node<T>* temp = front_node;

            if (front_node == rear_node) {
                front_node = nullptr;
                rear_node = nullptr;
            }
            else {
                front_node = front_node->next;
            }

            delete temp;
        }
    }

    int size() {
        int count = 0;
        Node<T>* current = front_node;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    T front() {
        if (!empty()) {
            return front_node->val;
        }
        else {
            throw "Queue is empty";
        }
    }

    T rear() {
        if (!empty()) {
            return rear_node->val;
        }
        else {
            throw "Queue is empty";
        }
    }
};
