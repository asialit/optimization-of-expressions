#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "List.h"


struct Node {
	List* list;
	struct Node* next;
};

class Stack {
public:
	Stack();

	~Stack();

	bool isEmpty();

	Node* Top();

	//add empty list
	void PushEmpty();

	void pushSign(char data);

	void Push(List* list);

	void pushStack(Node* node);

	void pushCopy();

	List* Pop();

	void pushNumber(int number);

private:
	Node * stack;
};

int count(Node* stack);

void reverseStack(Node** head_ref);

void printStack(Node* stack);

Node* getList(Node* element, int number, int counter);

int CountArray(char array[], int n, int count);

Node* copyStack(Node* list);

#endif