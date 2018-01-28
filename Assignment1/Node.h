#ifndef ASSIGNMENT1_NODE_H
#define ASSIGNMENT1_NODE_H

#include <iostream>

class Node {
public:
    std::string data;
    Node *next;
    Node():data(""), next(nullptr) {}

};


#endif //ASSIGNMENT1_NODE_H
