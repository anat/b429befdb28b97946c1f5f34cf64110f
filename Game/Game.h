#pragma once
#include <SFML/Graphics.hpp>
#include <list>

typedef enum Directions
{
	None,
	Up,
	Down,
	Right,
	Left
} TDirection;

class Game
{
	sf::RenderWindow _main;
	sf::Font* _ubuntuFont;
	int** _grid;
	int _size;
	std::list<std::string*>::const_iterator _it;
	sf::Clock* _animClock;
	float _from[2];
	float _to[2];
	int _tileSize;
	int _currentN;
	template <typename TEXT>
	void showText(TEXT Textable, int x, int y);
public:
	Game(int size, int **initialState, std::list<std::string *> & solution);
	~Game(void);
	void run();
	void showBoard();
	void showGrid();
	std::list<std::string*> Solution;

	void next();
};
