//Program Name: Trees and more Trees
//Programmer Name: Jason Hogan
//Description: Reads integers from an inital insert file to bst, avl, and splay tree. then performs operations based on the requested action in the operations file
//Date Created: 2/23/18
#include "pch.h"
#include "BinarySearchTree.h"
#include <cstdlib>

BinarySearchTree::BinarySearchTree()
{
}


BinarySearchTree::~BinarySearchTree()
{
}

int BinarySearchTree::getHeight(node* input)
{
	if (input == NULL)
		return 0;
	else
	{
		// find depth of left and right nodes
		int lDepth = getHeight(input->left);
		int rDepth = getHeight(input->right);

		
		if (lDepth > rDepth)
			return(lDepth + 1);
		else return(rDepth + 1);
	}
}

int BinarySearchTree::insert(int x)
{
	int opCount = 0;
	node* newNode = new node();
	newNode->twin = NULL;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->value = x;

	if (root == NULL) {
		root = newNode;
		opCount = 1;
	}
	else {
		node* current = root;

		while (current != NULL) {
			if (x == current->value) {
				// handle the twin node scenario
				while (current->twin != NULL) {
					current = current->twin;
					opCount++;
				}
				current->twin = newNode;
				return opCount;
			}
			// go to the left
			else if (x < current->value) {
				if (current->left == NULL) {
					current->left = newNode;
					opCount++;
					return opCount;
				}
				else{
					current = current->left;
					opCount++;
				}
			}
			// go to the right
			else if (x > current->value) {
				if (current->right == NULL) {
					current->right = newNode;
					opCount++;
					return opCount;
				}
				else {
					current = current->right;
					opCount++;
				}
			}
		}
		current = newNode;
	}

	return opCount;
}

int BinarySearchTree::search(int x)
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
		// go left
		else if (x < current->value) {
			current = current->left;
			opCount++;
		}
		// go right
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
}

BinarySearchTree::node * BinarySearchTree::getMinNode(node * input)
{
	node *current = input;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

BinarySearchTree::node * BinarySearchTree::deleteRecursive(int x, node * input, int * count)
{
	if (input == NULL) {
		return input;
	}
	else if (input->value > x) {
		*count+=1;
		input->left = deleteRecursive(x, input->left, count);
	}
	else if (input->value < x) {
		*count+= 1;
		input->right = deleteRecursive(x, input->right, count);
	}
	else if (input->value == x) {
		if (input->twin != NULL) {
			node* temp = input;
			while (temp->twin->twin != NULL) {
				temp = temp->twin;
				*count += 1;
			}
			free(temp->twin);
			temp->twin = NULL;
		}
		else {
			if (input->left != NULL && input->right != NULL) { // neither the left or right side is empty
				node* temp = getMinNode(input->right);
				input->value = temp->value;
				input->right = deleteRecursive(temp->value, input->right, count);
				count += 1;
			}
			else if (input->left == NULL) {
				node* temp = input->right;
				free(input); // deallocate the memory for the node
				return temp;
			}
			else if (input->right == NULL) {
				node* temp = input->left;
				free(input);
				return temp;
			}

		}
	}

	return input;
}

string BinarySearchTree::printRecursive(node* input, int spCount)
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

int BinarySearchTree::deleteValue(int x)
{
	int opCount = 0;
	root = deleteRecursive(x, root, &opCount);
	return opCount;
}

string BinarySearchTree::printTree()
{
	string structure = printRecursive(root, 0);

	return structure;
}

int BinarySearchTree::maxHeight()
{
	return getHeight(root);
}
