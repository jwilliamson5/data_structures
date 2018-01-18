//
// Created by prog2100 on 08/01/18.
//

#ifndef LINKEDLIST_LLIST_H
#define LINKEDLIST_LLIST_H
#include <iostream>
#include "node.h"

using namespace std;

class LinkedList {
private:
    Node *first;

public:
    LinkedList();

    virtual ~LinkedList();

    void Add(int num);

    void DeleteValue(int value);

    void DeleteNode(int nodenum);

    void InsertAfterValue(int value, int num);
    void InsertBeforeNode(int nodenum, int num);
    friend ostream &operator<<(ostream &output, LinkedList &list);
};

#endif //LINKEDLIST_LLIST_H