#pragma once
#include <string>
using namespace std;
class AvlTree
{
private:
	struct node {
		int value;
		node *right = NULL;
		node *left = NULL;
		node *twin = NULL;
		int height = 1;
	};
	node* root = NULL;

	node* llRotation(node* input);
	node* rrRotation(node* input);
	node* lrRotation(node* input);
	node* rlRotation(node* input);
	node* insertRecursive(int x, node* input, int *opCount, int * ll, int * rr, int *lr, int *rl);
	node* deleteRecursive(int x, node* input, int * opCount, bool * found, int * ll, int * rr, int *lr, int *rl);
	node* getMinNode(node* input);
	int getHeightDif(node* input);
	int getHeight(node* input);
	string printRecursive(node* input, int spCount);
public:
	AvlTree();
	~AvlTree();
	string printTree();
	int insert(int x);
	int search(int x);
	int deleteValue(int x);
};

