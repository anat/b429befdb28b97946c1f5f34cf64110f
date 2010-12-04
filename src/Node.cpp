#include "Node.h"
#include <iostream>

// Constructor for the first node
Node::Node() : Parent(0)
{
	this->G = 0;
	this->Direction = None;
	this->F = 0;
}

// Constructor for other's nodes
Node::Node(Node const &copy, TDirection dir)
{
	this->Size = copy.Size;
	this->Direction = dir;
	this->State = new int*[copy.Size];

	for (int i = 0 ; i < copy.Size ; i++)
	{
		this->State[i] = new int[copy.Size];
		for (int j = 0 ; j < copy.Size ; j++)
			this->State[i][j] =	copy.State[i][j];
	}

	this->BlankX = (dir == Down ? copy.BlankX - 1 :		(dir == Up ? copy.BlankX + 1 : copy.BlankX)		);
	this->BlankY = (dir == Right ? copy.BlankY - 1 :	(dir == Left ? copy.BlankY + 1 : copy.BlankY)	);

	//std::cout << "From " <<  copy.State[this->BlankX][this->BlankY] << " To " << this->State[copy.BlankX][copy.BlankX] << std::endl;
	this->State[copy.BlankX][copy.BlankY] = copy.State[this->BlankX][this->BlankY];
	this->State[this->BlankX][this->BlankY] = 0;
	this->G = copy.G + 1;
}

bool Node::Equals(Node *node1, Node *node2)
{
	for (int i = 0 ; i < node1->Size ; i++)
		for (int j = 0 ; j < node2->Size ; j++)
			if (node1->State[i][j] != node2->State[i][j])
				return false;
	return true;
}

void Node::setBlank()
{
	for (int i = 0 ; i < Size ; i++)
	{
		for (int j = 0 ; j < Size ; j++)
		{
			if (this->State[i][j] == BLANK)
			{
				this->BlankX = i;
				this->BlankY = j;
				return;
			}
		}
	}
}

char const * Node::getDirByEnum()
{
	if (Direction == Left)
		return "Left";
	else if (Direction == Right)
		return "Right";
	else if (Direction == Up)
		return "Up";
	else if (Direction == Down)
		return "Down";
	return "None";
}

void Node::show()
{
	std::cout << "-----------Node-------------------------------" << std::endl;
	std::cout << "\taddr : " << std::hex << this << "  -  parent : " << std::hex << this->Parent << std::endl;
	std::cout << "\tdir = " << getDirByEnum() << std::endl << "\tBlank x=" << BlankX << " y=" << BlankY << std::endl;
	std::cout << "\tG=" << G << "\rH=" << H << std::endl;
	for (int aa = 0; aa < this->Size; aa++)
	{
		std::cout << "\t";
		for (int bb = 0; bb < this->Size; bb++)
		{
			std::cout << std::dec << this->State[aa][bb] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "--------///Node-------------------------------" << std::endl;
}
