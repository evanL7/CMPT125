#include "Stack.h"
#include <iostream>
using namespace std;

/*
	Problem 1

	This program is the cpp file that implements a stack as a class.

	Author Evan Law August 4, 2023;
*/

void Stack::push(int value)
{
	insertFront(value);
}

void Stack::pop()
{
	removeFront();
}

int Stack::peek()
{
	if (LinkedList::isEmpty()) // Catches error if stack is empty
	{
		cout << "Stack is empty." << endl;
		return -1;
	}
	else
	{
		top = get_head();
		return top->data;
	}
}

bool Stack::isEmpty()
{
	return LinkedList::isEmpty();
}

void Stack::display()
{
	printList();
}

Stack::~Stack()
{
	// LinkedList destructor deals with memory deallocation
	// because top node of stack class is only used to access the head node of the LinkedList
	// with get_head method.
	top = nullptr;
}