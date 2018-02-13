//
// Created by jwill on 2018-02-12.
//

#ifndef ASSIGNMENT_2_STACK_H
#define ASSIGNMENT_2_STACK_H

#include "Node.h"

enum stackerror_code { success, underflow, overflow };

//First time using templates, so only way I could get it to work was put all the implementation
//into the same file
template <class T>
class Stack {
private:
    Node<T> *_top;
public:
    Stack(): _top(nullptr) {};

    Stack(const Stack<T> &stack2) {
        auto* cursor = stack2._top;
        _top = cursor;
        while(cursor->next != nullptr) {
            auto* next = cursor->next;
            cursor->next = next;
            cursor = cursor->next;
        }
    }

    virtual ~Stack() {
        while(_top != nullptr) {
            Pop();
        }
    };


    stackerror_code Push(T *data) {
        _top = new Node<T>(data, _top);
        return(success);
    }

    Node<T>* Peek() {
        return _top;
    };

    stackerror_code Pop() {
        if(_top != nullptr) {
            Node<T>* node = _top;
            _top = _top->next;
            delete node;
            return(success);
        } else {
            return underflow;
        }
    };
};

#endif //ASSIGNMENT_2_STACK_H
