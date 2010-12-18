#include "OutOf.h"
#include "Node.h"
#include <iostream>

OutOf::OutOf()
{
	std::cout << "Strategy : Out of row, Ouf of column Heuristic" << std::endl;
}

OutOf::~OutOf(void)
{
}

double OutOf::getH(Node * beforeState, Node* currentState)
{
	double cost = 0;
	for (int i = 0 ; i < (_size * _size) ; i++)
	{
			int k = this->_helper[currentState->State[i]].first;
			int l = this->_helper[currentState->State[i]].second;

			int x = Node::getX(currentState->State[i]);
			int y = Node::getY(currentState->State[i]);

			if (x != k)
				cost += 1;

			if (y != l)
				cost += 1;

			//cost += (k > x ? k - x : x - k);
			//cost += (l > y ? l - y : y - l);
	}
	return cost;
}

void OutOf::setSolution(Node *solution)
{
	_size = Node::Size;
	for (int i = 0 ; i < (Node::Size * Node::Size) ; i++)
		this->_helper[solution->State[i]] = std::pair<int, int>(Node::getX(i), Node::getY(i));
}