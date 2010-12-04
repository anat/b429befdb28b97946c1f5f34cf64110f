#ifndef			_NODE_H_
# define		_NODE_H_

# include		<string>
# define		BLANK	255

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

	unsigned char* State;
	static unsigned char Size;
	Node* Parent;
	int H;
	int G;
	int F;
	TDirection Direction;
	unsigned char Blank;
	Node();
	Node(Node const &n, TDirection direction);
	static bool Equals(Node *node1, Node *node2);
	void setBlank();
	void show();
	char const * getDirByEnum();

	static inline unsigned char getX(unsigned char pos)
	{
		return (pos / Size);
	}

	static inline unsigned char getY(unsigned char pos)
	{
		return (pos % Size);
	}

	static inline unsigned char getPos(unsigned char x, unsigned char y)
	{
		return ((x * Size) + y);
	}
};
#endif
