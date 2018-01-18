#include "stdafx.h"
#include <iostream>
#include "stacknode.h"

using namespace std;

StackNode::StackNode() : _data(0), _next(NULL) 
{
}

StackNode::StackNode( int data, StackNode* next ) : _data(data), _next(next) 
{
}

StackNode::~StackNode() 
{
}

int StackNode::getData() 
{ 
    return _data; 
}

void StackNode::setData( int data ) 
{ 
    _data = data; 
}

StackNode* StackNode::getNext() 
{ 
    return _next; 
}

void StackNode::setNext( StackNode *next ) 
{ 
    _next = next; 
}
