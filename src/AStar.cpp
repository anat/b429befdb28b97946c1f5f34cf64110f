#include "AStar.h"
#include <iostream>

AStar::AStar(int size, int** initialState) : _matrixHelper(0), _solution(0)
{
	_size = size;
	Node* n = new Node();
	n->State = initialState;
	n->Size = size;
	_initialState = n;
	_solution = getSolution();
	showNode(_solution);
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

	while (!isInClosedList(current))
	{
		std::cout << "Taille de la openList " << std::dec <<  _openList.size() << std::endl;
		std::cout << "Taille de la closedList " << std::dec <<  _closedList.size() << std::endl;

		if (_openList.size() == 0)
		{
			std::cout << "No solution" << std::endl;
		}
		else
		{
			// get The most interesting node
			getBestNode(current);
			// get All new possible moves
			getPossibleMove((*current));
			// Move the CostLess Node to closedList
			_closedList.splice(_closedList.begin(), _openList, current);
			// Ici on a baisé le pointeur 
			current = _closedList.begin();
		}
	}
}

bool AStar::isInClosedList(std::list<Node*>::iterator check)
{
	if (_closedList.size() == 0)
		return false;
	std::list<Node*>::iterator itclosed = _closedList.begin();
	std::list<Node*>::iterator endclosed = _closedList.end();
	while (itclosed != endclosed && Node::Equals((*check),_solution) == false)
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
			std::cout << "FOUND en " << _closedList.size() << " coups" << std::endl;

			std::cout << "closed :" << std::endl;
			std::list<Node*>::iterator itclosed = _closedList.begin();
			std::list<Node*>::iterator endclosed = _closedList.end();
			while (itclosed != endclosed)
				showNode(*(itclosed++));

			exit(0);
		}
		else if ((*it)->H < save)
		{

			current = it;
			save = (*it)->H;
		}
	}
	std::cout << "Plus petit : " << save << std::endl;
}



void AStar::getPossibleMove(Node * n)
{
	for (int i = 0 ; i < _size ; i++)
	{
		for (int j = 0 ; j < _size ; j++)
		{
			if (n->State[i][j] == BLANK)
			{
				if (i != 0)
				{
					Node * newNode = new Node(*n);
					newNode->State[i][j] = n->State[i - 1][j];
					newNode->State[i - 1][j] = 0;
					newNode->Parent = n;

					newNode->H = Node::ManhattanHeuristic(newNode->State,_solution->State, _size);
					_openList.push_back(newNode);
				}
				if (i != _size - 1)
				{
					Node * newNode = new Node(*n);
					newNode->State[i][j] = n->State[i + 1][j];
					newNode->State[i + 1][j] = 0;
					newNode->Parent = n;

					newNode->H = Node::ManhattanHeuristic(newNode->State,_solution->State, _size);
					_openList.push_back(newNode);
				}
				if (j != 0)
				{
					Node * newNode = new Node(*n);
					newNode->State[i][j] = n->State[i][j - 1];
					newNode->State[i][j - 1] = 0;
					newNode->Parent = n;

					newNode->H = Node::ManhattanHeuristic(newNode->State,_solution->State, _size);
					_openList.push_back(newNode);
				}
				if (j != _size - 1)
				{
					Node * newNode = new Node(*n);
					newNode->State[i][j] = n->State[i][j + 1];
					newNode->State[i][j + 1] = 0;
					newNode->Parent = n;

					newNode->H = Node::ManhattanHeuristic(newNode->State,_solution->State, _size);
					_openList.push_back(newNode);
				}
				return;
			}
		}
	}
}


void AStar::showNode(Node *n)
{
	std::cout <<"\taddr : " << std::hex << n << "  -  parent : " << std::hex << n->Parent << std::endl;
	for (int aa = 0; aa < n->Size; aa++)
	{
		std::cout << "\t";
		for (int bb = 0; bb < n->Size; bb++)
		{
			std::cout << n->State[aa][bb] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
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