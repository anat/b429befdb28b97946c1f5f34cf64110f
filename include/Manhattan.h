#ifndef		_MANHATTAN_H_
#define		_MANHATTAN_H_

#include "IHeuristic.h"
#include <map>

class Manhattan : public IHeuristic
{
private:
	int _size;
	std::map<int, std::pair<int, int> > _helper;
public:
	Manhattan();
	~Manhattan(void);
	int getH(Node * beforeState, Node* currentState);
	void setSolution(Node *solution);
};

#endif
