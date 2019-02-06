#include "tStack.h"
#include <iostream>
using namespace std;

template<class T>
tStack<T>::tStack()
{
}

template<class T>
tStack<T>::~tStack()
{
}

template<class T>
bool tStack<T>::isEmpty() {
	if (top() == NULL) {
		return true;
	}
	else {
		return false;
	}
}

template<class T>
void tStack<T>::push(T input) {
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

template<class T>
void tStack<T>::pop() {
	if (isEmpty() == false) {
		node* temp = topNode;
		topNode = topNode->next;
		delete(temp);
	}
}

template<class T>
T tStack<T>::top() {
	return topNode->value;
}