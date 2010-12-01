#include "AStar.h"
#include <iostream>
#include <fstream>
#include <map>
#include "Manhattan.h"
#include "Manhattan9.h"
#include "MisplacedTiles.h"

//#define TRACE 1
#ifdef TRACE
std::map<std::string,clock_t> tracing;
#endif

clock_t start = 0;

AStar::AStar(int size, int** initialState) : 
_matrixHelper(0),
_startTime(clock())
{
	_size = size;
	Node* n = new Node();
	n->State = initialState;
	n->Size = _size;
	n->setBlank();
	n->G = 0;
	_initialState = n;
	_solution = getSolution();
	_heuristic = new Manhattan9(_solution);
	n->H = _heuristic->getH(0, n);
		n->F = n->G + n->H;
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
	getPossibleMove(_initialState);
	_closedList2[std::pair<int,int>(_initialState->BlankX, _initialState->BlankY)].push_back(_initialState);
	
	std::multimap<int, Node*>::iterator current;
	
	bool found = false;
	clock_t total = 0;
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
	//start = clock();
	//	if (getClosedListCount() % 5000 == 0)
	//	{
	//		std::cout << "Analysed : " << getClosedListCount() << std::endl;
	//		std::cout << "Temps passe : " << total << std::endl;
	//		std::cout << "Temps courant : " << clock() - _startTime << std::endl;
	//		start = 0;
	//		total = clock();
	//	}
	//total += (clock() - start);
		getPossibleMove((*current).second);
		// Move the CostLess Node to closedList
		_closedList2[std::pair<int, int>((*current).second->BlankX, (*current).second->BlankY)].push_back((*current).second);
		_openList2.erase(current);
	}
#ifdef TRACE
	std::cout << "Time IN findLowestInClosedList = " << tracing["findLowestInClosedList"] << std::endl;
	std::cout << "Parcouru\t" << tracing["parcours"] << std::endl;
	std::cout << "Total\t\t" << tracing["total"] << std::endl;
#endif
	if (found)
	{
		solutionFound((*current).second);
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

bool AStar::isInOpenList(Node * n)
{
	clock_t start = clock();
	std::multimap<int, Node*>::iterator it;
	std::pair<std::multimap<int, Node*>::iterator, std::multimap<int, Node*>::iterator> range;
	range = _openList2.equal_range(n->F);
	for (it = range.first; it != range.second; ++it)
		if (Node::Equals(n, (*it).second))
		{
			return true;
		}
		if (getClosedListCount() > 150000)
			std::cout << "Time in isOpenList" << clock() - start << std::endl;
	return false;
}

void AStar::createNewNode(Node * parent, Node * newNode)
{
	newNode->Parent = parent;
	newNode->H = _heuristic->getH(parent, newNode);
	newNode->F = newNode->G + newNode->F;
	_openList2.insert(std::pair<int, Node *>(newNode->H, newNode));
}

void AStar::getPossibleMove(Node * n)
{

	if (n->BlankX != 0 && n->Direction != Up)
	{
		Node * newNode = new Node(*n);
		if (!isInClosedList(newNode) && !isInOpenList(newNode))
		{
			newNode->State[n->BlankX][n->BlankY] = n->State[n->BlankX - 1][n->BlankY];
			newNode->State[n->BlankX - 1][n->BlankY] = 0;
			newNode->Direction = Down;
			newNode->BlankX = n->BlankX - 1;
			createNewNode(n, newNode);
		}
	}

	if (n->BlankX != _size - 1 && n->Direction != Down)
	{

		Node * newNode = new Node(*n);
		if (!isInClosedList(newNode) && !isInOpenList(newNode))
		{
			newNode->State[n->BlankX][n->BlankY] = n->State[n->BlankX + 1][n->BlankY];
			newNode->State[n->BlankX + 1][n->BlankY] = 0;
			newNode->Direction = Up;
			newNode->BlankX = n->BlankX + 1;
			createNewNode(n, newNode);
		}
	}
	if (n->BlankY != 0  && n->Direction != Left)
	{
		Node * newNode = new Node(*n);
		if (!isInClosedList(newNode) && !isInOpenList(newNode))
		{
			newNode->State[n->BlankX][n->BlankY] = n->State[n->BlankX][n->BlankY - 1];
			newNode->State[n->BlankX][n->BlankY - 1] = 0;
			newNode->Direction = Right;
			newNode->BlankY = n->BlankY - 1;
			createNewNode(n, newNode);
		}
	}
	if (n->BlankY != _size - 1 && n->Direction != Right)
	{
		Node * newNode = new Node(*n);
		if (!isInClosedList(newNode) && !isInOpenList(newNode))
		{
			newNode->State[n->BlankX][n->BlankY] = n->State[n->BlankX][n->BlankY + 1];
			newNode->State[n->BlankX][n->BlankY + 1] = 0;
			newNode->Direction = Left;
			newNode->BlankY = n->BlankY + 1;
			createNewNode(n, newNode);
		}
	}

}



void AStar::solutionFound(Node* n)
{
	//found
	_startTime = (clock() - _startTime);
	int i = 0;
	//Node * n = (*it);

	std::string outputfile(_file + std::string(".solution"));
	std::ofstream ofs(outputfile.c_str());



	std::list<const char *> solution;
	while (n->Parent != 0)
	{
		solution.push_front(n->getDirByEnum());
		n = n->Parent;
		i++;
	}

	std::cout << "[MOVES] : " << i << std::endl;
	ofs << "[MOVES] : " << i << std::endl;
	std::list<const char *>::const_iterator it = solution.begin();
	std::list<const char *>::const_iterator end = solution.end();

	for (; it != end ; ++it)
	{
		ofs << (*it) << std::endl;
	}
	ofs.close();
	std::cout << "[TIME] Closed list size\t\t" << getClosedListCount() << std::endl;
	std::cout << "[SIZE] Two list size\t\t" << (getClosedListCount() + _openList2.size()) << std::endl;
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
	//std::cout << std::endl << "Open List :" << std::endl << std::endl;
	//std::list<Node*>::iterator itopen = _openList.begin();
	//std::list<Node*>::iterator endopen = _openList.end();
	//while (itopen != endopen)
	//{
	//	if (onlyH)
	//		std::cout << (*(itopen++))->H << std::endl;
	//	else
	//		(*(itopen++))->show();
	//}
	//std::cout << "End of open List" << std::endl << std::endl;
}

void AStar::getBestNode(std::list<Node*>::iterator & current)
{
	//int save = 99999999;
	//// Looking for CostLess Node
	//std::list<Node*>::iterator it = _openList.begin();
	//std::list<Node*>::iterator end = _openList.end();
	//for (; it != end ; ++it)
	//{
	//	if ((*it)->H == 0)
	//		solutionFound((*it));
	//	else if ((*it)->H < save)
	//	{
	//		current = it;
	//		save = (*it)->H;
	//		//std::cout << (*it)->F << std::endl;
	//	}
	//}
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

int AStar::getClosedListCount()
{
	int count = 0;
	std::map<std::pair<int, int>, std::list<Node*> >::iterator it = _closedList2.begin();
	std::map<std::pair<int, int>, std::list<Node*> >::iterator end = _closedList2.end();
	for (; it != end; ++it)
		count += (*it).second.size();
	return count;
}

int AStar::getOpenListCount()
{
  /*
	int count = 0;
	std::multimap<int, Node *>::iterator it = _openList2.begin();
	std::multimap<int, Node *>::iterator end = _openList2.end();
	for (; it != end; ++it)
	  count += _openList2.size((*it));
	return count;
  */
  return 0;
}

