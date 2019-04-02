#include "Edge.h"



Edge::Edge()
{
}


Edge::~Edge()
{
}

float Edge::getWeight()
{
	return weight;
}

void Edge::setWeight(float w)
{
	weight = w;
}

string Edge::getIdentifier1()
{
	return identifier1;
}

void Edge::setIdentifier1(string x)
{
	identifier1 = x;
}

string Edge::getIdentifier2()
{
	return identifier2;
}

void Edge::setIdentifier2(string x)
{
	identifier2 = x;
}
