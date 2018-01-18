//
//  main.cpp
//  linkedlist
//
//  Created by Hal O'Connell on 2012-10-29.
//  Copyright (c) 2012 Hal O'Connell. All rights reserved.
//
#include <iostream>
#include "llist.h"

using namespace std;
int main()
{
    // test 1: adding new nodes

    LinkedList list;

    list.Add(3);
    list.Add(5);
    list.Add(1);
    list.Add(7);
    list.Add(9);
    list.Add(13);
    list.Add(20);

    cout << "The list contains the following numbers: " << endl << endl;
    cout << list;

    // test 2: delete a node

    cout << "\nDeleting...." << endl;

    list.DeleteValue(1);
    list.DeleteNode(2);

    cout << "The list contains the following numbers: " << endl << endl;
    cout << list;

    // test 3: insert a node

    cout << "\nInserting...." << endl;

    // tests to insert after valid node
    list.InsertAfterValue(3, 10);
    // test to insert after non-existent node
    list.InsertAfterValue(25, 33);
    list.InsertBeforeNode(5,11);

    cout << "The list contains the following numbers: " << endl << endl;
    cout << list;
    cin.ignore();
    return 0;
}

















