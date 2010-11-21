#pragma once

class Node
{
	public:
	int** State;
	int Size;
	Node* Parent;
	int H;
	Node();
	Node(Node const &);
	static int ManhattanHeuristic(int **current, int **solution, int size);
	static bool Node::Equals(Node *node1, Node *node2);
};
