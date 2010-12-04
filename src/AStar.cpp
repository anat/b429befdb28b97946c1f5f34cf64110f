#include "AStar.h"
#include <iostream>
#include <fstream>
#include <map>
#include "Manhattan.h"
#include "MisplacedTiles.h"

AStar::AStar(int size, int** initialState, IHeuristic * strategy) : 
_matrixHelper(0),
_startTime(clock())
{
	_size = size;
	Node* n = new Node();
	n->State = initialState;
	n->Size = _size;
	n->setBlank();

	_initialState = n;
	_solution = getSolution();
	_heuristic = strategy;
	_heuristic->setSolution(_solution);
	_initialState->H = _heuristic->getH(0, _initialState);
	_initialState->F = _initialState->G + _initialState->H;
}

AStar::~AStar(void)
{
}


void AStar::run(char const * file)
{

	_file = file;
	// Add the first node to the open list
	getPossibleMove(_initialState);
	_closedList2[std::pair<int,int>(_initialState->BlankX, _initialState->BlankY)].push_back(_initialState);

	std::multimap<int, Node*>::iterator current;

	bool found = false;
	while (1)
	{
		if (_openList2.size() == 0)
			break;
		else
			current = _openList2.begin();

		if ((*current).second->H == 0)
		{
			found = true;
			break;
		}
		getPossibleMove((*current).second);
		// Move the CostLess Node to closedList
		_closedList2[std::pair<int, int>((*current).second->BlankX, (*current).second->BlankY)].push_back((*current).second);
		_openList2.erase(current);
		
		//showInfo();
	}
	if (found)
		solutionFound((*current).second);
	else
		std::cout << "Solution not found" << std::endl;
}

void AStar::createNewNode(Node * parent, Node * newNode)
{
	if (!isInOpenList(newNode) && !isInClosedList(newNode))
	{
		newNode->Parent = parent;
		newNode->H = _heuristic->getH(parent, newNode);
		newNode->F = newNode->G + newNode->H;
		_openList2.insert(std::pair<int, Node *>(newNode->F, newNode));
	}
}

void AStar::getPossibleMove(Node * n)
{

	if (n->BlankX != 0 && n->Direction != Up)
	{
		Node * newNode = new Node(*n, Down);
		createNewNode(n, newNode);
	}

	if (n->BlankX != _size - 1 && n->Direction != Down)
	{
		Node * newNode = new Node(*n, Up);
		createNewNode(n, newNode);
	}
	if (n->BlankY != 0  && n->Direction != Left)
	{
		Node * newNode = new Node(*n, Right);
		createNewNode(n, newNode);
	}
	if (n->BlankY != _size - 1 && n->Direction != Right)
	{
		Node * newNode = new Node(*n, Left);
		createNewNode(n, newNode);
	}
}

bool AStar::isInClosedList(Node* n)
{
	if (_closedList2[std::pair<int, int>(n->BlankX, n->BlankY)].size() == 0)
		return false;

	std::list<Node*>::iterator itclosed = _closedList2[std::pair<int, int>(n->BlankX, n->BlankY)].begin();
	std::list<Node*>::iterator endclosed = _closedList2[std::pair<int, int>(n->BlankX, n->BlankY)].end();
	while (itclosed != endclosed && Node::Equals((*itclosed), n) == false)
		itclosed++;

	if (itclosed != endclosed)
		return true;
	return false;
}

bool AStar::isInOpenList(Node * n)
{
	std::multimap<int, Node*>::iterator it;
	std::pair<std::multimap<int, Node*>::iterator, std::multimap<int, Node*>::iterator> range;
	range = _openList2.equal_range(n->F);
	for (it = range.first; it != range.second; ++it)
		if (Node::Equals(n, (*it).second))
			return true;
	return false;
}

void AStar::solutionFound(Node* n)
{
	_startTime = (clock() - _startTime);
	int i = 0;
	std::string outputfile(_file + std::string(".solution"));
	std::ofstream ofs(outputfile.c_str());
	std::list<const char *> solution;
	while (n->Parent != 0)
	{
		solution.push_front(n->getDirByEnum());
		n = n->Parent;
		i++;
	}

	ofs << "time=" << (double)_startTime / CLOCKS_PER_SEC <<  
			"&moves=" << i  << 
			"&complexity_in_time=" << 
			"&complexity_in_size" << std::endl;

	std::list<const char *>::const_iterator it = solution.begin();
	std::list<const char *>::const_iterator end = solution.end();

	for (; it != end ; ++it)
	{
		ofs << (*it) << std::endl;
	}
	ofs.close();
	std::cout << "[COMPUTE TIME]\t\t" << (double)_startTime / CLOCKS_PER_SEC << " sec" << std::endl;
	std::cout << "[MOVES]\t\t\t" << i << std::endl;
	std::cout << "[TIME] Closed list size\t" << getClosedListCount() << std::endl;
	std::cout << "[SIZE] Two list size\t" << (getClosedListCount() + _openList2.size()) << std::endl;
}

Node* AStar::getSolution()
{
	int** mat = fillMatrix();
	int** sol = new int*[_size];

	for (int i = 0 ; i < _size ; i++)
		sol[i] = new int[_size];
	for (int i = 0; i < _size ; i++)
		for (int j = 0; j < _size ; j++) 
			sol[i][j] = mat[i][j];

	Node * n = new Node();
	n->Size = _size;
	n->State = sol;
	for (int i = 0 ; i < _size ; i++)
		for (int j = 0 ; j < _size ; j++)
			if (n->State[i][j] == _size * _size)
				n->State[i][j] = BLANK;
	return n;
}


int** AStar::fillMatrix()
{
	//alloc
	int** matrix = new int*[_size];
	for (int i = 0 ; i < _size ; i++)
		matrix[i] = new int[_size];
	//fill
	for (int i = 0; i < _size ; i++)
	{
		for (int j = 0; j < _size ; j++) 
		{
			matrix[i][j] = getMatrixValue(i, j) + 1;
		}
	}
	return matrix;
}

int AStar::getMatrixValue(int y, int x)
{
	int p = 4 * _size;

	if (x >= y)
	{
		if (y < _size - x) 
			return x + y * p - ((1 + 4 * y) * y);
		else
			return y + _size + (_size - x - 1) * p - (1 + (3 + 4 * (_size - x - 1)) * (_size - x - 1));
	}
	else 
	{
		if (y < _size - x) 
			return (_size - y - 4) + _size  + 2 * _size + x * p - ((7 + 4 * x) * x);
		else 
			return (_size - x - 3) + _size + _size + (_size - y - 1) * p - ((5 + 4 * (_size - y - 1))*(_size - y - 1));
	}
}

int AStar::getClosedListCount()
{
	int count = 0;
	std::map<std::pair<int, int>, std::list<Node*> >::iterator it = _closedList2.begin();
	std::map<std::pair<int, int>, std::list<Node*> >::iterator end = _closedList2.end();
	for (; it != end; ++it)
		count += (*it).second.size();
	return count;
}

void AStar::showInfo()
{
	if (getClosedListCount() % 5000 == 0)
	{
		std::cout << "Analysed : " << getClosedListCount() << std::endl;
		std::cout << "Temps courant : " << clock() - _startTime << std::endl;
	}
}
