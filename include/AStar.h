#ifndef		_ASTAR_H_
# define	_ASTAR_H_

#include <list>
#include "Node.h"
#include "IHeuristic.h"
#include "Manhattan.h"

#ifdef _WIN32
#include "Windows.h"
#else
#include "time.h"
#endif

class AStar
{
private:
	Node* _initialState;
	Node* _solution;
	int	_size;
	std::list<Node*> _openList;
	std::list<Node*> _closedList;
	int** _matrixHelper;
	char const * _file;
#ifdef _WIN32
	DWORD _startTime;
#else
	time_t _startTime;
#endif

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
};

#endif