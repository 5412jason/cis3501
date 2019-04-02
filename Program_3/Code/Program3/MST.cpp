#include "MST.h"



MST::MST()
{
}

MST::MST(vector<Vertex> v)
{
	vertices = v;
	vector<vector<float>> m(vertices.size(), vector<float>(vertices.size()));
	adjMatrix = m;
}


MST::~MST()
{
}

void MST::generateMST()
{
	roots.clear();
	visited.clear();
	if (adjMatrix.size() == 0) {
		cout << "[ERROR] Cannot create MST, the adjacency matrix is empty" << endl;
		return;
	}
	int maxVertices = vertices.size();
	int currIndex = 0;
	int currRoot = 0;
	node* temp = NULL;
	roots.push_back(temp);
	Minheap heap = Minheap();
	while (visited.size() < maxVertices) {
		if (roots[currRoot] == NULL) {
			visited.push_back(vertices[currIndex]);
			node* temp = new node;
			temp->vertex = vertices[currIndex];
			roots[currRoot] = temp;
			int x = 0;
			while (x < maxVertices) {
				if (adjMatrix[currIndex][x] > 0.0) {
					bool alreadyVisited = false;
					for (int z = 0; z < visited.size(); z++) {
						if (vertices[x].getIdentifier() == visited[z].getIdentifier()) {
							alreadyVisited = true;
						}
					}
					if (alreadyVisited == false) {
						Edge e;
						e.setIdentifier1(vertices[currIndex].getIdentifier());
						e.setIdentifier2(vertices[x].getIdentifier());
						e.setWeight(adjMatrix[currIndex][x]);
						heap.insertElement(e);
					}
				}
				x += 1;
			}
		}
		else if (!heap.isEmpty()) {
			Edge e = heap.removeMinElement();
			for (int i = 0; i < vertices.size(); i++) {
				if (vertices[i].getIdentifier() == e.getIdentifier2()) {
					currIndex = i;
				}
			}
			bool alreadyVisited = false;
			for (int z = 0; z < visited.size(); z++) {
				if (vertices[currIndex].getIdentifier() == visited[z].getIdentifier()) {
					alreadyVisited = true;
				}
			}
			if (alreadyVisited == false) {
				visited.push_back(vertices[currIndex]);
				int x = 0;
				while (x < maxVertices) {
					if (adjMatrix[currIndex][x] > 0.0) {
						alreadyVisited = false;
						for (int z = 0; z < visited.size(); z++) {
							if (vertices[x].getIdentifier() == visited[z].getIdentifier()) {
								alreadyVisited = true;
							}
						}
						if (alreadyVisited == false) {
							Edge e;
							e.setIdentifier1(vertices[currIndex].getIdentifier());
							e.setIdentifier2(vertices[x].getIdentifier());
							e.setWeight(adjMatrix[currIndex][x]);
							heap.insertElement(e);
						}
					}
					x += 1;
				}
				node* temp = new node;
				temp->vertex = vertices[currIndex];
				node* parent = findNode(roots[currRoot], e.getIdentifier1());
				if (!parent->child) {
					parent->child = temp;
					temp->parent = parent;
					temp->weight = e.getWeight();
				}
				else {
					node* current = parent->child;
					while (current->sibling) {
						current = current->sibling;
					}
					current->sibling = temp;
					temp->parent = parent;
					temp->weight = e.getWeight();
				}
			}
		}
		else {
			currRoot += 1;
			node* temp = NULL;
			roots.push_back(temp);
			bool contains = false;
			bool next = false;
			for (int i = 0; i < vertices.size(); i++) {
				if (next == false) {
					contains = false;
					for (int x = 0; x < visited.size(); x++) {
						if (vertices[i].getIdentifier() != visited[x].getIdentifier() && contains == false) {
							contains = false;
						}
						else {

							contains = true;
						}
					}
					if (contains == false) {
						currIndex = i;
						next = true;
					}
				}
			}
		}
	}
}

void MST::printMST(node* root, int level)
{
	int x = 0;
	while (x < level) {
		cout << ".";
		x += 1;
	}
	cout << root->vertex.getIdentifier() << endl;
	if (root->child) {
		printMST(root->child, level+1);
	}
	if (root->sibling) {
		printMST(root->sibling, level);
	}
}

void MST::printMST()
{
	for (int i = 0; i < roots.size(); i++) {
		if (roots[i] != NULL) {
			cout << "Printing MST " << to_string(i+1) << ":" << endl;
			printMST(roots[i], 0);
		}
	}
}

node * MST::findNode(node * root, string id)
{
	node* found = NULL;
	if (root->vertex.getIdentifier() == id) {
		return root;
	}
	if (root->child) {
		found = findNode(root->child, id);
		if (found) {
			return found;
		}
	}
	if (root->sibling) {
		found = findNode(root->sibling, id);
		if (found) {
			return found;
		}
	}
	return NULL;
}

float MST::findPath(string id1, string id2)
{
	int v1 = -1;
	int v2 = -1;
	for (int x = 0; x < vertices.size(); x++) {
		if (vertices[x].getIdentifier() == id1) {
			v1 = x;
		}
		if (vertices[x].getIdentifier() == id2) {
			v2 = x;
		}
	}
	if (v1 == -1 || v2 == -1) {
		cout << "[ERROR] Cannot find a path, one of the vertices does not exist" << endl;
		return 0.0f;
	}
	if (v1 == v2) {
		cout << "[ERROR] Cannot find a path, the vertices are identical" << endl;
		return 0.0f;
	}
	vector<float>* distances = new vector<float>(vertices.size()); 
	vector<bool>* included = new vector<bool>(vertices.size());

	for (int x = 0; x < distances->size(); x++) {
		(*distances)[x] = INFINITY;
		(*included)[x] = false;
	}

	(*distances)[v1] = 0.0f;

	for (int i = 0; i < vertices.size(); i++) {
		int x = minDist(distances, included);
		if (x == INFINITY) {
			cout << "[ERROR] The vertices may not exist in the same tree" << endl;
			return 0.0f;
		}
	}

	return 0.0f;
}

void MST::addVertex(string id)
{
	Vertex v;
	v.setIdentifier(id);
	for (int i = 0; i < vertices.size(); i++) {
		if (v.getIdentifier() == vertices[i].getIdentifier()) {
			cout << "[ERROR] Vertex already exists, cannot insert: " << id << endl;
			return;
		}
	}
	vertices.push_back(v);
	// increase the size of the adjacency matrix
	adjMatrix.resize(adjMatrix.size() + 1);
	for (int i = 0; i < adjMatrix.size(); i++) {
		adjMatrix[i].resize(adjMatrix.size());
	}
	
	generateMST();
}

void MST::addEdge(string id1, string id2, float weight)
{
	Edge e;
	e.setIdentifier1(id1);
	e.setIdentifier2(id2);
	e.setWeight(weight);
	bool v1Exists = false;
	bool v2Exists = false;
	int v1Index = -1;
	int v2Index = -1;
	//check for the vertices
	for (int x = 0; x < vertices.size(); x++) {
		if (vertices[x].getIdentifier() == e.getIdentifier1()) {
			v1Exists = true;
			v1Index = x;
		}
		if (vertices[x].getIdentifier() == e.getIdentifier2()) {
			v2Exists = true;
			v2Index = x;
		}
	}
	if (v1Exists == false || v2Exists == false) {
		cout << "[ERROR] One of the vertices in the edge do not exist: " << e.getIdentifier1()
			<< ", " << e.getIdentifier2() << endl;
		return;
	}
	if (v1Index == v2Index) {
		cout << "[ERROR] Cannot have an edge between two identical vertices" << endl;
	}

	adjMatrix[v1Index][v2Index] = e.getWeight();
	adjMatrix[v2Index][v1Index] = e.getWeight();
	edges.push_back(e);
	cout << "Added edge: " << e.getIdentifier1() << ", " << e.getIdentifier2()
		<< " with weight: " << e.getWeight() << endl;

	generateMST();
}

void MST::deleteVertex(string id)
{
	if (adjMatrix.size() > 0) {
		bool exists = false;
		int index = -1;
		for (int x = 0; x < vertices.size(); x++) {
			if (vertices[x].getIdentifier() == id) {
				index = x;
				exists = true;
			}
		}
		if (exists == false) {
			cout << "[ERROR] Vertex does not exist, cannot delete: " << id << endl;
			return;
		}
		// remove it from the edges vector
		for (int x = 0; x > edges.size(); x++) {
			if (edges[x].getIdentifier1() == id || edges[x].getIdentifier2() == id) {
				edges.erase(edges.begin() + x);
			}
		}
		// remove it from the vertices vector
		vertices.erase(vertices.begin() + index);

		// remove it from the adjacency matrix
		adjMatrix.erase(adjMatrix.begin() + index);
		for (int x = 0; x > adjMatrix.size(); x++) {
			adjMatrix[x].erase(adjMatrix[x].begin() + index);
		}
		generateMST();
	}
	else {
		cout << "[ERROR] The adjacency matrix is empty, nothing to delete" << endl;
	}
}

void MST::deleteEdge(string id1, string id2)
{
	for (int x = 0; x < edges.size(); x++) {
		if (edges[x].getIdentifier1() == id1 || edges[x].getIdentifier2() == id1) {
			if (edges[x].getIdentifier2() == id2 || edges[x].getIdentifier2() == id2) {
				edges.erase(edges.begin() + x);
				int v1 = -1;
				int v2 = -1;
				for (int i = 0; i < vertices.size(); i++) {
					if (vertices[i].getIdentifier() == id1) {
						v1 = i;
					}
					if (vertices[i].getIdentifier() == id2) {
						v2 = i;
					}
				}
				adjMatrix[v1][v2] = 0.0f;
				adjMatrix[v2][v1] = 0.0f;
				generateMST();
				cout << "Removed edge: " << id1 << ", " << id2 << endl;
				return;
			}
		}
	}
	cout << "[ERROR] Did not delete edge, could not find the edge: " << id1 << ", " << id2 << endl;
}

void MST::increaseWeight(string id1, string id2, float w)
{
	for (int x = 0; x < edges.size(); x++) {
		if (edges[x].getIdentifier1() == id1 || edges[x].getIdentifier2() == id1) {
			if (edges[x].getIdentifier2() == id2 || edges[x].getIdentifier2() == id2) {
				int newWeight = edges[x].getWeight() + w;
				if (newWeight <= 0.0f) {
					"[ERROR] New weight cannot be less than or equal to 0.0";
					return;
				}
				edges[x].setWeight(newWeight);
				int v1 = -1;
				int v2 = -1;
				for (int i = 0; i < vertices.size(); i++) {
					if (vertices[i].getIdentifier() == id1) {
						v1 = i;
					}
					if (vertices[i].getIdentifier() == id2) {
						v2 = i;
					}
				}
				adjMatrix[v1][v2] = newWeight;
				adjMatrix[v2][v1] = newWeight;
				generateMST();
				cout << "Increased edge weight to: " << to_string(newWeight) << ", " << id1 << ", " << id2 << endl;
				return;
			}
		}
	}
	cout << "[ERROR] Did not increase weight, could not find the edge: " << id1 << ", " << id2 << endl;
}

void MST::decreaseWeight(string id1, string id2, float w)
{
	for (int x = 0; x < edges.size(); x++) {
		if (edges[x].getIdentifier1() == id1 || edges[x].getIdentifier2() == id1) {
			if (edges[x].getIdentifier2() == id2 || edges[x].getIdentifier2() == id2) {
				int newWeight = edges[x].getWeight() - w;
				if (newWeight <= 0.0f) {
					"[ERROR] New weight cannot be less than or equal to 0.0";
					return;
				}
				edges[x].setWeight(newWeight);
				int v1 = -1;
				int v2 = -1;
				for (int i = 0; i < vertices.size(); i++) {
					if (vertices[i].getIdentifier() == id1) {
						v1 = i;
					}
					if (vertices[i].getIdentifier() == id2) {
						v2 = i;
					}
				}
				adjMatrix[v1][v2] = newWeight;
				adjMatrix[v2][v1] = newWeight;
				generateMST();
				cout << "Decreased edge weight to: " << to_string(newWeight) << ", " << id1 << ", " << id2 << endl;
				return;
			}
		}
	}
	cout << "[ERROR] Did not decrease weight, could not find the edge: " << id1 << ", " << id2 << endl;
}

int MST::minDist(vector<float>* dist, vector<bool>* incl)
{
	int min = INFINITY;
	int minIndex = INFINITY;
	for (int x = 0; x < dist->size(); x++) {
		if ((*incl)[x] == false && (*dist)[x] < INFINITY) {
			min = (*dist)[x];
			minIndex = x;
		}
	}
	return min == INFINITY ? INFINITY : minIndex;
}
