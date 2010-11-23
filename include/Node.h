#ifndef			_NODE_H_
# define		_NODE_H_

# include		<string>
# define		BLANK	0

typedef enum Directions
{
	None,
	Up,
	Down,
	Right,
	Left
} TDirection;

class Node
{
public:

	int** State;
	int Size;
	Node* Parent;
	int H;
	int G;
	TDirection Direction;
	int BlankX;
	int BlankY;
	Node();
	Node(Node const &);
	static bool Node::Equals(Node *node1, Node *node2);
	void setBlank();
	void show();
	char const * getDirByEnum();
};
#endif