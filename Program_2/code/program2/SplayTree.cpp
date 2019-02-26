#include "SplayTree.h"
#include <cstdlib>


SplayTree::SplayTree()
{
}


SplayTree::~SplayTree()
{
}

void SplayTree::splay(node * input, int * opCount, int * i, int * a, int * ia, int * ai, int * ii, int * aa)
{
	while (true){
		node* parent1 = input->parent;
		if (parent1 == NULL) {
			break;
		}

		node* parent2 = parent1->parent;

		if (parent2 == NULL) {
			if (parent1->left == input) {
				*i += 1;
				zig(parent1);
			}
			else if(parent1->right == input) {
				*a += 1;
				zag(parent2);
			}
			*opCount += 1;
			break;
		}
		if (parent2->left == parent1) {
			if (parent1->left == input) {
				*ii += 1;
				zigzig(parent1);
			}
			else if (parent1->right == input) {
				*ai += 1;
				zagzig(parent1);
			}
			*opCount += 1;
		}
		if (parent2->right == parent1) {
			if (parent1->left == input) {
				*ia += 1;
				zigzag(parent1);
			}
			else if (parent1->right == input) {
				*aa += 1;
				zagzag(parent1);
			}
			*opCount++;
		}
	}
	root = input;
}

void SplayTree::insert(int x, int * opCount, int * i, int * a, int * ia, int * ai, int * ii, int * aa)
{
	node* newNode = new node;
	newNode->value = x;
	if (root == NULL) {
		*opCount += 1;
		root = newNode;
		return;
	}

	node* current = root;

	while (true) {
		*opCount += 1;
		if (current->value == x) {
			node* temp = current;
			// handle the twin node scenario
			while (temp->twin != NULL) {
				temp = temp->twin;
				*opCount += 1;
			}
			temp->twin = newNode;
			break;
		}
		else if (x < current->value) {
			if (current->left == NULL) {
				current->left = newNode;
				current = current->left;
				break;
			}
			else {
				current = current->left;
			}
		}
		else if (x > current->value) {
			if (current->right == NULL) {
				current->right = newNode;
				current = current->right;
				break;
			}
			else {
				current = current->right;
			}
		}
	}
	//bring the newly inserted node to the top
	splay(current, opCount, i, a, ia, ai, ii, aa);
}

void SplayTree::search(int x, int * opCount, int * i, int * a, int * ia, int * ai, int * ii, int * aa)
{
	bool found = false;

	if (root == NULL) {
		*opCount = 0;
		return;
	}
	node* current = root;
	while (current != NULL && found == false) {
		*opCount += 1;
		if (current->value == x) {
			found = true;
			break;
		}
		else if (current->value > x) {
			current = current->left;
		}
		else if (current->value < x) {
			current = current->right;
		}
	}
	if (!found) {
		*opCount = *opCount * -1;
		return;
	}
	splay(current, opCount, i, a, ia, ai, ii, aa);

}

void SplayTree::deleteNode(int x, int * opCount, int * i, int * a, int * ia, int * ai, int * ii, int * aa)
{
	bool found = false;

	if (root == NULL) {
		*opCount = 0;
		return;
	}
	node* current = root;
	while (current != NULL && found == false) {
		*opCount += 1;
		if (current->value == x) {
			found = true;
			break;
		}
		else if (current->value > x) {
			current = current->left;
		}
		else if (current->value < x) {
			current = current->right;
		}
	}
	if (!found) {
		*opCount = *opCount * -1;
		return;
	}
	splay(current, opCount, i, a, ia, ai, ii, aa);

	node* temp1 = current->left;
	if (temp1 == NULL) {
		root = current->right;
		root->parent = NULL;
		free(temp1);
		return;
	}
	while (temp1->right != NULL) {
		temp1 = temp1->right;
	}
	if (current->right != NULL) {
		temp1->right = current->right;
		current->right->parent = temp1;
	}
	root = current->left;
	root->parent = NULL;
	free(current);

}

string SplayTree::printTree()
{
	string structure = printRecursive(root, 0);

	return structure;
}

void SplayTree::rotateRight(node * input)
{
	node* temp1 = input->left;
	node* temp2 = temp1->right;
	node* parent1 = input->parent;
	if (parent1 != NULL) {
		if (parent1->right == input) {
			parent1->right = temp1;
		}
		else {
			parent1->left = temp1;
		}
	}
	if (temp2 != NULL) {
		temp2->parent = input;
	}
	temp1->parent = parent1;
	temp1->right = input;
	input->parent = temp1;
	input->left = temp2;
}

void SplayTree::rotateLeft(node * input)
{
	node* temp1 = input->right;
	node* temp2 = temp1->left;
	node* parent1 = input->parent;
	if (parent1 != NULL) {
		if (parent1->right == input) {
			parent1->right = temp1;
		}
		else {
			parent1->left = temp1;
		}
	}
	if (temp2 != NULL) {
		temp2->parent = input;
	}
	temp1->parent = parent1;
	temp1->left = input;
	input->parent = temp1;
	input->right = temp2;
}

void SplayTree::zig(node * input)
{
	rotateRight(input);
}

void SplayTree::zag(node * input)
{
	rotateLeft(input);
}

void SplayTree::zigzag(node * input)
{
	rotateRight(input);
	rotateLeft(input->parent);
}

void SplayTree::zigzig(node * input)
{
	rotateRight(input);
	rotateRight(input->parent);
}

void SplayTree::zagzig(node * input)
{
	rotateLeft(input);
	rotateRight(input->parent);
}

void SplayTree::zagzag(node * input)
{
	rotateLeft(input);
	rotateLeft(input->parent);
}

string SplayTree::printRecursive(node * input, int spCount)
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
