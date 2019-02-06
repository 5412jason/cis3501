#pragma once

template <class T>
class tStack
{
private:
	class node {
	public:
		T value;
		node* next;
	};
	node* topNode;

public:
	tStack();
	~tStack();
	void push(T input);
	bool isEmpty();
	void pop();
	T top();
};
