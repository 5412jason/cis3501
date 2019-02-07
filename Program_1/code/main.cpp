#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iterator>
#include <stdio.h>

#define FILENAME "output.dat"

using namespace std;

struct treeNode{
	treeNode* left = NULL;
	treeNode* right = NULL;

	char value;
};

class strQueue{
private:
	struct node{
		string value;
		node* next = NULL;
	};
	node* head = NULL;

public:
	void enqueue(string input){
		if (isEmpty()){
			node* newNode = new node;
			newNode->value = input;
			head = newNode;
		}
		else{
			node* newNode = new node;
			newNode->value = input;
			node* current = head;
			while(current->next != NULL){
				current = current->next;
			}
			current->next = newNode;
		}
	}
	string dequeue(){
		if (isEmpty()){
			cout << "[ERROR]] Cannot dequeue item, Queue is empty" << endl;
			return "";
		}
		else{
			node* temp = head;
			string value = head->value;
			head = head->next;
			//delete(temp);
			return value;
		}
	}

	bool isEmpty(){
		if(head == NULL){
			return true;
		}
		else{
			return false;
		}
	}
};

template <typename T>
class tStack
{
private:
	class node {
	public:
		T value;
		node* next = NULL;
	};
	node* topNode = NULL;

public:
	tStack()
	{
	}

	~tStack()
	{
	}

	bool isEmpty() {
		if (topNode == NULL) {
			return true;
		}
		else {
			return false;
		}
	}

	void push(T input) {
		if (isEmpty()) {
			node* newNode = new node();
			newNode->value = input;
			topNode = newNode;
		}
		else {
			node* newNode = new node();
			newNode->value = input;
			newNode->next = topNode;
			topNode = newNode;
		}
	}

	T pop() {
		T value = topNode->value;
		if (!isEmpty()) {
			//node* temp = topNode;
			topNode = topNode->next;
			//delete(temp);
		}
		return value;
	}

	T top() {
		return topNode->value;
	}
};

void log(const std::string &input){
	ofstream filestream(FILENAME, std::ios_base::app|std::ios_base::out);
	std::cout << input << endl;
	filestream << input << endl;
}

bool isOperand(char input){
	if (input == '+' || input == '-' || input == '/' || input == '*'){
		return true;
	}
	else{
		return false;
	}
}

bool isOperator(char input){
	if(input >= 'A' && input <= 'Z'){
		return true;
	}
	else{
		return false;
	}
}

int getOperatorWeight(char input){
	if (input == '+' || input == '-'){
		return 1;
	}
	else if (input == '*' || input == '/'){
		return 2;
	}
	else{
		log("[ERROR][getOperatorWeight] Cannot get weight, invalid operator: " + input);
		return -1;
	}
}

string infixToPostfix(std::string infix){
	std::string postfix = "";
	tStack<char> stack;
	int parCount = 0;
	int prevIndex = 0;
	bool errors = false;

	char characters[infix.size()];
	strcpy (characters, infix.c_str());

	for (int i = 0; i <= infix.size(); i++){
		if(characters[i] == ' '){
			i += 1;
			if (i > infix.length()){
				if(postfix.size() != 0){
					// string is done being parsed
					break;
				}
				else{
					errors = true;
					log("[ERROR] Empty line!");
				}
			}
			else if (isOperand(characters[prevIndex] && isOperand(characters[i]))){
				errors = true;
				log("[ERROR] Two operands cannot be next to each other! At indexes: " + characters[prevIndex] + ',' + characters[i]);
			}
			else if (isOperator(characters[prevIndex]) && characters[i] == '('){
				errors = true;
				log("[ERROR] Missing operand! At indexes: " + characters[prevIndex] + ',' + characters[i]);
			}
			else if (characters[prevIndex] == ')' && characters[i] == '('){
				errors = true;
				log("[ERROR] Missing operator! At indexes: " + characters[prevIndex] + ',' + characters[i]);
			}
			else if (characters[i] == ' '){
				errors = true;
				log("[ERROR] Invalid spacing! At indexes: " + characters[prevIndex] + ',' + characters[i]);
			}
			else if (isOperand(characters[i])){
				postfix += characters[i];
			}
			else if (isOperator(characters[i])){
				while(stack.isEmpty() == false && stack.top() != '(' && getOperatorWeight(stack.top() > getOperatorWeight(characters[i]))){
					postfix += stack.pop();
				}
				stack.push(characters[i]);
			}
			else if(characters[i] == '('){
				stack.push(characters[i]);
				parCount += 1;
			}
			else if (characters[i] == ')'){
				while(stack.isEmpty() == false && stack.top() != '('){
					postfix += stack.pop();
				}
				if (stack.isEmpty() == false){
					stack.pop();
				}
				parCount -= 1;
			}
		}
		else if (characters[i] != ' '){
			errors = true;
			log("[ERROR] Invalid spacing! At indexes: " + characters[prevIndex] + '+' + characters[i]);
		}
	}
	while (stack.isEmpty() == false){
		postfix +=stack.pop();
	}
	if(parCount != 0){
		errors = true;
		log("[ERROR] Mismatched Parentheses!");
	}
	if(errors) {
		return "";
	}
	else{
		return postfix;
	}
}

// main method for testing stuff
int main(int argc, const char* argv[]) {
	log("Welcome to the program!");
	//logger->log("Logging test ");
	tStack<char> test;
	test.push('a');
	log("push: a");
	test.push('b');
	log("push: b");
	test.push('c');
	log("push: c");
	while (!test.isEmpty()) {
		log("pop: " + test.top());
		test.pop();
	}
	return 1;
}
