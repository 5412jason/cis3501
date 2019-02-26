#include "pch.h"
#include "AvlTree.h"
#include <algorithm>
using namespace std;

AvlTree::AvlTree()
{
}


AvlTree::~AvlTree()
{
}

AvlTree::node * AvlTree::rightRotation(node * input)
{
	node* temp1 = input->left;
	node* temp2 = input->right;
	
	temp1->right = input;
	input->left = temp2;

	input->height = max(input->right->height, input->left->height) + 1;
	temp1->height = max(temp1->right->height, temp1->left->height) + 1;

	return temp1;
}

AvlTree::node * AvlTree::leftRotation(node * input)
{
	node* temp1 = input->right;
	node* temp2 = temp1->left;

	temp1->left = input;
	input->right = temp2;

	input->height = max(input->right->height, input->left->height) + 1;
	temp1->height = max(temp1->right->height, temp1->left->height) + 1;

	return temp1;
}

AvlTree::node * AvlTree::doubleRightRotation(node * input)
{
	input->left = leftRotation(input->left);
	input = rightRotation(input);

	return input;
}

AvlTree::node * AvlTree::doubleLeftRotation(node * input)
{
	input->right = rightRotation(input->right);
	input = leftRotation(input);

	return input;
}

AvlTree::node * AvlTree::insertRecursive(int x, node * input, int * opCount)
{
	if (input == NULL) {
		node* newNode = new node();
		newNode->value = x;
		input = newNode;
	}
	else if (x < input->value) {

	}
	else if (x > input->value) {

	}
	else if (x == input->value) {

	}
	return nullptr;
}

