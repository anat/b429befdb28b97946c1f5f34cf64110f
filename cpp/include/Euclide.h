#ifndef		_EUCLIDE_H_
#define		_EUCLIDE_H_

#include "IHeuristic.h"
#include <map>

class Euclide : public IHeuristic
{
private:
	char _size;
	std::map<unsigned char, std::pair<unsigned char, unsigned char> > _helper;
public:
	Euclide();
	~Euclide(void);
	double getH(Node * beforeState, Node* currentState);
	void setSolution(Node *solution);
};

#endif
