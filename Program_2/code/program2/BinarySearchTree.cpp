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
		/* compute the depth of each subtree */
		int lDepth = getHeight(input->left);
		int rDepth = getHeight(input->right);

		/* use the larger one */
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
			while (temp->twin != NULL) {
				temp = temp->twin;
				*count += 1;
			}
			free(temp);
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
