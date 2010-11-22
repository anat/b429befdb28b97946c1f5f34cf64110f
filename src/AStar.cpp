#include "AStar.h"
#include <iostream>
#include <time.h>

AStar::AStar(int size, int** initialState) : _matrixHelper(0), _solution(0)
{
	_startTime = time(0);
	_size = size;
	Node* n = new Node();
	n->State = initialState;
	n->Size = size;
	n->setBlank();
	_initialState = n;
	_solution = getSolution();
	_heuristic = new Manhattan(_solution);
	//_solution->show();
}

AStar::~AStar(void)
{
}


void AStar::run()
{
	// Add the start to the open list
	_openList.push_back(_initialState);
	getPossibleMove(_initialState);
	_closedList.splice(_closedList.begin(), _openList, _openList.begin());


	std::list<Node*>::iterator current;
	current = _openList.begin();
	while (1)
	{
		//if (_openList.size() % 1000 == 0)
		//std::cout << "Taille de la openList " << std::dec <<  _openList.size() << std::endl;

		//if (_closedList.size() % 1000 == 0)
		//std::cout << "Taille de la closedList " << std::dec <<  _closedList.size() << std::endl;

		//if (_openList.size() == 0)
		//{
		//	std::cout << "No solution" << std::endl;
		//}
		//else
		//{
		// get The most interesting node
		getBestNode(current);
		// get All new possible moves
		getPossibleMove((*current));
		// Move the CostLess Node to closedList
		_closedList.splice(_closedList.begin(), _openList, current);
		//}
	}
}

bool AStar::isInClosedList(Node* n)
{
	if (_closedList.size() == 0)
		return false;
	std::list<Node*>::iterator itclosed = _closedList.begin();
	std::list<Node*>::iterator endclosed = _closedList.end();
	while (itclosed != endclosed && Node::Equals((*itclosed), n) == false)
		itclosed++;
	if (itclosed != endclosed)
		return true;
	return false;
}

void AStar::getBestNode(std::list<Node*>::iterator & current)
{
	int save = 9999;
	// Looking for CostLess Node
	std::list<Node*>::iterator it = _openList.begin();
	std::list<Node*>::iterator end = _openList.end();
	for (; it != end ; ++it)
	{
		if ((*it)->H == 0)
		{
			int i = 0;
			Node * n = (*it);
			std::cout << (time(0) - _startTime) << " secondes" << std::endl;
			while (n->Parent != 0)
			{
				std::cout << n->getDirByEnum() << std::endl;
				n = n->Parent;
				i++;
			}
			std::cout << "FOUND en " << i << " coups" << std::endl;
			system("pause");
			this->showClosedList();
			exit(0);
		}
		else if ((*it)->H < save)
		{

			current = it;
			save = (*it)->H;
		}
	}
	//std::cout << "Plus petit : " << save << std::endl;
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
			newNode->H = _heuristic->getH(newNode);
			_openList.push_back(newNode);
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
			newNode->H = _heuristic->getH(newNode);
			_openList.push_back(newNode);
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
			newNode->H = _heuristic->getH(newNode);
			_openList.push_back(newNode);
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
			newNode->H = _heuristic->getH(newNode);
			_openList.push_back(newNode);
		}
	}
	return;
}

void AStar::showOpenList()
{
	std::cout << "Open :" << std::endl;
	std::list<Node*>::iterator itopen = _openList.begin();
	std::list<Node*>::iterator endopen = _openList.end();
	while (itopen != endopen)
		(*(itopen++))->show();
}

void AStar::showClosedList()
{
	std::cout << "Closed :" << std::endl;
	std::list<Node*>::iterator itclosed = _closedList.begin();
	std::list<Node*>::iterator endclosed = _closedList.end();
	while (itclosed != endclosed)
		(*(itclosed++))->show();
}


Node* AStar::getSolution()
{

	if (_solution)
		return _solution;

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