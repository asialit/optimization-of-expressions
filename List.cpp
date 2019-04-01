#include "List.h"

List::List() {
	list = NULL;
}

List::~List() {
while (list != NULL) {
Pop();
}
}

LNode* List::Top() {
	return list;
}

bool List::isEmpty() {
	return (list == NULL);
}


void List::Push(char data) {
	LNode* node = new LNode;
	node->data = data;
	node->next = list;
	list = node;
}

void List::pushList(LNode* node) {
	list = node;
}

char List::Pop() {
	char poppedNumber = -1;

	// guard from popping empty stack
	if (!isEmpty()) {
		LNode* node = list;
		// save popped data for return
		poppedNumber = list->data;

		// switch first element to next
		list = list->next;
		delete node;
	}

	return poppedNumber;
}

void Print(LNode* element) {
	bool isFirstLoop = true;
	bool isPreviousNumber = false;
	bool isPreviousMinus = false;
	bool isPreviousBracket = false;

	while (element != nullptr) {
		// first loop - no space before
		// number after number - no space before (isPreviousNumber)
		// minus without space only after (

		if (isFirstLoop || ((isPreviousNumber || isPreviousMinus) && (element->data >= '0' && element->data <= '9'))) {
			std::cout << element->data;
		}
		else {
			std::cout << " " << element->data;
		}

		if ((isPreviousBracket || isFirstLoop) && element->data == '-') {
			isPreviousMinus = true;
			isPreviousNumber = false;
			isPreviousBracket = false;
		}
		else if (element->data >= '0' && element->data <= '9') {
			isPreviousMinus = false;
			isPreviousNumber = true;
			isPreviousBracket = false;
		}
		else if (element->data == '(' || element->data == '/' || element->data == '*' || element->data == '+' || element->data == '-') {
			isPreviousNumber = false;
			isPreviousBracket = true;
			isPreviousMinus = false;
		}
		else {
			isPreviousMinus = false;
			isPreviousBracket = false;
			isPreviousNumber = false;
		}
		if (isFirstLoop) {
			isFirstLoop = false;
		}

		element = element->next;
	}
}

LNode* Copy(LNode* list) {
	if (list == NULL) return NULL;

	LNode* copy = new LNode;
	copy->data = list->data;
	copy->next = Copy(list->next);
	return copy;
}

char lastElem(LNode* node) {
	// stop - end of list
	if (node == nullptr) return '\0';

	// recursive call
	char result = lastElem(node->next);
	// check if list ended in recursion
	if (result == '\0')
	{
		// return last list element
		return node->data;
	}

	return result;
}

//change list to number
int getNumber(LNode* node, int counter) {
	// stop 1 - end of list
	if (node == nullptr)
	{
		return 0;
	}

	// stop 2, - last element
	if (node->data == '-')
	{
		return -1;
	}

	// recursive call with greater counter
	int result = getNumber(node->next, counter * 10);

	// recursive called list element -
	if (result == -1)
	{
		if (node->data == '0' && counter == 1)
		{
			return 0;
		}
		else if (node->data == '0')
		{
			return -1;
		}
		else {
			return (node->data - '0')*counter*-1;
		}
	}

	// sum up if number was <0
	if (result < 0)
	{
		return -(-result + ((node->data - '0') * counter));
	}

	// normal sum
	return result + ((node->data - '0')*counter);
}

void reverseList(LNode** head) {
	struct LNode* first;
	struct LNode* rest;

	/* empty list */
	if (*head == NULL)
		return;

	first = *head;
	rest = first->next;

	// List has only one node
	if (rest == NULL)
		return;

	// reverse the rest list and put the first element at the end
	reverseList(&rest);
	first->next->next = first;

	first->next = NULL;

	//fix the head pointer
	*head = rest;
}

void List::pushNumber(int number) {
		
	if (number < 0) {
		number *= -1;
		while (number != 0) {
			int tmp = number % 10;
			Push(tmp + '0');
			number = number / 10;
		}
		Push('-');
	}

	while (number != 0) {
		int tmp = number % 10;
		Push(tmp + '0');
		number = number / 10;
	}
}

bool checkIfLetter(LNode* node) {

	while (node != nullptr) {
		if (node->data >= 'a' && node->data <= 'z')
			return true;
		else {
			node = node->next;
		}
	}
	return false;
}

bool checkIfBrackets(LNode* node) {

	while (node != nullptr) {
		if (node->data == '(' || node->data == ')')
			return true;
		else {
			node = node->next;
		}
	}
	return false;
}

LNode* connect(LNode* a, LNode* b)
{
	if (a != NULL)
	{
		if (a->next == NULL)
			a->next = b;
		else
			connect(a->next, b);
	}

	return a;
}

