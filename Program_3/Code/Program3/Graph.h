#pragma once
#include <string>
#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include <iostream>
using namespace std;
class Graph
{
public:
	Graph();
	Graph(vector<Vertex> v);
	~Graph();
	void addVertex(Vertex v);
	void addEdge(Edge e);
	void deleteVertex(string id);
	void deleteEdge(Edge e);
	void printGraph();
	void increaseWeight(string id1, string id2, float w);
	void decreaseWeight(string id1, string id2, float w);

protected:
	vector<vector<float>> adjMatrix;
	vector<Vertex> vertices;
	vector<Edge> edges;
};

