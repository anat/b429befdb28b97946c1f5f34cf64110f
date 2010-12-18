#include "MisplacedTiles.h"
#include "Node.h"
#include <iostream>

MisplacedTiles::MisplacedTiles()
{
	std::cout << "Strategy : Misplaced Tiles Heuristic" << std::endl;
}

MisplacedTiles::~MisplacedTiles(void)
{
}

double MisplacedTiles::getH(Node * beforeState, Node* currentState)
{
	int cost = 0;
	for (int i = 0 ; i < (_size * _size) ; i++)
	{
		if (currentState->State[i] != BLANK)
		{
			if (this->_helper[currentState->State[i]].first != Node::getX(i) || this->_helper[currentState->State[i]].second !=  Node::getY(i))
				cost += 1;
		}
	}
	return cost;
}

void MisplacedTiles::setSolution(Node *solution)
{
	_size = Node::Size;
	for (int i = 0 ; i < (Node::Size * Node::Size) ; i++)
		this->_helper[solution->State[i]] = std::pair<int, int>(Node::getX(i), Node::getY(i));
}