#include "MisplacedTiles.h"
#include "Node.h"
#include <iostream>

MisplacedTiles::MisplacedTiles()
{
}

MisplacedTiles::~MisplacedTiles(void)
{
}

int MisplacedTiles::getH(Node * beforeState, Node* currentState)
{
  beforeState = beforeState;
	int cost = 0;
	for (int i = 0 ; i < _size ; i++)
	{
		for (int j = 0 ; j < _size ; j++)
		{
			if (this->_helper[currentState->State[i][j]].first != i || this->_helper[currentState->State[i][j]].second != j)
				cost++;
		}
	}
	return cost;
}

void MisplacedTiles::setSolution(Node *solution)
{
	_size = solution->Size;
	for (int i = 0 ; i < _size ; i++)
		for (int j = 0 ; j < _size ; j++)
			this->_helper[solution->State[i][j]] = std::pair<int, int>(i, j);
}