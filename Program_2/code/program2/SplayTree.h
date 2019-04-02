//Program Name: Trees and more Trees
//Programmer Name: Jason Hogan
//Description: Reads integers from an inital insert file to bst, avl, and splay tree. then performs operations based on the requested action in the operations file
//Date Created: 2/23/18
#pragma once
#include <string>
using namespace std;
class SplayTree
{
private:
	struct node {
		int value;
		node* left = NULL;
		node* right = NULL;
		node* twin = NULL;
		node* parent = NULL;
	};

	node* root = NULL;

	void rotateRight(node* input);
	void rotateLeft(node* input);
	/*void zig(node* input);
	void zag(node* input);
	void zigzag(node* input);
	void zigzig(node* input);
	void zagzig(node* input);
	void zagzag(node* input);*/
	string printRecursive(node* input, int spCount);
	int getHeight(node* input);

public:
	SplayTree();
	~SplayTree();
	void splay(node* T, int* opCount, int* i, int* a, int* ia, int* ai, int* ii, int* aa);
	void insert(int x, int* opCount, int* i, int* a, int* ia, int* ai, int* ii, int* aa);
	void search(int x, int* opCount, int* i, int* a, int* ia, int* ai, int* ii, int* aa);
	void deleteNode(int x, int* opCount, int* i, int* a, int* ia, int* ai, int* ii, int* aa);
	string printTree();
	int getMaxHeight();
};
