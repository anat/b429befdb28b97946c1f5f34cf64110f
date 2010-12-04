#include "Manhattan.h"
#include "Node.h"
#include <iostream>

unsigned char Node::Size;

Manhattan::Manhattan()
{
	std::cout << "Strategy : Manhattan Heuristic" << std::endl;
}

Manhattan::~Manhattan(void)
{
}

int Manhattan::getH(Node * beforeState, Node* currentState)
{
	int cost = 0;
	for (int i = 0 ; i < (_size * _size) ; i++)
	{
			int k = this->_helper[currentState->State[i]].first;
			int l = this->_helper[currentState->State[i]].second;
			int x = Node::getX(i);
			int y = Node::getY(i);
			cost += (k > x ? k - x : x - k);
			cost += (l > y ? l - y : y - l);
	}
	return cost;
}

void Manhattan::setSolution(Node *solution)
{
	_size = Node::Size;
	for (int i = 0 ; i < (Node::Size * Node::Size) ; i++)
		this->_helper[solution->State[i]] = std::pair<int, int>(Node::getX(i), Node::getY(i));
}