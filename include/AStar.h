#ifndef		_ASTAR_H_
# define	_ASTAR_H_

#include <list>
#include "Node.h"
#include "IHeuristic.h"
#include "time.h"
#include <map>
#include <hash_map>
#include <iostream>

typedef const char * KeyType;

struct greater_str 
{

	//static const size_t bucket_size = 10000000; // mean bucket size that the container should try not to exceed
	//static const size_t min_buckets = (1 << 30); // minimum number of buckets, power of 2, >0

	//size_t operator() (const KeyType & s) const
	//{
	//	std::cout << "hash" << std::endl;
	//	size_t h = 5381;
	//	int i = 0;
	//	while(s[i] != 0) {
	//		int c = s[i];
	//		/* hash = hash*33 + c */
	//		h = ((h << 5) + h) + c;
	//		i++;
	//	}

	//	return h;
	//}


	size_t operator()( const KeyType & x ) const                                           
    {        

		return std::tr1::hash< KeyType >()( x );                                              
    }

	bool operator()(const KeyType & x, const KeyType & y) const {
		if ( strcmp(x, y) < 0)
		   return true;
		return false;
	}
};


class AStar
{
private:
	Node* _initialState;
	Node* _solution;
	int	_size;
	std::multimap<int, Node *> _openList2;
	//stdext::hash_map<KeyType, Node * , stdext::hash_compare<KeyType, greater_str > > _openHashMap;
	//stdext::hash_map<KeyType, Node * ,stdext::hash_compare<KeyType, greater_str > > _closedHashMap;


	stdext::hash_map<KeyType, Node * , stdext::hash_compare<KeyType, greater_str > > _globalHashMap;
	int** _matrixHelper;
	char const * _file;
	clock_t _startTime;

	IHeuristic* _heuristic;

public:
	AStar(unsigned char size, unsigned char* initialState, IHeuristic * strategy);
	void getPossibleMove(Node * n);
	~AStar(void);
	void run(char const * file);
	int getMatrixValue(int y, int x);
	Node* getSolution();
	int** fillMatrix();
	void solutionFound(Node* n);
	void findLowestInClosedList(Node * n, std::list<Node*>::iterator &);
	int getClosedListCount();
	void createNewNode(Node *parent, Node *newNode);
	void showInfo();
};

#endif
