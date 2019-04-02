#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "MST.h"
using namespace std;
// Test main function for testing the graph class with adjacency matrix
/*
void main() {
	string initVertexFile;
	string initEdgeFile;
	int vertexCount;
	int edgeCount;

	vector<Vertex> vertices;

	Graph graph;

	cout << "Enter the directory of the initial vertex file: ";
	getline(cin, initVertexFile);
	ifstream vstream(initVertexFile);
	if (vstream) {
		string input;
		getline(vstream, input);
		while (getline(vstream, input)) {

			Vertex v;
			v.setIdentifier(input);
			vertices.push_back(v);
			cout << "Adding vertex: " << v.getIdentifier() << endl;
		}
	}
	else {
		cout << "Cannot open file: " << initVertexFile << endl;
		system("PAUSE");
		return;
	}
	graph = Graph(vertices);
	graph.printGraph();

	cout << "Enter the directory of the initial edge file: ";
	getline(cin, initEdgeFile);
	// add the edges
	ifstream estream(initEdgeFile);
	if (estream) {
		string input;
		getline(estream, input);
		while (getline(estream, input)) {
			stringstream ss(input);
			vector<string> strs(istream_iterator<string>{ss}, istream_iterator<string>());
			Edge e;
			e.setIdentifier1(strs[0]);
			e.setIdentifier2(strs[1]);
			e.setWeight(strtof((strs[2]).c_str(), 0));

			graph.addEdge(e);
		}
	}
	else {
		cout << "Cannot open file: " << initVertexFile << endl;
		system("PAUSE");
		return;
	}

	graph.printGraph();

	system("PAUSE");
}
*/

void main() {
	string initVertexFile = "C:\\Users\\Jason\\Documents\\CIS3501\\Program_3\\Test_files\\test_1.txt";
	string initEdgeFile = "C:\\Users\\Jason\\Documents\\CIS3501\\Program_3\\Test_files\\test_e_1.txt";
	int vertexCount;
	int edgeCount;

	vector<Vertex> vertices;

	MST mst;

	cout << "Enter the directory of the initial vertex file: ";
	//getline(cin, initVertexFile);
	ifstream vstream(initVertexFile);
	if (vstream) {
		string input;
		getline(vstream, input);
		while (getline(vstream, input)) {

			Vertex v;
			v.setIdentifier(input);
			vertices.push_back(v);
			cout << "Adding vertex: " << v.getIdentifier() << endl;
		}
	}
	else {
		cout << "Cannot open file: " << initVertexFile << endl;
		system("PAUSE");
		return;
	}
	mst = MST(vertices);
	mst.printGraph();
	cout << "Enter the directory of the initial edge file: ";
	//getline(cin, initEdgeFile);
	// add the edges
	ifstream estream(initEdgeFile);
	if (estream) {
		string input;
		getline(estream, input);
		while (getline(estream, input)) {
			stringstream ss(input);
			vector<string> strs(istream_iterator<string>{ss}, istream_iterator<string>());
			/*Edge e;
			e.setIdentifier1(strs[0]);
			e.setIdentifier2(strs[1]);
			e.setWeight(strtof((strs[2]).c_str(), 0));*/
			float weight = strtof((strs[2]).c_str(), 0);
			mst.addEdge(strs[0], strs[1], weight);
		}
	}
	else {
		cout << "Cannot open file: " << initEdgeFile << endl;
		system("PAUSE");
		return;
	}

	mst.generateMST();

	mst.printGraph();
	mst.printMST();

	cout << "Would you like to enter directives via a file? (y/n): ";
	string input;
	getline(cin, input);
	if (input == "y") {
		string dirFile;
		cout << "Enter a directive file name: ";
		ifstream dStream(dirFile);
		if (dStream) {
			while (getline(dStream, input)) {
				stringstream ss(input);
				vector<string> strs(istream_iterator<string>{ss}, istream_iterator<string>());
				if (strs[0] == "print-graph") {
					mst.printGraph();
				}
				else if (strs[0] == "print-mst") {
					mst.printMST();
				}
				else if (strs[0] == "path") {
					mst.findPath(strs[1], strs[2]);
				}
				else if (strs[0] == "insert-vertex") {
					mst.addVertex(strs[1]);
				}
				else if (strs[0] == "insert-edge") {
					mst.addEdge(strs[1], strs[2], strtof((strs[2]).c_str(), 0));
				}
				else if (strs[0] == "decrease-weight") {
					mst.decreaseWeight(strs[1], strs[2], strtof((strs[3]).c_str(), 0));
				}
				else if (strs[0] == "increase-weight") {
					mst.increaseWeight(strs[1], strs[2], strtof((strs[3]).c_str(), 0));
				}
				else if (strs[0] == "delete-edge") {
					mst.deleteEdge(strs[1], strs[2]);
				}
				else if (strs[0] == "delete-vertex") {
					mst.deleteVertex(strs[1]);
				}
				else if (strs[0] == "quit") {
					cout << "Exiting the program" << endl;
					return;
				}
				else {
					cout << "[ERROR] Directive not recognized: " << input << endl;
				}
			}
		}
	}
	else {
		while (true) {
			cout << "Enter a directive (with attributes): ";
			getline(cin, input);
			stringstream ss(input);
			vector<string> strs(istream_iterator<string>{ss}, istream_iterator<string>());
			if (strs[0] == "print-graph") {
				mst.printGraph();
			}
			else if (strs[0] == "print-mst") {
				mst.printMST();
			}
			else if (strs[0] == "path") {
				mst.findPath(strs[1], strs[2]);
			}
			else if (strs[0] == "insert-vertex") {
				mst.addVertex(strs[1]);
			}
			else if (strs[0] == "insert-edge") {
				mst.addEdge(strs[1], strs[2], strtof((strs[3]).c_str(), 0));
			}
			else if (strs[0] == "decrease-weight") {
				mst.decreaseWeight(strs[1], strs[2], strtof((strs[3]).c_str(), 0));
			}
			else if (strs[0] == "increase-weight") {
				mst.increaseWeight(strs[1], strs[2], strtof((strs[3]).c_str(), 0));
			}
			else if (strs[0] == "delete-edge") {
				mst.deleteEdge(strs[1], strs[2]);
			}
			else if (strs[0] == "delete-vertex") {
				mst.deleteVertex(strs[1]);
			}
			else if (strs[0] == "quit") {
				cout << "Exiting the program" << endl;
				return;
			}
			else {
				cout << "[ERROR] Directive not recognized: " << input << endl;
			}
		}
	}
	system("PAUSE");
}