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
	{
		for (int j = 0 ; j < copy.Size ; j++)
		{
			this->State[i][j] =	copy.State[i][j];
		}
	}
}

int Node::ManhattanHeuristic(int **current, int **solution, int size)
{
	int cost = 0;
	for (int i = 0 ; i < size ; i++)
	{
		for (int j = 0 ; j < size ; j++)
		{
			// Parcours de toute les cases.
			int toFind = current[i][j];
			int k = 0;
			int l = 0;
			for (int k = 0 ; k < size ; k++)
			{
				for (int l = 0 ; l < size ; l++)
				{
					if (solution[k][l] == toFind)
					{
						cost += (k > i ? k - i : i - k);
						cost += (l > j ? l - j : j - l);
					}
				}
			}
		}
	}

	return cost;
}

bool Node::Equals(Node *node1, Node *node2)
{
	for (int i = 0 ; i < node1->Size ; i++)
		for (int j = 0 ; j < node2->Size ; j++)
			if (node1->State[i][j] != node2->State[i][j])
				return false;
	return true;
}