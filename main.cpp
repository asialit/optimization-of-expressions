#include <string.h>
#include "Stack.h"

int getPriority(char C)
{
	if (C == '-' || C == '+')
		return 1;
	else if (C == '*' || C == '/')
		return 2;

	return 0;
}

//send operators with equal or higher priority to the output
void pushOperator(Stack &stack, Stack &output, char* currentLineInput) {
	Node * element = stack.Top();
	if (!stack.isEmpty()) {
		while (getPriority(char(stack.Top()->list->Top()->data)) >= getPriority(char(currentLineInput[0]))) {
			List* list = new List;
			list->Push(stack.Top()->list->Pop());
			output.Push(list);
			stack.Pop();
		}
	}
}

int main() {
	Stack stack;
	Stack output;

	char* line = nullptr;
	char* currentLineInput;

	size_t lineSize = 80000;

	bool quit = false;

	while (!quit) {
		line = (char*)malloc(lineSize * sizeof(char));

		std::cin.getline(line, lineSize);

		currentLineInput = strtok(line, " ");

		if (currentLineInput[0] == 'q') {
			quit = true;
		}

		if (quit) {
			break;
		}

		// check if continue to split
		while (currentLineInput != NULL) {

			// change to Reverse Polish notation
			switch (currentLineInput[0]) {
			case '(':
				stack.pushSign('(');
				break;
			case ')':
			{
				Node * element = stack.Top();
				//send operators to the output until you meet the character '('
				while (element->list->Top()->data != '(' && !stack.isEmpty()) {
					char sign = stack.Top()->list->Pop();
					output.pushSign(sign);
					stack.Pop();
					element = stack.Top();
				}

				stack.Pop();
			}
			break;
			case '+':
				pushOperator(stack, output, currentLineInput);
				stack.pushSign('+');
				break;
			case '-':
				pushOperator(stack, output, currentLineInput);
				stack.pushSign('-');
				break;
			case '*':
				pushOperator(stack, output, currentLineInput);
				stack.pushSign('*');
				break;
			case '/':
				pushOperator(stack, output, currentLineInput);
				stack.pushSign('/');
				break;
			case ' ':
				//do nothing
				break;
			default:
			{
				int n = CountArray(currentLineInput, 0, 0);
				List* list = new List;
				for (int i = n - 1; i >= 0; i--) {
					list->Push(currentLineInput[i]);
				}
				output.Push(list);
			}
			break;
			}

			currentLineInput = strtok(NULL, " ");

			//send operators from the stack to the output
			if (currentLineInput == NULL) { 
				if (!stack.isEmpty()) {
					Node * element = stack.Top();
					while (stack.isEmpty() != true) {
						char sign = stack.Top()->list->Pop();
						stack.Pop();
						if (sign != '(') {
							output.pushSign(sign);
							element = stack.Top();
						}
					}
				}

			}

		}

		Node* tmp = copyStack(output.Top());
		reverseStack(&tmp);
		while (!output.isEmpty())
		{
			output.Pop();
		}

		output.pushStack(copyStack(tmp));

		delete tmp;

		while (!output.isEmpty()) {
			if (output.Top()->list->Top()->data == '+' || output.Top()->list->Top()->data == '-' ||
				output.Top()->list->Top()->data == '*' || output.Top()->list->Top()->data == '/') {


				List* node2 = new List;
				List* node1 = new List;
				
				if (stack.Top() != nullptr) {
					node2 = stack.Pop();
				}			
				if (stack.Top() != nullptr) {
					node1 = stack.Pop();
				}

				//both do not contain letters
				if (checkIfLetter(node2->Top()) == false && checkIfLetter(node1->Top()) == false) {

					LNode* head2 = node2->Top();
					LNode* head1 = node1->Top();

					reverseList(&head2);
					reverseList(&head1);

					int b = getNumber(head2, 1);
					int a = getNumber(head1, 1);

					List* list = new List;
					stack.Push(list);
					
					switch (output.Top()->list->Top()->data) {
						case '+':
							if (a == -b) {
								stack.Top()->list->Push('0');
							}
							else {
								stack.Top()->list->pushNumber(a + b);
							}
							break;
						case '-':
							if (a == b) {
								stack.Top()->list->Push('0');
							}
							else {
								stack.Top()->list->pushNumber(a - b);
							}
							break;
						case '*':
							if (a == 0 || b == 0) {
								stack.Top()->list->Push('0');
							}
							else { 
								stack.Top()->list->pushNumber(a * b); 
							}
							break;
						case '/':
							if ((a < b && a > 0) || (a < 0 && -a < b)) {
								stack.Top()->list->Push('0');
							}
							else {
								stack.Top()->list->pushNumber(a / b);
							}
							break;
						default:
							break;
					}
					

					output.Pop();

				}
				//both contain letters
				else if (checkIfLetter(node2->Top()) == true && checkIfLetter(node1->Top()) == true) {

					List* list = new List;

					LNode* element = new LNode;
					element->data = output.Top()->list->Top()->data;
					element->next = node2->Top();

					List* list2 = new List;
					list2->Push(')');
					list->pushList(connect(connect(node1->Top(), element), list2->Top()));
					list->Push('(');

					stack.Push(list);

					output.Pop();

				}
				//one contains letter
				else {
					//when the operator is + or * and one of the arguments is a number, it should be on the left
					if (output.Top()->list->Top()->data == '+' || output.Top()->list->Top()->data == '*') {
						List* list = new List;

						if (checkIfLetter(node2->Top()) == true && checkIfLetter(node1->Top()) == false) {

							LNode* element = new LNode;
							element->data = output.Top()->list->Top()->data;
							element->next = node2->Top();

							List* list2 = new List;
							list2->Push(')');
							list->pushList(connect(connect(node1->Top(), element), list2->Top()));
							list->Push('(');

							stack.Push(list);
						}
						else if (checkIfLetter(node2->Top()) == false && checkIfLetter(node1->Top()) == true) {

							LNode* element = new LNode;
							element->data = output.Top()->list->Top()->data;
							element->next = node1->Top();


							List* list2 = new List;
							list2->Push(')');
							list->pushList(connect(connect(node2->Top(), element), list2->Top()));
							list->Push('(');

							stack.Push(list);
						}
					}
					else {
						List* list = new List;

						LNode* element = new LNode;
						element->data = output.Top()->list->Top()->data;
						element->next = node2->Top();

						List* list2 = new List;
						list2->Push(')');
						list->pushList(connect(connect(node1->Top(), element), list2->Top()));
						list->Push('(');

						stack.Push(list);
					}
					output.Pop();

				}

			}
			else {
				if (checkIfLetter(output.Top()->list->Top()) == true) {
					stack.Push(output.Pop());
				}
				else {
					LNode* tmp3 = output.Top()->list->Top();
					reverseList(&tmp3);

					List* list = new List;

					while (tmp3 != nullptr) {
						list->Push(tmp3->data);
						tmp3 = tmp3->next;
					}

					stack.Push(list);

					output.Pop();
				}
			}
		}

		if (checkIfBrackets(stack.Top()->list->Top()) == false){
			std::cout << "( ";
			Print(stack.Top()->list->Top());
			std::cout << " )" << std::endl;
		}
		else {
			Print(stack.Top()->list->Top());
			std::cout << std::endl;
		}

		free(line);
		while (!stack.isEmpty())
		{
			stack.Pop();
		}
	}

	return 0;
}