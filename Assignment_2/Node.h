//
// Created by jwill on 2018-02-08.
//

#ifndef ASSIGNMENT_2_NODE_H
#define ASSIGNMENT_2_NODE_H

template <class T>
class Node {
public:
    Node *next;
    T *data;
    Node(): data(nullptr), next(nullptr) {}
    Node(T *data, Node<T> *next):data(data), next(next) {};
    virtual ~Node() = default;
};


#endif //ASSIGNMENT_2_NODE_H
