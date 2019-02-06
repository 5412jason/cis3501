#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <stdio.h>

#define FILENAME "output.dat"

using namespace std;

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

	void pop() {
		if (!isEmpty()) {
			//node* temp = topNode;
			topNode = topNode->next;
			//delete(temp);
		}
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

// main method for testing stuff
int main(int argc, const char* argv[]) {
	log("Welcome to the program!");
	//logger->log("Logging test ");
	tStack<char> test;
	test.push('a');
	log("Pushed: a");
	test.push('b');
	log("Pushed: b");
	test.push('c');
	log("Pushed: c");
	while (!test.isEmpty()) {
		log("Popped: " + std::string(1,test.top()));
		test.pop();
	}
	return 1;
}
