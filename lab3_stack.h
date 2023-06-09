#pragma once
#include <iostream>

using namespace std;

template<typename T>
class TNode {
public:
    T val;
    TNode<T>* next;

    TNode(T val) {
        this->val = val;
        this->next = nullptr;
    }
};

template<typename T>
class Stack {
private:
    TNode<T>* top_node;

public:
    Stack() {
        this->top_node = nullptr;
    }

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

    bool empty() {
        return top_node == nullptr;
    }

    void push(T val) {
        TNode<T>* new_node = new TNode<T>(val);
        new_node->next = top_node;
        top_node = new_node;
    }

    int pop() {
        if (!empty()) {
            TNode<T>* temp = top_node;
            top_node = top_node->next;
            delete temp;
        }
        return 0;
    }

    int size() {
        int count = 0;
        TNode<T>* current = top_node;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    T top() {
        if (!empty()) {
            return top_node->val;
        }
        else {
            throw "Stack is empty";
        }
    }
};

