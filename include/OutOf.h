#pragma once
#include "IHeuristic.h"
#include <map>
class OutOf : public IHeuristic
{
private:
	int _size;
	std::map<int, std::pair<int, int> > _helper;
public:
	OutOf(Node * solution);
	~OutOf(void);
	int getH(Node * beforeState, Node* currentState);
};
