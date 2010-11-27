#include "AStar.h"
#include <iostream>
#include <fstream>
#include "Manhattan.h"
#include "Manhattan9.h"

//#define TRACE 1
#ifdef TRACE
std::map<std::string,clock_t> tracing;
#endif


AStar::AStar(int size, int** initialState) : 
_matrixHelper(0),
_startTime(clock())
{
	_size = size;
	Node* n = new Node();
	n->State = initialState;
	n->Size = _size;
	n->setBlank();
	n->G = 100;
	n->F = 9999;
	_initialState = n;
	_solution = getSolution();
	_heuristic = new Manhattan9(_solution);
#ifdef TRACE
	tracing["findLowestInClosedList"] = 0;
	tracing["parcours"] = 0;
	tracing["total"] = 0;
#endif
}

AStar::~AStar(void)
{
}


void AStar::run(char const * file)
{

	_file = file;
	// Add the start to the open list
	_openList.push_back(_initialState);
	getPossibleMove(_initialState);
	_closedList2[std::pair<int, int>((*_openList.begin())->BlankX, (*_openList.begin())->BlankY)].splice(
		_closedList2[std::pair<int, int>((*_openList.begin())->BlankX,(*_openList.begin())->BlankY)].begin()
		, _openList, 
		_openList.begin());

	std::list<Node*>::iterator current;
	current = _openList.begin();
	bool found = false;
	while (1)
	{
		if (_openList.size() == 0)
		{
			break;
		}

		if ((*current)->H == 0)
		{
			found = true;
			break;
		}

		// get The most interesting node
		//getBestNode(current);
		current = _openList.begin();
		// get All new possible moves
		getPossibleMove((*current));

		// Move the CostLess Node to closedList
		_closedList2[std::pair<int, int>((*current)->BlankX, (*current)->BlankY)].splice(
			_closedList2[std::pair<int, int>((*current)->BlankX,(*current)->BlankY)].begin()
			, _openList, 
			current);
	}
#ifdef TRACE
	std::cout << "Time IN findLowestInClosedList = " << tracing["findLowestInClosedList"] << std::endl;
	std::cout << "Parcouru\t" << tracing["parcours"] << std::endl;
	std::cout << "Total\t\t" << tracing["total"] << std::endl;
#endif
	if (found)
	{
		solutionFound((*current));
	}
	else
	{
		std::cout << "Solution not found" << std::endl;
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



void AStar::findLowestInClosedList(Node * n, std::list<Node*>::iterator & it)
{
#ifdef TRACE
	clock_t start = clock();
#endif
	it = _openList.begin();
	std::list<Node*>::iterator end = _openList.end();
	int i = 0;
	while (it != end && (*it)->F < n->F)
	{
		i++;
		++it;
	}
	//std::cout << "Parcours de " << (i * 100) / _openList.size() << " % " << std::endl;
#ifdef TRACE
	tracing["findLowestInClosedList"] += clock() - start;
	tracing["parcours"] += i;
	tracing["total"] += _openList.size();
#endif
}

void AStar::getPossibleMove(Node * n)
{
	if (n->BlankX != 0 && n->Direction != Up)
	{
		Node * newNode = new Node(*n);
		if (!isInClosedList(newNode))
		{
			newNode->State[n->BlankX][n->BlankY] = n->State[n->BlankX - 1][n->BlankY];
			newNode->State[n->BlankX - 1][n->BlankY] = 0;
			newNode->Parent = n;
			newNode->Direction = Down;
			newNode->BlankX = n->BlankX - 1;
			newNode->H = _heuristic->getH(n, newNode);
			newNode->F = newNode->G + newNode->H;
			std::list<Node*>::iterator it = _openList.begin();
			findLowestInClosedList(newNode, it);
			_openList.insert(it,newNode);
			//_openList.push_back(newNode);
		}
	}

	if (n->BlankX != _size - 1 && n->Direction != Down)
	{

		Node * newNode = new Node(*n);
		if (!isInClosedList(newNode))
		{
			newNode->State[n->BlankX][n->BlankY] = n->State[n->BlankX + 1][n->BlankY];
			newNode->State[n->BlankX + 1][n->BlankY] = 0;
			newNode->Parent = n;
			newNode->Direction = Up;
			newNode->BlankX = n->BlankX + 1;
			newNode->H = _heuristic->getH(n, newNode);
			newNode->F = newNode->G + newNode->H;
			std::list<Node*>::iterator it = _openList.begin();
			findLowestInClosedList(newNode, it);
			_openList.insert(it,newNode);
			//_openList.push_back(newNode);
		}
	}
	if (n->BlankY != 0  && n->Direction != Left)
	{
		Node * newNode = new Node(*n);
		if (!isInClosedList(newNode))
		{
			newNode->State[n->BlankX][n->BlankY] = n->State[n->BlankX][n->BlankY - 1];
			newNode->State[n->BlankX][n->BlankY - 1] = 0;
			newNode->Parent = n;
			newNode->Direction = Right;
			newNode->BlankY = n->BlankY - 1;
			newNode->H = _heuristic->getH(n, newNode);
			newNode->F = newNode->G + newNode->H;
			std::list<Node*>::iterator it = _openList.begin();
			findLowestInClosedList(newNode, it);
			_openList.insert(it,newNode);
			//_openList.push_back(newNode);
		}
	}
	if (n->BlankY != _size - 1 && n->Direction != Right)
	{
		Node * newNode = new Node(*n);
		if (!isInClosedList(newNode))
		{
			newNode->State[n->BlankX][n->BlankY] = n->State[n->BlankX][n->BlankY + 1];
			newNode->State[n->BlankX][n->BlankY + 1] = 0;
			newNode->Parent = n;
			newNode->Direction = Left;
			newNode->BlankY = n->BlankY + 1;
			newNode->H = _heuristic->getH(n, newNode);
			newNode->F = newNode->G + newNode->H;
			std::list<Node*>::iterator it = _openList.begin();
			findLowestInClosedList(newNode, it);
			_openList.insert(it,newNode);
			//_openList.push_back(newNode);
		}
	}
}



void AStar::solutionFound(Node* n)
{
	//found
#ifdef _WIN32
	_startTime = (clock() - _startTime);
#else
	_startTime = (time(0) - _startTime);
#endif
	int i = 0;
	//Node * n = (*it);

	std::cout << _startTime << " millisecondes" << std::endl;

	std::string outputfile(_file + std::string(".solution"));
	std::ofstream ofs(outputfile.c_str());



	std::list<const char *> solution;
	while (n->Parent != 0)
	{
		solution.push_front(n->getDirByEnum());
		n = n->Parent;
		i++;
	}

	ofs << "Moves : " << i << " Compute time : " << _startTime << " Milliseconds" << std::endl;

	std::list<const char *>::const_iterator it = solution.begin();
	std::list<const char *>::const_iterator end = solution.end();

	for (; it != end ; ++it)
	{
		ofs << (*it) << std::endl;
	}
	ofs.close();
#include <fstream>
	std::ofstream oofs("Tracing.txt", std::ios_base::app);
	oofs << _file << "\t:" << _startTime << " with " << i << "moves" << std::endl;
	oofs.close();

	std::cout << "PASSWORD FOUND in " << i << " moves" << std::endl;
	//std::cout << "[TIME] Closed list size\t\t" << _closedList.size() << std::endl;
	//std::cout << "[SIZE] Two list size\t\t" << (_closedList.size() + _openList.size()) << std::endl;
	system("pause");
	//this->showClosedList();
	exit(0);
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

void AStar::showOpenList(bool onlyH)
{
	std::cout << std::endl << "Open List :" << std::endl << std::endl;
	std::list<Node*>::iterator itopen = _openList.begin();
	std::list<Node*>::iterator endopen = _openList.end();
	while (itopen != endopen)
	{
		if (onlyH)
			std::cout << (*(itopen++))->H << std::endl;
		else
			(*(itopen++))->show();
	}
	std::cout << "End of open List" << std::endl << std::endl;
}

void AStar::getBestNode(std::list<Node*>::iterator & current)
{
	int save = 99999999;
	// Looking for CostLess Node
	std::list<Node*>::iterator it = _openList.begin();
	std::list<Node*>::iterator end = _openList.end();
	for (; it != end ; ++it)
	{
		if ((*it)->H == 0)
			solutionFound((*it));
		else if ((*it)->H < save)
		{
			current = it;
			save = (*it)->H;
			//std::cout << (*it)->F << std::endl;
		}
	}
	//std::cout << "Plus petit : " << save << std::endl;
}

void AStar::showClosedList()
{
	//std::cout << "Closed :" << std::endl;
	//std::list<Node*>::iterator itclosed = _closedList.begin();
	//std::list<Node*>::iterator endclosed = _closedList.end();
	//while (itclosed != endclosed)
	//	(*(itclosed++))->show();
}