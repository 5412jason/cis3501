#include "Graph.h"


Graph::Graph()
{
	
}

Graph::Graph(vector<Vertex> v)
{
	vertices = v;
	// create the matrix with no edges of size v x v
	vector<vector<float>> m(vertices.size(), vector<float>(vertices.size()));
	adjMatrix = m;
}


Graph::~Graph()
{
}

void Graph::addVertex(Vertex v)
{
	vertices.push_back(v);
	// increase the size of the adjacency matrix
	adjMatrix.resize(adjMatrix.size() + 1);
	for (int i = 0; i < adjMatrix.size(); i++) {
		adjMatrix[i].resize(adjMatrix.size());
	}
}

void Graph::addEdge(Edge e)
{
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
}

void Graph::deleteVertex(string id)
{
	if (adjMatrix.size() > 0) {
		bool exists = false;
		int index = -1;
		for (int x = 0; x > vertices.size(); x++) {
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
	}
	else {
		cout << "[ERROR] The adjacency matrix is empty, nothing to delete" << endl;
	}
}

void Graph::deleteEdge(Edge e)
{
	for (int x = 0; x < edges.size(); x++) {
		if (edges[x].getIdentifier1() == e.getIdentifier1() || edges[x].getIdentifier2() == e.getIdentifier2()) {
			if (edges[x].getIdentifier2() == e.getIdentifier2() || edges[x].getIdentifier2() == e.getIdentifier2()) {
				edges.erase(edges.begin() + x);
				int v1 = -1;
				int v2 = -1;
				for (int i = 0; i < vertices.size(); i++) {
					if (vertices[i].getIdentifier() == e.getIdentifier1()) {
						v1 = i;
					}
					if (vertices[i].getIdentifier() == e.getIdentifier2()) {
						v2 = i;
					}
				}
				adjMatrix[v1][v2] = 0.0f;
				adjMatrix[v2][v1] = 0.0f;
				cout << "Removed edge: " << e.getIdentifier1() << ", " << e.getIdentifier2() << endl;
				return;
			}
		}
	}
	cout << "[ERROR] Did not delete edge, could not find the edge: " << e.getIdentifier1() << ", " << e.getIdentifier2() << endl;
}

void Graph::printGraph()
{
	if (adjMatrix.size() != 0) {
		cout << "Printing adjacency matrix for the graph: " << endl;
		for (int x = 0; x < vertices.size(); x++) {
			for (int i = 0; i < vertices.size(); i++) {
				cout << to_string(adjMatrix[x][i]) << ", ";
			}
			cout << endl;
		}
	}
}

void Graph::increaseWeight(string id1, string id2, float w)
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
				cout << "Increased edge weight to: " << to_string(newWeight) << ", " << id1 << ", " << id2 << endl;
				return;
			}
		}
	}
	cout << "[ERROR] Did not increase weight, could not find the edge: " <<id1<< ", " << id2 << endl;

}

void Graph::decreaseWeight(string id1, string id2, float w)
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
				cout << "Decreased edge weight to: " << to_string(newWeight) << ", " << id1 << ", " << id2 << endl;
				return;
			}
		}
	}
	cout << "[ERROR] Did not decrease weight, could not find the edge: " << id1 << ", " << id2 << endl;
}
