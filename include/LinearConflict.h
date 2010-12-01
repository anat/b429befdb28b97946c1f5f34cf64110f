#pragma once
#include "IHeuristic.h"
#include <map>

class LinearConflict : public IHeuristic
{
private:
	int _size;
	std::map<int, std::pair<int, int> > _helper;
public:
	LinearConflict(Node * solution);
	~LinearConflict(void);
	int getH(Node * beforeState, Node* currentState);
};
