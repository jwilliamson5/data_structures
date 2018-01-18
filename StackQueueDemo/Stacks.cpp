// Stacks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "stack.h"

using namespace std;
void pr_error(myerror_code err)
// Generic error print routine
{
	switch (err) {
	case overflow: {
		cout << "Error encountered: stack overflow" << endl;
		}
	case underflow: {
		cout << "Error encountered: stack underflow" << endl;
		}
	}

}

int main()
{
    // test 1: push on to stack
    Stack stack;
	Stack stack2; // use this one just to force errors

	myerror_code err;

    err = stack.Push( 32 );
	if (err != success) pr_error(err); // just a sample of catching a returning error code
    stack.Push( 12 );
    stack.Push( 87 );
    stack.Push( 26 );
    stack.Push( 91 );

    // verify contents of stack
    cout << stack;

    // test 2: peek/pop from stack
    cout << "The first node on the stack is: ";
    cout << stack.Peek() << endl;

    // remove the first node
    cout << "First node removed." << endl;
    stack.Pop();

    // show new top of stack
    cout << "The new first node on the stack is: ";
    cout << stack.Peek() << endl;
	cin.ignore();

	// Now going to force an underflow error with stack2
	// There is no data, so a Pop should fail
	err = stack2.Pop();
	if (err != success) pr_error(err); // just a sample of catching a returning error code

	cout << "Ending..." << endl;
	cin.ignore();

    return 0;
}












