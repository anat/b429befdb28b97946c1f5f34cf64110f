#ifndef		_MANHATTAN_H_
#define		_MANHATTAN_H_

#include "IHeuristic.h"
#include <map>

class Manhattan : public IHeuristic
{
private:
	char _size;
	std::map<unsigned char, std::pair<unsigned char, unsigned char> > _helper;
public:
	Manhattan();
	~Manhattan(void);
	int getH(Node * beforeState, Node* currentState);
	void setSolution(Node *solution);
};

#endif
