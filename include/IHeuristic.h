#ifndef		_IHEURISTIC_H_
# define	_IHEURISTIC_H_

#include "Node.h"

class IHeuristic
{
public:
	IHeuristic(){};
	IHeuristic(Node * solution);
	virtual ~IHeuristic(void) {};
	virtual int getH(Node * beforeState, Node* currentState) = 0;
};

#endif