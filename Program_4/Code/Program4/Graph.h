/*!
 * Author: Jason Hogan
 * Description: Developed for CIS 3501 program #4. Generates a graph based on datasets inputted and finds the hamiltonian cycle.
 *
 */
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "DualStreams.h"

using namespace std;

/*!
 * Handles all functionality related to creating, modifying, and processing the graph.
 * 
 */
class Graph
{
private:
	vector<vector<int>> adjMatrix;
public:
	Graph();
	Graph(int size);
	~Graph();

	void addEdge(int v1, int v2);
	void printGraph();
	bool findHamiltonianCycle(vector<int>* cycle);
	void hamiltonianCycle();
};