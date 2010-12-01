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
	std::multimap<int, Node *> _openList2;
	std::map<std::pair<int, int>, std::list<Node*> > _closedList2;
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
	bool isInClosedList(Node* n);
	bool isInOpenList(Node * n);
	void solutionFound(Node* n);
	void findLowestInClosedList(Node * n, std::list<Node*>::iterator &);
	int getClosedListCount();
	void createNewNode(Node *parent, Node *newNode);
	void showInfo();
};

#endif
