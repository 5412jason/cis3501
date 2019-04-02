//Program Name: Trees and more Trees
//Programmer Name: Jason Hogan
//Description: Reads integers from an inital insert file to bst, avl, and splay tree. then performs operations based on the requested action in the operations file
//Date Created: 2/23/18
#pragma once
#include <string>
using namespace std;
class BinarySearchTree
{
private:
	struct node {
		int value;
		node *right; 
		node *left;
		node *twin;
	};
	node* root = NULL;

	node* getMinNode(node* input);
	node* deleteRecursive(int x, node* input, int *count);
	string printRecursive(node* input, int spCount);

	int getHeight(node* input);

public:
	BinarySearchTree();
	~BinarySearchTree();
	int insert(int x);
	int search(int x);
	int deleteValue(int x);
	string printTree();
	int maxHeight();
};

