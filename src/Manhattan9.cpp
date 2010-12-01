#include "Manhattan9.h"
#include "Node.h"
#include <iostream>

Manhattan9::Manhattan9(Node * solution)
{
	_size = solution->Size;
	for (int i = 0 ; i < _size ; i++)
		for (int j = 0 ; j < _size ; j++)
			this->_helper[solution->State[i][j]] = std::pair<int, int>(i, j);
}

Manhattan9::~Manhattan9(void)
{
}

int Manhattan9::getH(Node * beforeState, Node* currentState)
{
  beforeState = beforeState;
	int cost = 0;
	for (int i = 0 ; i < _size ; i++)
	{
		for (int j = 0 ; j < _size ; j++)
		{
			int k = this->_helper[currentState->State[i][j]].first;
			int l = this->_helper[currentState->State[i][j]].second;
			cost += (k > i ? k - i : i - k);
			cost += (l > j ? l - j : j - l);
		}
	}
	//std::cout << n->G << std::endl;
	//cost += n->G;
	return cost;
}
