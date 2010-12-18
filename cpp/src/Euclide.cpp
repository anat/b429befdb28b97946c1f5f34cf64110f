#include "Euclide.h"
#include "Node.h"
#include <iostream>
#include <math.h>

Euclide::Euclide()
{
	std::cout << "Strategy : Euclide Heuristic" << std::endl;
}

Euclide::~Euclide(void)
{
}

double Euclide::getH(Node * beforeState, Node* currentState)
{
	double cost = 0;
	for (int i = 0 ; i < (_size * _size) ; i++)
	{
		if (currentState->State[i] != BLANK)
		{
			int k = this->_helper[currentState->State[i]].first;
			int l = this->_helper[currentState->State[i]].second;
			int x = Node::getX(i);
			int y = Node::getY(i);
			x = (k > x ? k - x : x - k);
			y = (l > y ? l - y : y - l);
			cost += ::sqrt(static_cast<double>((x*x) + (y*y)));
		}
	}
	return cost;
}

void Euclide::setSolution(Node *solution)
{
	_size = Node::Size;
	for (int i = 0 ; i < (Node::Size * Node::Size) ; i++)
		this->_helper[solution->State[i]] = std::pair<int, int>(Node::getX(i), Node::getY(i));
}