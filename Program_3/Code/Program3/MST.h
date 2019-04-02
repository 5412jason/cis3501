#pragma once
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Minheap.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct node {
	Vertex vertex;
	node* child = NULL;
	node* sibling = NULL;
	node* parent = NULL;
	float weight = 0.0;
};
class MST :
	public Graph
{
public:
	MST();
	MST(vector<Vertex> v);
	~MST();
	void generateMST();
	void printMST(node* root, int level);
	void printMST();
	node* findNode(node* root, string id);
	float findPath(string id1, string id2);
	void addVertex(string v);
	void addEdge(string id1, string id2, float weight);
	void deleteVertex(string id);
	void deleteEdge(string id1, string id2);
	void increaseWeight(string id1, string id2, float w);
	void decreaseWeight(string id1, string id2, float w);
private:
	int minDist(vector<float>* dist, vector<bool>* incl);
	vector<node*> roots;
	vector<Vertex> visited;
};

