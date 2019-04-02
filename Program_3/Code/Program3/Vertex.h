#pragma once
#include <string>
using namespace std;
class Vertex
{
public:
	Vertex();
	~Vertex();

	string getIdentifier();
	void setIdentifier(string id);
private:
	string identifier;
};

