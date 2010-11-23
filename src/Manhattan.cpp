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

int Manhattan::getH(Node * n)
{
	int cost = 0;
	for (int i = 0 ; i < _size ; i++)
	{
		for (int j = 0 ; j < _size ; j++)
		{
			int k = this->_helper[n->State[i][j]].first;
			int l = this->_helper[n->State[i][j]].second;
			cost += (k > i ? k - i : i - k);
			cost += (l > j ? l - j : j - l);
		}
	}
	std::cout << n->G << std::endl;
	//cost += n->G;
	return cost;
}