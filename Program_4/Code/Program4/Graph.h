#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "DualStreams.h"

using namespace std;
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