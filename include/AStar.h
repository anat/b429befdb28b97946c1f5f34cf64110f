#ifndef		_ASTAR_H_
# define	_ASTAR_H_

#include <list>
#include "Node.h"
#include "IHeuristic.h"
#include "Manhattan.h"

class AStar
{
private:
	Node* _initialState;
	Node* _solution;
	int	_size;
	std::list<Node*> _openList;
	std::list<Node*> _closedList;
	int** _matrixHelper;
	time_t _startTime;
	IHeuristic* _heuristic;
public:
	AStar(int size, int** initialState);
	void getPossibleMove(Node * n);
	~AStar(void);
	void run();
	int getMatrixValue(int y, int x);
	Node* getSolution();
	int** fillMatrix();
	bool AStar::isInClosedList(Node* n);
	void AStar::getBestNode(std::list<Node*>::iterator & current);
	void showOpenList();
	void showClosedList();
};

#endif