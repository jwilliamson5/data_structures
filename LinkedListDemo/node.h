//
// Created by prog2100 on 08/01/18.
//

#ifndef LINKEDLIST_NODE_H
#define LINKEDLIST_NODE_H


class Node
{
public:
    int data;
    Node *next;

    Node() : next(nullptr), data(-1) {}
};


#endif //LINKEDLIST_NODE_H