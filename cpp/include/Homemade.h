#ifndef		_HOMEMADE_H_
#define		_HOMEMADE_H_

#include "IHeuristic.h"
#include <map>

class Homemade : public IHeuristic
{
private:
	char _size;
	std::map<unsigned char, std::pair<unsigned char, unsigned char> > _helper;
public:
	Homemade();
	~Homemade(void);
	double getH(Node * beforeState, Node* currentState);
	void setSolution(Node *solution);
};

#endif
