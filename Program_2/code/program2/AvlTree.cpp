//Program Name: Trees and more Trees
//Programmer Name: Jason Hogan
//Description: Reads integers from an inital insert file to bst, avl, and splay tree. then performs operations based on the requested action in the operations file
//Date Created: 2/23/18
#include "pch.h"
#include "AvlTree.h"
#include <algorithm>
#include <cstdlib>
using namespace std;

AvlTree::AvlTree()
{
}

AvlTree::~AvlTree()
{
}

//Description: Public function that returns a string with a horizontally structured tree
string AvlTree::printTree()
{
	string structure = printRecursive(root, 0);

	return structure;
}

//Description: Public function that inserts an integer value into the AVL tree
int AvlTree::insert(int x, int * ll, int * rr, int *lr, int *rl)
{
	int opCount = 0;
	root = insertRecursive(x, root, &opCount, ll, rr, lr, rl);
	return opCount;
}
//Description: public Function that searches through the AVL tree for the requested value.
// If the value can't be found then a negative operation cound will be returned
int AvlTree::search(int x)
{
	int opCount = 0;
	bool found = false;
	node* current = root;

	while (current != NULL) {
		if (x == current->value) {
			opCount++;
			found = true;
			break;
		}
		else if (x < current->value) {
			current = current->left;
			opCount++;
		}
		else if (x > current->value) {
			current = current->right;
			opCount++;
		}
	}
	if (found) {
		return opCount;
	}
	else {
		//not found so return a -value
		return opCount * -1;
	}
	return 0;
}

// Description: Public function that removes a value from the AVL tree.
int AvlTree::deleteValue(int x, int * ll, int * rr, int *lr, int *rl)
{

	bool found = false;
	int opCount = 0;
	root = deleteRecursive(x, root, &opCount, &found, ll, rr, lr, rl);
	if(found == true){
		return opCount;
	}
	else {
		return opCount * -1;
	}
}

//Description: Public function to get the maxHeight of the root node
int AvlTree::maxHeight()
{
	return getMaxHeight(root);
}

//Description: Performs a left-left rotation on the inputted node
AvlTree::node * AvlTree::llRotation(node * input)
{
	node* temp1 = input->left;
	node* temp2 = temp1->right;
	
	temp1->right = input;
	input->left = temp2;

	input->height = max(getHeight(input->left), getHeight(input->right)) + 1;
	temp1->height = max(getHeight(input->left), getHeight(input->right)) + 1;

	return temp1;
}

//Description: Performs a right-right rotation on the inputted node
AvlTree::node * AvlTree::rrRotation(node * input)
{
	node* temp1 = input->right;
	node* temp2 = temp1->left;

	temp1->left = input;
	input->right = temp2;

	input->height = max(getHeight(input->left), getHeight(input->right)) + 1;
	temp1->height = max(getHeight(input->left), getHeight(input->right)) + 1;

	return temp1;
}

//Description: Performs a left-right rotation on the inputted node
AvlTree::node * AvlTree::lrRotation(node * input)
{
	input->left = rrRotation(input->left);
	input = llRotation(input);

	return input;
}

//Description: Perfoms a right-left rotation on the inputted node
AvlTree::node * AvlTree::rlRotation(node * input)
{
	input->right = llRotation(input->right);
	input = rrRotation(input);

	return input;
}

//Description: Recursively traverses throught the AVL tree to insert the inputted value in the correct position.
// After value is inserted, the proper rotations are done to ensure the tree is balanced properly
AvlTree::node * AvlTree::insertRecursive(int x, node * input, int * opCount, int * ll, int * rr, int *lr, int *rl)
{ 
	//node* y = root;
	if (input == NULL) {
		node* newNode = new node();
		newNode->value = x;
		return newNode;
	}
	else if (x < input->value) {
		*opCount+=1;
		input->left = insertRecursive(x, input->left, opCount, ll, rr, lr, rl);
	}
	else if (x > input->value) {
		*opCount+= 1;
		input->right = insertRecursive(x, input->right, opCount, ll, rr, lr, rl);
	}
	else if (x == input->value) {
		node* current = input;
		node* newNode = new node();
		newNode->value = x;
		// handle the twin node scenario
		while (current->twin != NULL) {
			current = current->twin;
			*opCount+=1;
		}
		current->twin = newNode;
		return input;
	}

	input->height = max(getHeight(input->left), getHeight(input->right)) + 1;
	int hDiff = getHeightDif(input);
	if (hDiff > 1 && x < input->left->value) {
		*ll += 1;
		return llRotation(input);
	}
	if (hDiff > 1 && x > input->left->value) {
		*lr += 1;
		return lrRotation(input);
	}
	if (hDiff < -1 && x > input->right->value) {
		*rr += 1;
		return rrRotation(input);
	}
	if (hDiff < -1 && x < input->right->value) {
		*rl += 1;
		return rlRotation(input);
	}
	return input;
}

//Description: Recursively traverses throught the tree to delete the requested value. If the value isn't found, then the opCount will be negative.
AvlTree::node * AvlTree::deleteRecursive(int x, node * input, int * opCount, bool * found, int * ll, int * rr, int *lr, int *rl)
{
	node* y = root;
	if (input == NULL) {
		return input;
	}
	else if (x < input->value) {
		*opCount += 1;
		input->left = deleteRecursive(x, input->left, opCount, found, ll, rr, lr, rl);
	}
	else if (x > input->value) {
		*opCount += 1;
		input->right = deleteRecursive(x, input->right, opCount, found, ll, rr, lr, rl);
	}
	else if (x == input->value) {
		*found = true;
		if (input->twin != NULL) {
			node* temp = input;
			while (temp->twin->twin != NULL) {
				temp = temp->twin;
				*opCount += 1;
			}
			free(temp->twin);
			temp->twin = NULL;
		}
		else if (input->left == NULL || input->right == NULL) {
			node* temp = input->left ? input->left : input->right;

			if (temp == NULL) {
				temp = input;
				input = NULL;
			}
			else {
				input->value = temp->value;
				input->height = temp->height;
				input->left = temp->left;
				input->right = temp->right;
				input->twin = temp->twin;
			}
			free(temp);
			temp = NULL;
		}
		else {
			node *temp = getMinNode(input->right);
			input->value = temp->value;
			input->right = deleteRecursive(temp->value, input->right, opCount, found, ll, rr, lr, rl);
		}
	}

	if (input == NULL) {
		return input;
	}

	input->height = max(getHeight(input->left), getHeight(input->right)) + 1;

	int hDiff = getHeightDif(input);
	if (hDiff > 1 && getHeightDif(input->left) >= 0) {
		*ll+=1;
		return llRotation(input);
	}
	if (hDiff > 1 && getHeightDif(input->left) < 0) {
		*lr+=1;
		return lrRotation(input);
	}
	if (hDiff < -1 && getHeightDif(input) <= 0) {
		*rr+=1;
		return rrRotation(input);
	}
	if (hDiff < -1 && getHeightDif(input) > 0) {
		*rl+=1;
		return rlRotation(input);
	}
	return input;
}

//Description: Finds the minimum valued node under the inputted node
AvlTree::node * AvlTree::getMinNode(node * input)
{
	node *current = input;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

//Description: Gets the difference in height of the right an left child nodes of the inputted node
int AvlTree::getHeightDif(node * input)
{
	if (input == NULL) {
		return 0;
	}
	int left = getHeight(input->left);
	int right = getHeight(input->right);

	return left-right;
}

//Description: Gets the current height of the inputted node
int AvlTree::getHeight(node * input)
{
	if (input == NULL) {
		return 0;
	}
	else {
		return input->height;
	}
}

//Description: Recursively builds a string that represents a horizantal structure of the tree
string AvlTree::printRecursive(node * input, int spCount)
{
	string temp;
	if (input != NULL) {
		spCount += 5;
		temp += printRecursive(input->right, spCount);
		temp += "\n";
		for (int i = 0; i < spCount; i++) {
			temp += " ";
		}
		temp += to_string(input->value);
		if (input->twin != NULL) {
			int tcount = 0;
			node* x = input;
			while (x->twin != NULL) {
				tcount += 1;
				x = x->twin;
			}
			temp += "(" + to_string(tcount);
			temp += ")";
		}
		temp += printRecursive(input->left, spCount);

	}
	return temp;
}

//Description: Gets the maximum height of the inputted node
int AvlTree::getMaxHeight(node * input)
{
	if (input == NULL)
		return 0;
	else
	{
		/* compute the depth of each subtree */
		int lDepth = getMaxHeight(input->left);
		int rDepth = getMaxHeight(input->right);

		/* use the larger one */
		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}

