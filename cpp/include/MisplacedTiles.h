#ifndef		_MISPLACEDTILES_H_
#define		_MISPLACEDTILES_H_

#include "IHeuristic.h"
#include <map>
class MisplacedTiles : public IHeuristic
{
private:
	int _size;
	std::map<int, std::pair<int, int> > _helper;
public:
	MisplacedTiles();
	~MisplacedTiles(void);
	double getH(Node * beforeState, Node* currentState);
	void setSolution(Node *solution);
};

#endif