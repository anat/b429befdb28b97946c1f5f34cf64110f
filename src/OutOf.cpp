#include "OutOf.h"

OutOf::OutOf(Node * solution)
{
  solution = solution;
}

OutOf::~OutOf(void)
{
}

int OutOf::getH(Node * beforeState, Node* currentState)
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
