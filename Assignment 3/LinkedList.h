#ifndef LinkedListFlag
#define LinkedListFlag

/*
	Problem 1

	This program is the header file that implements a linked list as a class.

	Author Evan Law August 4, 2023;
*/

typedef struct Node {
	int data;
	Node* next;
	Node(int val) : data(val), next(nullptr) {}
}Node;


class LinkedList {
private:
	Node* head;

public:
	LinkedList();
	~LinkedList();

	void insertFront(int val);
	void insertBack(int val);
	void removeFront();
	void removeBack();
	bool isEmpty() const;
	void printList() const;
	int length() const;

	// Added accessor function to get the head node, used
	// in the stack class method peek.
	Node* get_head() const
	{
		return head;
	}
};

#endif
