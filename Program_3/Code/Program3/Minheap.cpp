#include "Minheap.h"



Minheap::Minheap()
{
}


Minheap::~Minheap()
{
}

void Minheap::insertElement(Edge e)
{
	elements.push_back(e);
	int index = elements.size() - 1;
	while (index != 0 && elements[(index-1)/2].getWeight() > elements[index].getWeight()) {
		iter_swap(elements.begin() + ((index - 1) / 2), elements.begin() + index);
	}
}

Edge Minheap::removeMinElement()
{
	if (elements.size() <= 0) {
		return Edge();
	}
	if (elements.size() == 1) {
		Edge temp = elements[0];
		elements.pop_back();
		return temp;
	}
	Edge min = elements[0];
	elements[0] = elements[elements.size() - 1];
	elements.pop_back();
	heapify(0);
	return min;
}

bool Minheap::isEmpty()
{
	if (elements.size() <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void Minheap::heapify(int index)
{
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int smallest = index;


	if (left <= elements.size()-1) {
		if (smallest < elements.size() && elements[left].getWeight() < elements[index].getWeight()) {
			smallest = left;
		}
	}
	if (right <= elements.size() - 1) {
		if (right < elements.size() && elements[right].getWeight() < elements[smallest].getWeight()) {
			smallest = right;
		}
	}
	if (smallest != index) {
		Edge temp = elements[smallest];
		elements[smallest] = elements[index];
		elements[index] = temp;
		heapify(smallest);
	}
}
