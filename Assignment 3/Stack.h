#ifndef StackFlag
#define StackFlag

#include "LinkedList.h"

/*
	Problem 1

	This program is the header file that implements a stack as a class.

	Author Evan Law August 4, 2023;
*/

class Stack : public LinkedList { // Added inheritance to use the methods of the LinkedList class
private:
	Node* top;

public:
	Stack(): top(nullptr) {}

	// Push an element onto the stack
	void push(int value);

	// Pop the top element from the stack
	void pop();

	// Get the value of the top element without removing it
	int peek();

	// Check if the stack is empty
	bool isEmpty();

	// Display the stack elements
	void display();

	// Destructor to free memory
	~Stack();
};

#endif
