#pragma once
#include <string>
using namespace std;
class AvlTree
{
private:
	struct node {
		int value;
		node* right, *left;
		int height;
	};
	node* root = NULL;

	node* rightRotation(node* input);
	node* leftRotation(node* input);
	node* doubleRightRotation(node* input);
	node* doubleLeftRotation(node* input);
	node* insertRecursive(int x, node* input, int *opCount);
	node* deleteRecursive(int x, node* input, int *opCount);
	node* getMinNode(node* input);
	node* printRecursive(node* input, int spCount);
public:
	AvlTree();
	~AvlTree();
	string printTree();
	int insert(int x);
	int search(int x);
	int deleteValue(int x);
};

