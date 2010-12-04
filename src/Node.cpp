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
	this->Direction = dir;
	this->State = new unsigned char[(Node::Size * Node::Size) + 1];
	this->State[Node::Size * Node::Size] = 0;

	for (int i = 0 ; i <= Node::Size * Node::Size ; i++)
	{
		this->State[i] = copy.State[i];
	}

	this->Blank = (dir == Down ? copy.Blank - Node::Size : (dir == Up ? copy.Blank + Node::Size : (dir == Right ? getPos(getX(copy.Blank), getY(copy.Blank) - 1) :	getPos(getX(copy.Blank), getY(copy.Blank) + 1)	)	)		);
	if (this->Blank > Size * Size)
	{
		exit(0);
	}
	this->State[copy.Blank] = copy.State[this->Blank];
	this->State[this->Blank] = BLANK;
	this->G = copy.G + 1;
}

bool Node::Equals(Node *node1, Node *node2)
{
	for (int i = 0 ; i < Node::Size * Node::Size ; i++)
		if (node1->State[i] != node2->State[i])
			return false;
	return true;
}

void Node::setBlank()
{
	for (int i = 0 ; i < Node::Size * Node::Size ; i++)
	{
			if (this->State[i] == BLANK)
			{
				this->Blank = i;
				return;
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
	std::cout << "\tdir = " << getDirByEnum() << std::endl << "\tBlank =" << std::dec << (int)Blank << std::endl;
	std::cout << "\tG=" << std::dec << G << "\rH=" << std::dec << H << std::endl;
	for (int aa = 0; aa < (Node::Size * Node::Size); aa++)
	{
		if (aa != 0)
			if (getX(aa) != getX(aa - 1))
				std::cout << std::endl;
		std::cout << std::dec << (int)this->State[aa] << "\t";
	}
	std::cout << std::endl;
	std::cout << "--------///Node-------------------------------" << std::endl;
}
