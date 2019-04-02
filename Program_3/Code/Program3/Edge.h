#pragma once
#include <string>
using namespace std;

class Edge
{
public:
	Edge();
	~Edge();
	float getWeight();
	void setWeight(float w);
	string getIdentifier1();
	void setIdentifier1(string x);
	string getIdentifier2();
	void setIdentifier2(string x);

private:
	float weight;
	string identifier1;
	string identifier2;
};

