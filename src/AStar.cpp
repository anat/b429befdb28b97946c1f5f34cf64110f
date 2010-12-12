#include "AStar.h"
#include <iostream>
#include <fstream>
#include <map>
#include "Manhattan.h"
#include "MisplacedTiles.h"


AStar::AStar(unsigned char size, unsigned char* initialState, IHeuristic * strategy) : 
_matrixHelper(0),
_startTime(clock())
{
	Node::Size = size;
	_size = size;
	_initialState = new Node();
	_initialState->State = initialState;
	_initialState->setBlank();

	_solution = getSolution();
	_heuristic = strategy;
	_heuristic->setSolution(_solution);
	_initialState->H = _heuristic->getH(0, _initialState);
	_initialState->F = _initialState->G + _initialState->H;
	_initialState->show();
}

AStar::~AStar(void)
{
}


void AStar::run(char const * file)
{
	_file = file;
	// Add the first node to the open list
	getPossibleMove(_initialState);
	_globalHashMap[(const char *)_initialState->State] = _initialState;

	std::multimap<int, Node*>::iterator current;

	bool found = false;
	while (1)
	{
		if (_openList2.size() == 0)
			break;
		current = _openList2.begin();

		if ((*current).second->H == 0)
		{
			found = true;
			break;
		}
		getPossibleMove((*current).second);
		_openList2.erase(current);
		//Node* n = _globalHashMap[(const char *)current->second->State];
		//_globalHashMap[(const char *)current->second->State] = 0;
		//delete n;
	}
	if (found)
		solutionFound((*current).second);
	else
		solutionFound(0);

}

void AStar::createNewNode(Node * parent, Node * newNode)
{
	if (_globalHashMap.find((const char *)newNode->State) == _globalHashMap.end())
	{
		newNode->Parent = parent;
		newNode->H = _heuristic->getH(parent, newNode);
		newNode->F = newNode->G + newNode->H;
		_openList2.insert(std::pair<int, Node *>(newNode->F, newNode));
		_globalHashMap[(const char *)newNode->State] = newNode;
	}
	else
	{
		delete newNode;
	}
}

void AStar::getPossibleMove(Node * n)
{
	if (Node::getX(n->Blank) != 0 && n->Direction != Up)
	{
		Node * newNode = new Node(*n, Down);
		createNewNode(n, newNode);
	}

	if (Node::getX(n->Blank) != _size - 1 && n->Direction != Down)
	{
		Node * newNode = new Node(*n, Up);
		createNewNode(n, newNode);
	}
	if (Node::getY(n->Blank) != 0  && n->Direction != Left)
	{
		Node * newNode = new Node(*n, Right);
		createNewNode(n, newNode);
	}
	if (Node::getY(n->Blank) != _size - 1 && n->Direction != Right)
	{
		Node * newNode = new Node(*n, Left);
		createNewNode(n, newNode);
	}
}

void AStar::solutionFound(Node* n)
{
	_startTime = (clock() - _startTime);
	std::cout << "[COMPUTE TIME]\t\t" << (double)_startTime / CLOCKS_PER_SEC << " sec" << std::endl;
	int i = 0;
	if (n != 0)
	{
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
	}
	if (n == 0)
		std::cout << "Solution not found" << std::endl;
	else
		std::cout << "[MOVES]\t\t\t" << i << std::endl;
	std::cout << "[TIME] Closed list size\t" << _globalHashMap.size() -  _openList2.size() << std::endl;
	std::cout << "[SIZE] Two list size\t" << _globalHashMap.size() << std::endl;
}

Node* AStar::getSolution()
{
	int** mat = fillMatrix();
	unsigned char* sol = new unsigned char[(_size * _size) + 1];
	int z = 0;
	for (int i = 0; i < _size ; i++)
	{
		for (int j = 0; j < _size ; j++)
		{
			sol[z] = mat[i][j];
			z++;
		}
	}

	Node * n = new Node();
	n->Size = _size;
	n->State = sol;
	for (int i = 0 ; i < (_size *_size) ; i++)
			if (n->State[i] == _size * _size)
				n->State[i] = BLANK;
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

void AStar::showInfo()
{
	if (_globalHashMap.size() % 50000 == 0)
	{
		std::cout << "Open List :" << _openList2.size() << std::endl;
		std::cout << "Closed List : " << _globalHashMap.size() -  _openList2.size() << std::endl;
		std::cout << "Temps courant : " << clock() - _startTime << std::endl;
	}
}