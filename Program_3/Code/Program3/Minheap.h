#pragma once
#include "Edge.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Minheap
{
public:
	Minheap();
	~Minheap();
	void insertElement(Edge e);
	Edge removeMinElement();
	bool isEmpty();
	
private:
	int maxSize;
	vector<Edge> elements;
	void heapify(int index);
};

