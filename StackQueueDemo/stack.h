#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include "stacknode.h"

using namespace std;
enum myerror_code { success, underflow, overflow };

class Stack
{
private:
    StackNode *_top;

public:
    Stack();
    virtual ~Stack();

    myerror_code Push( int num );
    int Peek();
    myerror_code Pop();

    friend ostream& operator<<( ostream& output, Stack& stack );
};

#endif
