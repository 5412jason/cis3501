#include "Graph.h"
Graph::Graph()
{
}

Graph::Graph(int size)
{
	vector<vector<int>> m(size, vector<int>(size));
	adjMatrix = m;
}

Graph::~Graph()
{
}

void Graph::addEdge(int v1, int v2)
{
	DualStreams dsout("output.txt");
	bool valid = true;
	if (v1 < 0 || v1 >= adjMatrix.size()) {
		dsout << "    Vertex #1 does not exist: v" + to_string(v1+1) << "\n";
		valid = false;
	}
	if (v2 < 0 || v2 >= adjMatrix.size()) {
		dsout << "    Vertex #2 does not exist: v" + to_string(v2+1) << "\n";
		valid = false;
	}
	if (valid == false) {
		return;
	}
	// set the edge in the matrix

	adjMatrix[v1][v2] = 1;
	adjMatrix[v2][v1] = 1;
}

void Graph::printGraph()
{
	DualStreams dsout("output.txt");
	if (adjMatrix.size() != 0) {
		dsout << "Printing adjacency matrix for the graph: " << "\n";
		for (int x = 0; x < adjMatrix.size(); x++) {
			for (int i = 0; i < adjMatrix.size(); i++) {
				cout << to_string(adjMatrix[x][i]) << ", ";
			}
			cout << endl;
		}
	}
}

bool Graph::findHamiltonianCycle(vector<int>* cycle) 
{
	DualStreams dsout("output.txt");

	if (cycle->size() == adjMatrix.size()) {
		if (adjMatrix[cycle->back()][cycle->front()]) {
			cycle->push_back(cycle->front());
			return true;
		}
		return false;
	}
	for (int i = 0; i < adjMatrix.size(); i++) {
		if (adjMatrix[i][cycle->back()] == 1) {
			bool contains = false;
			for (int x = 0; x < cycle->size(); x++) {
				if ((*cycle)[x] == i) {
					contains = true;
				}
			}
			if (contains == false) {
				cycle->push_back(i);
				dsout << "Adding vertex " << to_string(i+1) << "\n";
				if (findHamiltonianCycle(cycle)) {
					return true;
				}
				else {
					cycle->pop_back();
					dsout << "Removing vertex " << to_string(i+1) << "\n";
				}
			}
		}
	}
	return false;
}

void Graph::hamiltonianCycle()
{
	DualStreams dsout("output.txt");

	vector<int>* cycle = new vector<int>();
	cycle->push_back(0); // Add the first vertex to the vector
	dsout << "Adding vertex " << to_string(1)<< "\n";
	if (findHamiltonianCycle(cycle) == true) {
		dsout << "Hamiltonian Cycle Exists: " << "\n";
		for (int x = 0; x < cycle->size(); x++) {
			dsout << to_string((*cycle)[x]+1) << " ";
		}
		dsout << "\n";
	}
	else {
		dsout << "No Hamiltonian Cycle found" << "\n";
	}
}
