//Program Name: Trees and more Trees
//Programmer Name: Jason Hogan
//Description: Reads integers from an inital insert file to bst, avl, and splay tree. then performs operations based on the requested action in the operations file
//Date Created: 2/23/18

#include "pch.h"
#include <iostream>
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "SplayTree.h"
#include <string>
#include <fstream>
using namespace std;

void log(const std::string &input, string fileName) {
	ofstream filestream(fileName, std::ios_base::app | std::ios_base::out);
	filestream.flush();
	cout.flush();
	std::cout << input << endl;
	filestream << input << endl;
	filestream.close();

}

/*int main() {
	AvlTree avl;

	string tree;
	int i, a, ia, ai, aa, ii, opCount;

	cout << "Zig";

	opCount = i = a = ia = ai = aa = ii = 0;
	avl.insert(10, &opCount, &i, &a, &ia);
	tree = avl.printTree();
	cout << tree;
	cout << "\n===========================" << endl;
	opCount = i = a = ia = ai = aa = ii = 0;
	avl.insert(5, &opCount, &i, &a, &ia);
	tree = avl.printTree();
	cout << tree;
	cout << "\n===========================" << endl;
	avl.insert(7, &opCount, &i, &a, &ia);
	tree = avl.printTree();
	cout << tree;
	cout << "\n===========================" << endl;
	system("pause");
}*/


int main()
{
	string bstLog = "bst_3_2.txt";
	string avlLog = "avl_3_2.txt";
	string splayLog = "splay_3_2.txt";
	string metricLog = "metrics_3_2.txt";

	cout << "Enter an initial input file: ";
	string initFile;
	getline(cin, initFile);
	cout << endl;
	ifstream initStream(initFile);
	if (!initStream) {
		cout << initFile + " Does not exist!" << endl;
		system("pause");
		return 0;
	}
	else if (initStream.peek() == ifstream::traits_type::eof()) {
		cout << initFile + " File is empty!" << endl;
		system("pause");
		return 0;
	}

	BinarySearchTree bst;
	AvlTree avl;
	SplayTree splay;
	int metrics[3][3] = {{ 0,0,0 }, { 0,0,0 }, {0, 0, 0}};

	string line;
	while (getline(initStream, line)) {
		int opCount;
		string vis;

		int rr = 0;
		int ll = 0;
		int lr = 0;
		int rl = 0;

		log("Inserting " + line, bstLog);
		opCount = bst.insert(stoi(line));
		vis = bst.printTree();
		log(vis, bstLog);
		log("Tree height is: " + to_string(bst.maxHeight()), bstLog);
		log("======================================================", bstLog);


		log("Inserting " + line, avlLog);
		opCount = avl.insert(stoi(line),&ll,&rr,&lr,&rl);
		vis = avl.printTree();
		log(vis, avlLog);
		log("Tree height is: " + to_string(avl.maxHeight()), avlLog);
		log("right-right: " + to_string(rr), avlLog);
		log("right-left: " + to_string(rl), avlLog);
		log("left-right: " + to_string(lr), avlLog);
		log("left-left: " + to_string(ll), avlLog);
		log("======================================================", avlLog);

		int i, a, ia, ai, aa, ii;
		i = a = ia = ai = aa = ii = 0;

		log("Inserting " + line, splayLog);
		opCount = 0;
		splay.insert(stoi(line), &opCount, &i, &a, &ia, &ai, &ii, &aa);
		vis = splay.printTree();
		log(vis, splayLog);
		log("Tree height is: " + to_string(bst.maxHeight()), splayLog);
		log("======================================================", splayLog);

		
	}


	cout << "Enter an opertations file: ";
	string opFile;
	getline(cin, opFile);
	cout << endl;
	ifstream opStream(opFile);
	if (!opStream) {
		cout << opFile + " Does not exist!" << endl;
		system("pause");

		return 0;
	}
	else if (opStream.peek() == ifstream::traits_type::eof()) {
		cout << opFile + " File is empty!" << endl;
		system("pause");

		return 0;
	}

	while (getline(opStream, line)) {
		char action = line.at(0);
		int value = stoi(line.substr(2));
		int opCount = 0;
		string vis;
		//cout << "[" << action << "]" << endl;
		//cout << "[" << to_string(value) << "]" << endl;
		if (action == 'S') {
			opCount = bst.search(value);
			if (opCount > 0) {
				log("Value found: " + to_string(value), bstLog);
				log("Operations: " + to_string(opCount), bstLog);
				log("======================================================", bstLog);

				metrics[1][0] += opCount;
			}
			else {
				log("Value not found: " + to_string(value), bstLog);
				log("Operations: " + to_string(opCount * -1), bstLog);
				log("======================================================", bstLog);

				metrics[1][0] += opCount * -1;
			}

			opCount = avl.search(value);
			if (opCount > 0) {
				log("Value found: " + to_string(value), avlLog);
				log("Operations: " + to_string(opCount), avlLog);
				log("======================================================", avlLog);

				metrics[1][1] += opCount;
			}
			else {
				log("Value not found: " + to_string(value), avlLog);
				log("Operations: " + to_string(opCount * -1), avlLog);
				log("======================================================", avlLog);

				metrics[1][1] += opCount * -1;
			}

			int i, a, ia, ai, aa, ii;
			opCount = i = a = ia = ai = aa = ii = 0;
			splay.search(value, &opCount, &i, &a, &ia, &ai, &ii, &aa);
			if (opCount > 0) {
				log("Found: " + to_string(value), splayLog);
				vis = splay.printTree();
				log(vis, splayLog);
				log("Tree height is: " + to_string(splay.getMaxHeight()), splayLog);
				log("zig: " + to_string(i), splayLog);
				log("zag: " + to_string(a), splayLog);
				log("zigzig: " + to_string(ii), splayLog);
				log("zigzag: " + to_string(ia), splayLog);
				log("zagzag: " + to_string(aa), splayLog);
				log("zagzig: " + to_string(ai), splayLog);
				log("======================================================", splayLog);
				metrics[1][2] += opCount;
			}
			else {
				log("Value not found: " + to_string(value), splayLog);
				log("Operations: " + to_string(opCount * -1), splayLog);
				vis = splay.printTree();
				log(vis, splayLog);
				log("Tree height is: " + to_string(splay.getMaxHeight()), splayLog);
				log("======================================================", splayLog);
				metrics[1][2] += opCount * -1;
			}
		}
		else if (action == 'I') {
			log("Inserting " + to_string(value), bstLog);
			opCount = bst.insert(value);
			vis = bst.printTree();
			log(vis, bstLog);
			log("Tree height is: " + to_string(bst.maxHeight()), bstLog);
			log("======================================================", avlLog);

			metrics[0][0] += opCount;

			int rr = 0;
			int ll = 0;
			int lr = 0;
			int rl = 0;

			log("Inserting " + to_string(value), avlLog);
			opCount = avl.insert(value, &ll, &rr, &lr, &rl);
			vis = avl.printTree();
			log(vis, avlLog);
			log("Tree height is: " + to_string(avl.maxHeight()), avlLog);
			log("right-right: " + to_string(rr), avlLog);
			log("right-left: " + to_string(rl), avlLog);
			log("left-right: " + to_string(lr), avlLog);
			log("left-left: " + to_string(ll), avlLog);
			log("======================================================", avlLog);

			metrics[0][1] += opCount;

			int i, a, ia, ai, aa, ii;
			i = a = ia = ai = aa = ii = 0;

			log("Inserting " + to_string(value), splayLog);
			opCount = 0;
			splay.insert(value, &opCount, &i, &a, &ia, &ai, &ii, &aa);
			vis = splay.printTree();
			log(vis, splayLog);
			log("Tree height is: " + to_string(splay.getMaxHeight()), splayLog);
			log("zig: " + to_string(i), splayLog);
			log("zag: " + to_string(a), splayLog);
			log("zigzig: " + to_string(ii), splayLog);
			log("zigzag: " + to_string(ia), splayLog);
			log("zagzag: " + to_string(aa), splayLog);
			log("zagzig: " + to_string(ai), splayLog);
			log("======================================================", splayLog);
			metrics[0][2] += opCount;
		}
		else if (action == 'D') {
			opCount = bst.deleteValue(value);
			if (opCount > 0) {
				log("Deleted: " + to_string(value), bstLog);
				log("Operations: " + to_string(opCount), bstLog);

				vis = bst.printTree();
				log(vis, bstLog);
				log("Tree height is: " + to_string(bst.maxHeight()), bstLog);
				log("======================================================", bstLog);

				metrics[2][0] += opCount;
			}
			else {
				log("Could not delete: " + to_string(value), bstLog);
				log("Operations: " + to_string(opCount * -1), bstLog);
				vis = bst.printTree();
				log(vis, bstLog);
				log("Tree height is: " + to_string(bst.maxHeight()), bstLog);
				log("======================================================", bstLog);

				metrics[2][0] += opCount * -1;
			}

			int rr = 0;
			int ll = 0;
			int lr = 0;
			int rl = 0;

			opCount = avl.deleteValue(value,&ll, &rr, &lr, &rl);
			if (opCount > 0) {
				log("Deleted: " + to_string(value), avlLog);
				log("Operations: " + to_string(opCount), avlLog);
				vis = avl.printTree();
				log(vis, avlLog);
				log("Tree height is: " + to_string(avl.maxHeight()), avlLog);
				log("right-right: " + to_string(rr), avlLog);
				log("right-left: " + to_string(rl), avlLog);
				log("left-right: " + to_string(lr), avlLog);
				log("left-left: " + to_string(ll), avlLog);
				log("======================================================", avlLog);

				metrics[2][1] += opCount;
			}
			else {
				log("Could not delete: " + to_string(value), avlLog);
				log("Operations: " + to_string(opCount * -1), avlLog);
				vis = avl.printTree();
				log(vis, avlLog);
				log("Tree height is: " + to_string(avl.maxHeight()), avlLog);
				log("======================================================", avlLog);
				metrics[2][1] += opCount * -1;
			}

			int i, a, ia, ai, aa, ii;
			opCount = i = a = ia = ai = aa = ii = 0;
			splay.deleteNode(value, &opCount, &i, &a, &ia, &ai, &ii, &aa);
			if (opCount > 0) {
				log("Deleted: " + to_string(value), splayLog);
				vis = splay.printTree();
				log(vis, splayLog);
				log("Tree height is: " + to_string(splay.getMaxHeight()), splayLog);
				log("zig: " + to_string(i), splayLog);
				log("zag: " + to_string(a), splayLog);
				log("zigzig: " + to_string(ii), splayLog);
				log("zigzag: " + to_string(ia), splayLog);
				log("zagzag: " + to_string(aa), splayLog);
				log("zagzig: " + to_string(ai), splayLog);
				log("======================================================", splayLog);
				metrics[2][2] += opCount;
			}
			else {
				log("Could not delete: " + to_string(value), splayLog);
				log("Operations: " + to_string(opCount * -1), splayLog);
				vis = splay.printTree();
				log(vis, splayLog);
				log("Tree height is: " + to_string(splay.getMaxHeight()), splayLog);
				log("======================================================", splayLog);
				metrics[2][2] += opCount * -1;
			}
		}
		else {
			cout << "[ERROR] Invalid input line: " << line << endl;
		}
	}

	log("--------Inserts--------", metricLog);
	log("BST: " + to_string(metrics[0][0]), metricLog);
	log("AVL: " + to_string(metrics[0][1]), metricLog);
	log("Splay: " + to_string(metrics[0][2]), metricLog);
	log("--------Searches--------", metricLog);
	log("BST: " + to_string(metrics[1][0]), metricLog);
	log("AVL: " + to_string(metrics[1][1]), metricLog);
	log("Splay: " + to_string(metrics[1][2]), metricLog);
	log("--------Deletes--------", metricLog);
	log("BST: " + to_string(metrics[2][0]), metricLog);
	log("AVL: " + to_string(metrics[2][1]), metricLog);
	log("Splay: " + to_string(metrics[2][2]), metricLog);
	
	system("pause");
}