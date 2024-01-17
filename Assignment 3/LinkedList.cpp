#include "LinkedList.h"
#include <iostream>
using namespace std;

/*
	Problem 1

	This program is the cpp file that implements a linked list as a class.

	Author Evan Law August 4, 2023;
*/

// Initialization list for efficiency
LinkedList::LinkedList()
	: head(nullptr)
{}

LinkedList::~LinkedList()
{
	Node* current;
	current = head;

	while (head != nullptr)
	{
		current = head;
		head = head->next;
		delete current;
	}
	head = nullptr; // Prevent dangling pointers
}

void LinkedList::insertFront(int val)
{
	Node* new_node;
	new_node = new Node(val);

	if (head == nullptr) // Linked list is empty
	{
		head = new_node;
	}
	else
	{
		new_node->next = head;
		head = new_node;
	}
}

void LinkedList::insertBack(int val)
{
	Node* new_node;
	Node* current;

	new_node = new Node(val);
	current = head;

	if (head == nullptr)
	{
		head = new_node;
	}
	else
	{
		while (current->next) // Exit once last element reached
		{
			current = current->next;
		}
		current->next = new_node;
	}
}

void LinkedList::removeFront()
{	
	if (head == nullptr) // List is already empty
	{
		return;
	}
	else if (head->next == nullptr) // Only one element in the list
	{
		delete head;
		head = nullptr; // To remove any dangling pointers
		return;
	}
	else // More than one element in the list
	{
		Node* current; // Temporary varaiable that stores the node to be removed
		current = head;
		head = head->next; // Shifts the current head to the new head
		delete current;
	}
}

void LinkedList::removeBack()
{
	Node* prev; // To update the "next" attribute of the node to nullptr 
	Node* current;

	if (head == nullptr) // List is already empty
	{
		return;
	}
	else if (head->next == nullptr) // Only one element in the list
	{
		delete head;
		head = nullptr; // To remove any dangling pointers
		return;
	}
	else
	{
		prev = head;
		current = head;

		while (current->next)
		{
			prev = current;
			current = current->next;
		}
		prev->next = nullptr; // Update the node before the last node
		delete current;
	}
}

bool LinkedList::isEmpty() const
{
	return head == nullptr;
}

int LinkedList::length() const
{
	Node* current;
	int total;

	current = head;
	total = 0;
	
	while (current)
	{
		current = current->next;
		total++;
	}
	return total;
}

void LinkedList::printList() const
{
	Node* current;
	current = head;

	while (current) // Exit once all elements printed
	{
		cout << current->data;
		current = current->next;
		if (current != nullptr)
		{
			cout << " -> "; // Elements are printed separated by " -> " until the end
		}
	}
	cout << endl;
}
