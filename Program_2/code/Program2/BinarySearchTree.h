#pragma once
class BinarySearchTree
{
private:
	struct node {
		int value;
		node *left;
		node *right;
	};
public:
	BinarySearchTree();
	~BinarySearchTree();
};

