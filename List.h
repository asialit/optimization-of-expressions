#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <iostream>
#include <stdio.h>


struct LNode {
	char data;
	struct LNode* next;
};

class List {
public:
	List();

	~List();

	LNode* Top();

	bool isEmpty();

	void Push(char data);

	void pushList(LNode* node);

	// return -1 if failed to pop else return popped number
	char Pop();

	void pushNumber(int number);

private:
	LNode * list;
};

void Print(LNode* element);

char lastElem(LNode* node);

int getNumber(LNode* node, int counter);

LNode* Copy(LNode* list);

void reverseList(LNode** head);

bool checkIfLetter(LNode* node);

bool checkIfBrackets(LNode* node);

LNode* connect(LNode* a, LNode* b);

#endif
