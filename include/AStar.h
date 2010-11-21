#pragma once

#include <list>
#include "Node.h"
#define BLANK 0
class AStar
{
private:
	Node* _initialState;
	Node* _solution;
	int	_size;
	std::list<Node*> _openList;
	std::list<Node*> _closedList;
	int** _matrixHelper;
public:
	AStar(int size, int** initialState);
	void getPossibleMove(Node * n);
	~AStar(void);
	void run();
	void showNode(Node *n);
	int getMatrixValue(int y, int x);
	Node* getSolution();
	int** fillMatrix();
	bool AStar::isInClosedList(std::list<Node*>::iterator check);
	void AStar::getBestNode(std::list<Node*>::iterator & current);
};
