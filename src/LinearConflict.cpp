#include "LinearConflict.h"
#include "Node.h"
#include <iostream>

LinearConflict::LinearConflict(Node * solution)
{
	_size = solution->Size;
	for (int i = 0 ; i < _size ; i++)
		for (int j = 0 ; j < _size ; j++)
			this->_helper[solution->State[i][j]] = std::pair<int, int>(i, j);
}

LinearConflict::~LinearConflict(void)
{
}

int LinearConflict::getH(Node * beforeState, Node* currentState)
{
	int cost = 0;
	for (int i = 0 ; i < _size ; i++)
	{
		for (int j = 0 ; j < _size ; j++)
		{
			// iterates on the numbers of the state
			int k = this->_helper[currentState->State[i][j]].first;
			int l = this->_helper[currentState->State[i][j]].second;
			cost += (k > i ? k - i : i - k);
			cost += (l > j ? l - j : j - l);

//Linear Conflict Tiles Definition: Two tiles tj and tk are in a linear conflict if tj and tk are in the same line, the goal positions of tj and tk are both in that line, tj is to the right of tk and goal position of tj is to the left of the goal position of tk.
//
//The linear conflict adds at least two moves to the Manhattan Distance of the two conflicting tiles, by forcing them to surround one another. Therefore the heuristic function will add a cost of 2 moves for each pair of conflicting tiles.


		}
	}
	return cost;
}