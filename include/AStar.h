#ifndef		_ASTAR_H_
# define	_ASTAR_H_

#include <list>
#include "Node.h"
#include "IHeuristic.h"
#include "time.h"
#include <map>

class AStar
{
private:
	Node* _initialState;
	Node* _solution;
	int	_size;
	std::list<Node*> _openList;
	std::map<std::pair<int, int>, std::list<Node*>> _closedList2;
	//std::list<Node*> _closedList;
	int** _matrixHelper;
	char const * _file;
	clock_t _startTime;

	IHeuristic* _heuristic;

public:
	AStar(int size, int** initialState);
	void getPossibleMove(Node * n);
	~AStar(void);
	void run(char const * file);
	int getMatrixValue(int y, int x);
	Node* getSolution();
	int** fillMatrix();
	bool AStar::isInClosedList(Node* n);
	void AStar::getBestNode(std::list<Node*>::iterator & current);
	void showOpenList(bool onlyH = false);
	void showClosedList();
	void solutionFound(Node* n);
	void findLowestInClosedList(Node * n, std::list<Node*>::iterator &);
	int getClosedListCount();
};

#endif