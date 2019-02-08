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
			delete(temp);
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

	string top() {
		if(isEmpty()) {
			return "";
		}
		else {
			return head->value;
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
			node* temp = topNode;
			topNode = topNode->next;
			delete(temp);
		}
		return value;
	}

	T top() {
		return topNode->value;
	}
};

void log(const std::string &input){
	ofstream filestream(FILENAME, std::ios_base::app|std::ios_base::out);
	filestream.flush();
	cout.flush();
	std::cout << input << endl;
	filestream << input << endl;
	filestream.close();

}

bool isOperator(char input){
	if (input == '+' || input == '-' || input == '/' || input == '*'){
		return true;
	}
	else{
		return false;
	}
}

bool isOperand(char input){
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

treeNode* convertPostfixToTree(string postfix) {
	tStack<treeNode*> treeStack;
	treeNode* root = new treeNode();
	for (int i = 0; i < postfix.size(); i++) {
		treeNode* node = new treeNode();
		node->value = postfix[i];
		if (isOperand(postfix[i])) {
			treeStack.push(node);
		}
		if (isOperator(postfix[i])) {
			treeNode* temp = treeStack.pop();
			node->right = temp;
			temp = treeStack.pop();
			node->left = temp;
			treeStack.push(node);
		}
	}
	root = treeStack.pop();
	return root;
}

string infixToPostfix(string infix){
	std::string postfix = "";
	tStack<char> stack;
	int parCount = 0;
	int prevIndex = 0;
	bool errors = false;

	for (int i = 0; i <= infix.size(); i++){
		if(infix[i] == ' '){
			i += 1;
			if (i > infix.length() - 1 ){
				if (isOperator(infix[prevIndex])) {
					errors = true;
					log("[ERROR] Missing second operand at indexes: " + to_string(prevIndex) + ',' + to_string(i));
				}
				else if (postfix.size() == 0){
					errors = true;
					log("[ERROR] Empty line!");
				}
				else {
					// all done
					break;
				}
			}
			else if (isOperand(infix[prevIndex]) && isOperand(infix[i])){
				errors = true;
				log("[ERROR] Two operands cannot be next to each other! At indexes: " + to_string(prevIndex) + ',' + to_string(i));
			}
			else if (isOperator(infix[prevIndex]) && infix[i] == '('){
				errors = true;
				log("[ERROR] Missing operand! At indexes: " + to_string(prevIndex) + ',' + to_string(i));
			}
			else if (infix[prevIndex] == ')' && infix[i] == '('){
				errors = true;
				log("[ERROR] Missing operator! At indexes: " + to_string(prevIndex) + ',' + to_string(i));
			}
			else if (infix[i] == ' '){
				errors = true;
				log("[ERROR] Invalid spacing! At indexes: " + to_string(prevIndex) + ',' + to_string(i));
			}
			else if (isOperand(infix[i])){
				postfix += infix[i];
			}
			else if (isOperator(infix[i])){
				while(stack.isEmpty() == false && stack.top() != '(' && getOperatorWeight(stack.top()) >= getOperatorWeight(infix[i])){
					postfix += stack.pop();
				}
				stack.push(infix[i]);
			}
			else if(infix[i] == '('){
				stack.push(infix[i]);
				parCount += 1;
			}
			else if (infix[i] == ')'){
				while(stack.isEmpty() == false && stack.top() != '('){
					postfix += stack.pop();
				}
				if (stack.isEmpty() == false){
					stack.pop();
				}
				parCount -= 1;
			}
		}
		else if (infix[i] != ' '){
			errors = true;
			log("[ERROR] Invalid spacing! At indexes: " + to_string(prevIndex) + ',' + to_string(i));
		}
		prevIndex = i;
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

string getPostfixOperations(string postfix) {
	string operations;
	string operation1;
	string operation2;
	tStack<string> stack;
	for (int i = 0; i < postfix.size(); i++) {
		if (isOperand(postfix[i])) {
			stack.push(string(1, postfix[i]));
		}
		else if (isOperator(postfix[i])) {
			operation1 = stack.pop();
			operation2 = stack.pop();
			string temp = operation2 + operation1 + postfix[i];
			stack.push(temp);
			operations += temp + "\n";
		}
	}
	return operations;
}

string visualizeTree(treeNode* root, int spacing) {
	string temp;
	if (root != NULL) {
		spacing += 5;
		temp += visualizeTree(root->right, spacing);
		temp += "\n";
		for (int i = 0; i < spacing; i++) {
			temp += " ";
		}
		temp += string(1,root->value);
		temp += visualizeTree(root->left, spacing);

	}
	return temp;
}

string getPostfixFromTree(treeNode* root) {
	string postfix;
	if (root == NULL) {
		return "";
	}
	else {
		if (root->left != NULL) {
			postfix += getPostfixFromTree(root->left);
		}
		if (root->right != NULL) {
			postfix += getPostfixFromTree(root->right);
		}
		postfix += string(1,root->value);
	}
	return postfix;
}
string getPrefixFromTree(treeNode* root) {
	string prefix;
	if (root == NULL) {
		return "";
	}
	else {
		prefix += string(1, root->value);
		if (root->left != NULL) {
			prefix += getPrefixFromTree(root->left);
		}
		if (root->right != NULL) {
			prefix += getPrefixFromTree(root->right);
		}
	}
	return prefix;
}
string getInfixFromTree(treeNode* root) {
	string infix;
	if (root == NULL) {
		return "";
	}
	else {
		if (root->left != NULL) {
			infix += getInfixFromTree(root->left);
		}
		infix += root->value;
		if (root->right != NULL) {
			infix += getInfixFromTree(root->right);
		}
	}
	return infix;
}

int getVariableValue(char input) {
	if (input >= 'A' && input <= 'Z') {
		return input - 64;
	}
	else {
		log("[ERROR][getVariableValue] Invalid Character, defaulting to -1: " + string(1, input));
		return -1;
	}
}

void solutionFromPrefix(string prefix) {
	tStack<string> opStack;
	tStack<int> intStack;
	int curVal = 0;
	for (int i = prefix.size() - 1; i >= 0; i--) {

		if (isOperand(prefix[i])) {
			curVal = getVariableValue(prefix[i]);
			opStack.push(string(1,prefix[i]));
			intStack.push(getVariableValue(prefix[i]));
		}
		else {
			if (opStack.isEmpty() == false) {
				string temp = string(1,prefix[i]);
				int tmpInt;
				string str1, str2;
				str1 = opStack.pop();
				temp += str1;
				str2 = opStack.pop();
				temp += str2;
				opStack.push(temp);

				if (prefix[i] == '+') {
					int int1 = intStack.pop();
					int int2 = intStack.pop();
					int tmp = int1 + int2;
					intStack.push(tmp);
				}
				else if (prefix[i] == '-') {
					int int1 = intStack.pop();
					int int2 = intStack.pop();
					int tmp = int1 - int2;
					intStack.push(tmp);
				}
				else if (prefix[i] == '*') {
					int int1 = intStack.pop();
					int int2 = intStack.pop();
					int tmp = int1 * int2;
					intStack.push(tmp);
				}
				else if (prefix[i] == '/') {
					int int1 = intStack.pop();
					int int2 = intStack.pop();
					if (int2 != 0) {
						int tmp = int1 / int2;
						intStack.push(tmp);
					}
					else {
						log("[ERROR] Cannot divide by zero!");
						return;
					}
				}
				curVal = intStack.top();
				log(temp + "   =   " + to_string(intStack.top()));
			}
		}
	}
	log("Final Solution: " + to_string(curVal));
}

// main method for testing stuff
/*int main(int argc, const char* argv[]) {
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
		log("pop: " + string(1,test.pop()));
		//test.pop();
	}
	system("PAUSE");
	return 1;
}*/

int main() {
	log("\nWelcome to the best program ever!");
	log("Please enter an input file name: ");
	string inputFileName;
	getline(cin, inputFileName);
	ifstream inFile(inputFileName);
	if (!inFile) {
		log(inputFileName + " Does not exist!");
		system("PAUSE");
		return 1;
	}
	else if (inFile.peek() == ifstream::traits_type::eof()) {
		log(inputFileName + " File is empty!");
		system("PAUSE");
		return 1;
	}
	log(inputFileName + " File was opened successfully!");

	string line;
	while (getline(inFile, line)) {
		log("===============================================");
		log("Input: " + line);
		string postfix;
		postfix = infixToPostfix(line);
		if (postfix != "") {
			log("\nPostfix: " + postfix);
			string operations = getPostfixOperations(postfix);
			log("\nOperations: " + operations);
			treeNode* root = convertPostfixToTree(postfix);
			string visTree = visualizeTree(root, 1);
			log("\nTree: \n" + visTree);
			string postfixTree = getPostfixFromTree(root);
			string infixTree = getInfixFromTree(root);
			string prefixTree = getPrefixFromTree(root);
			log("\nPostfix from tree: " + postfixTree);
			log("Prefix from tree: " + prefixTree);
			log("Infix from tree: " + infixTree);
			solutionFromPrefix(prefixTree);
		}
	}

	log("Thank you for using the program! Have a great day!");

	system("PAUSE");
	return 1;
}
