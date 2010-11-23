#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "GameSprite.h"
class Game
{
	 sf::RenderWindow* _main;
	sf::Font _ubuntuFont;
	int** _grid;
	int _size;
	std::list<std::string*>::const_iterator _it;
public:
	Game(void);
	~Game(void);
	void run(int size, int **initialState);
	void show();
	std::list<std::string*> Solution;

	void next();
};
