#include<cstdlib>
#include "Stack.h"
#include "List.h"

Stack::Stack() {
	stack = NULL;
}

Stack::~Stack() {
	while (stack != NULL) {
		Pop();
	}
}

bool Stack::isEmpty() {
	return (stack == NULL);
}

Node* Stack::Top() {
	return stack;
}

// add empty list
void Stack::PushEmpty() {
	Node* node = (Node*)malloc(sizeof(Node));
	node->list = nullptr;
	node->next = stack;
	stack = node;
}

void Stack::pushSign(char sign) {
		List* list = new List;
		list->Push(sign);
		Push(list);
}

void Stack::Push(List* Pushinglist) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->list = Pushinglist;
	node->next = stack;
	stack = node;
}

void Stack::pushStack(Node* node) {
	stack = node;
}

List* Stack::Pop() {

	List* poppedList = NULL;

	if (!isEmpty()) {
		Node* node = stack;
		// save popped list for return
		poppedList = stack->list;

		// switch first element to next
		stack = stack->next;
		delete node;
	}

	return poppedList;
}

void Stack::pushCopy() {

	LNode* copy = Copy(stack->list->Top());

	List* element = (List*)malloc(sizeof(List));

	element->pushList(copy);

	Push(element);
}

void Stack::pushNumber(int number) {
	List* list = new List;

	if (number == 0) {
		list->Push('0');
		Push(list);
	}
	else {
		list->pushNumber(number);

		LNode* head = list->Top();

		reverseList(&head);

		List* tmp = new List;
		tmp->pushList(head);
		Push(tmp);
	}
}

void reverseStack(Node** head)
{
	struct Node* first;
	struct Node* rest;

	// empty list
	if (*head == NULL)
		return;

	first = *head;
	rest = first->next;

	// List has only one node
	if (rest == NULL)
		return;

	// reverse the rest list and put the first element at the end
	reverseStack(&rest);
	first->next->next = first;

	first->next = NULL;

	// fix the head pointer
	*head = rest;
}

int count(Node* stack) {
	// Base case
	if (stack == NULL)
		return 0;

	// count is 1 + count of remaining list
	return 1 + count(stack->next);
}

void printStack(Node* element) { //do poprawy 

	while (element != NULL) {
		if (element->list != NULL) {
			Print(element->list->Top());
		}
		element = element->next;
	}

	std::cout << "\n";
}

Node* getList(Node* element, int number, int counter) {

	if (counter == number) {
		return element;
	}
	else return getList(element->next, number, counter + 1);

}

int CountArray(char array[], int n, int count) {

	while (array[n] != '\0') {
		count++;
		n++;
	}

	return count;
}

Node* copyStack(Node* stack) {
	if (stack == NULL) return NULL;
	List* list = new List;
	list->pushList(Copy(stack->list->Top()));

	Node* copy = new Node;
	copy->list = list;
	copy->next = copyStack(stack->next);
	return copy;
}