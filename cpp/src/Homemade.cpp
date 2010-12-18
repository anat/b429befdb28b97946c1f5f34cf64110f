#include "Homemade.h"
#include "Node.h"
#include <iostream>

Homemade::Homemade()
{
	std::cout << "Strategy : Homemade Heuristic" << std::endl;
}

Homemade::~Homemade(void)
{
}

double Homemade::getH(Node * beforeState, Node* currentState)
{
	double cost = 0;
	double tileCost;
	for (int i = 0 ; i < (_size * _size) ; i++)
	{
		if (currentState->State[i] != BLANK)
		{
			int k = this->_helper[currentState->State[i]].first;
			int l = this->_helper[currentState->State[i]].second;
			int x = Node::getX(i);
			int y = Node::getY(i);
			tileCost = (k > x ? k - x : x - k) + (l > y ? l - y : y - l);
			double tmp = tileCost * tileCost; 

			tmp = (tmp > 1) ? tmp / 2 : tmp;
			cost += tmp;
		}
	}

	return cost;
}

void Homemade::setSolution(Node *solution)
{
	_size = Node::Size;
	for (int i = 0 ; i < (Node::Size * Node::Size) ; i++)
		this->_helper[solution->State[i]] = std::pair<int, int>(Node::getX(i), Node::getY(i));
}