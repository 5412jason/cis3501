/*!
 * Author: Jason Hogan
 * Description: Developed for CIS 3501 program #4. Generates a graph based on datasets inputted and finds the hamiltonian cycle.
 *
 */
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include "Graph.h"
#include "DualStreams.h"

using namespace std;

/*!
 * Main function that is called on applicaiton startup to test finding hamiltonian cycles on a graph (adjacency matrix).
 * 
 */
void main() {
	DualStreams dsout("output.txt");
	dsout.clearfile();
	dsout << "Enter the name of the input file: \n";
	string input;
	getline(cin, input);
	dsout << "Opening: " << input << "\n";

	ifstream in(input);
	if (in) {
		vector<Graph> graphs;
		int currentGraph = 0;
		int edgeCount = 0;
		while (getline(in, input)) {
			if (edgeCount == 0) {
				stringstream ss(input);
				vector<string> strs(istream_iterator<string>{ss}, istream_iterator<string>());
				Graph temp(stoi(strs[0]));
				edgeCount = stoi(strs[1]);
				graphs.push_back(temp);
				dsout << "Creating graph #" << to_string(graphs.size()) << " with " << strs[0] << " vertices and " << strs[1] << " edges\n";
				
			}
			else {
				stringstream ss(input);
				vector<string> strs(istream_iterator<string>{ss}, istream_iterator<string>());
				dsout << "  Adding edge: " << strs[0] << ", " << strs[1] << "\n";
				graphs.back().addEdge(stoi(strs[0])-1, stoi(strs[1])-1);
				edgeCount = edgeCount - 1;
			}
		}
		for (int x = 0; x < graphs.size(); x++) {
			dsout << "============ Graph #" << to_string(x + 1) << " ============\n";
			graphs[x].printGraph();
			graphs[x].hamiltonianCycle();
		}
	}
	else {
		dsout << "[ERROR] Could not open input file\n";
	}
	system("PAUSE");
}