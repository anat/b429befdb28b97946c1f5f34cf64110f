#include "..\include\Node.h"
#include <iostream>

Node::Node() : Parent(0)
{
}

Node::Node(Node const &copy)
{
	this->Size = copy.Size;
	this->Parent = copy.Parent;
	this->State = new int*[copy.Size];
	for (int i = 0 ; i < copy.Size ; i++)
		this->State[i] = new int[copy.Size];
	for (int i = 0 ; i < copy.Size ; i++)
		for (int j = 0 ; j < copy.Size ; j++)
			this->State[i][j] =	copy.State[i][j];
	this->BlankX = copy.BlankX;
	this->G = copy.G + 1;
	this->BlankY = copy.BlankY;
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
	for (int aa = 0; aa < this->Size; aa++)
	{
		std::cout << "\t";
		for (int bb = 0; bb < this->Size; bb++)
		{
			std::cout << this->State[aa][bb] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << "--------///Node-------------------------------" << std::endl;
}