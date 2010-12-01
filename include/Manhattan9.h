#ifndef		_MANHATTAN9_H_
#define		_MANHATTAN9_H_

#include "IHeuristic.h"
#include <map>

class Manhattan9 : public IHeuristic
{
private:
	int _size;
	std::map<int, std::pair<int, int> > _helper;
public:
	Manhattan9(Node * solution);
	~Manhattan9(void);
	int getH(Node * beforeState, Node* currentState);
};

#endif
