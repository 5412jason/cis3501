// program2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "SplayTree.h"
#include <string>
using namespace std;

int main()
{
/*	BinarySearchTree bst;
	bst.insert(10);
	bst.insert(12);
	bst.insert(1);
	bst.insert(3);
	bst.insert(2);
	bst.insert(-4);
	bst.insert(20);
	bst.insert(11);

	std::string tree = bst.printTree();

	cout << tree << endl;

	cout << std::to_string(bst.search(-4)) << std::endl;
	cout << std::to_string(bst.search(13)) << std::endl;
	bst.deleteValue(12);
	bst.deleteValue(-2);
	cout << bst.printTree() << std::endl;
	*/
	int opCount, i, a, ia, ai, aa, ii;
	SplayTree splay;
	splay.insert(10, &opCount, &i, &a, &ia, &ai, &ii, &aa);
	std::string tree = splay.printTree();

	cout << tree << "\n"  << endl;
	splay.insert(12, &opCount, &i, &a, &ia, &ai, &ii, &aa);
	tree = splay.printTree();

	cout << tree << "\n" << endl;
	splay.insert(1, &opCount, &i, &a, &ia, &ai, &ii, &aa);
	tree = splay.printTree();

	cout << tree << "\n"  << endl;
	splay.insert(3, &opCount, &i, &a, &ia, &ai, &ii, &aa);
	tree = splay.printTree();

	cout << tree << "\n"  << endl;
	splay.insert(2, &opCount, &i, &a, &ia, &ai, &ii, &aa);
	tree = splay.printTree();

	cout << tree << "\n" <<endl;
	splay.insert(-4, &opCount, &i, &a, &ia, &ai, &ii, &aa);
	tree = splay.printTree();

	cout << tree << "\n"  << endl;
	splay.insert(11, &opCount, &i, &a, &ia, &ai, &ii, &aa);
	tree = splay.printTree();

	cout << tree << "\n"  << endl;


	//avl.deleteValue(12);
	//avl.deleteValue(2);
	//cout << avl.printTree() << std::endl;

	system("pause");
}
