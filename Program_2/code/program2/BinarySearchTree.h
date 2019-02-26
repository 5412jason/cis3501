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
public:
	BinarySearchTree();
	~BinarySearchTree();
	int insert(int x);
	int search(int x);
	int deleteValue(int x);
	string printTree();
};

