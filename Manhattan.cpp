#include "Manhattan.h"
#include "Node.h"
#include <iostream>
Manhattan::Manhattan(Node * solution)
{
	_size = solution->Size;
	for (int i = 0 ; i < _size ; i++)
		for (int j = 0 ; j < _size ; j++)
			this->_helper[solution->State[i][j]] = std::pair<int, int>(i, j);
}

Manhattan::~Manhattan(void)
{
}

int Manhattan::getH(Node * beforeState, Node* currentState)
{
	int cost = 0;
	int n = currentState->State[beforeState->BlankX][beforeState->BlankY];
	int i = beforeState->BlankX;
	int j = beforeState->BlankY;
	int k = this->_helper[n].first;
	int l = this->_helper[n].second;
	cost += (k > i ? k - i : i - k);
	cost += (l > j ? l - j : j - l);

	//for (int i = 0 ; i < _size ; i++)
	//{
	//	for (int j = 0 ; j < _size ; j++)
	//	{
	//		int k = this->_helper[currentState->State[i][j]].first;
	//		int l = this->_helper[currentState->State[i][j]].second;
	//		cost += (k > i ? k - i : i - k);
	//		cost += (l > j ? l - j : j - l);
	//	}
	//}
	return cost;
}