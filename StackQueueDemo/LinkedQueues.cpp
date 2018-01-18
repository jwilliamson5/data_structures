// LinkedQueues.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//
//  main.cpp
//  Linked Queues
//
//  Created by Hal O'Connell on 2013-01-21.
//  Copyright (c) 2013 Hal O'Connell. All rights reserved.
//

#include <iostream>

using namespace std;

class QueueNode
{
private:
    int _data;
    QueueNode* _next;
public:
    QueueNode() : _data(0), _next(NULL) {}
    QueueNode( int data, QueueNode* next ) : _data(data), _next(next) {}
    virtual ~QueueNode() {}
    
    int getData() { return _data; }
    void setData( int data ) { _data = data; }
    
    QueueNode* getNext() { return _next; }
    void setNext( QueueNode* next ) { _next = next; }
};

class Queue
{
private:
    QueueNode* _first;
    QueueNode* _last;
    
public:
    Queue() : _first(NULL), _last(NULL) {}
    virtual ~Queue()
    {
        while( _first != NULL )
        {
            Serve();
        }
    }
    
    void Add( int num )
    {
        QueueNode* node = new QueueNode();
        node->setData(num);
        
        if( _first == NULL )
        {
            _first = node;
        }
        else
        {
            _last->setNext( node );
        }
        
        _last = node;
    }
    
    int Peek()
    {
        return _first->getData();
    }
    
    void Serve()
    {
        QueueNode* node = _first;
        _first = _first->getNext();
        delete node;
    }
    
    friend ostream& operator<<( ostream& output, Queue& queue );
};

ostream& operator<<( ostream& output, Queue& queue )
{
    QueueNode* node = queue._first;
    
    while( node != NULL )
    {
        cout << node->getData() << endl;
        
        node = node->getNext();
    }
    
    return output;
}

int main()
{
    // test 1: push nodes on to queue
    Queue queue;
    
    queue.Add( 1 );
    queue.Add( 2 );
    queue.Add( 3 );
    queue.Add( 4 );
    queue.Add( 5 );
    queue.Add( 6 );
    queue.Add( 7 );
    queue.Add( 8 );
    
    cout << "Queued values:" << endl;
    cout << queue;
    
    // test 2: peek/pop nodes from queue
    
    cout << "The head of the queue is: " << queue.Peek() << endl;
    
    queue.Serve();
    
    cout << "The new head of the queue is: " << queue.Peek() << endl;

	cout << "Queued values now:" << endl;
	cout << queue;
	cin.ignore();
    return 0;
}
