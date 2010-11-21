#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "GameSprite.h"
class Game
{
	 sf::RenderWindow* _main;
	sf::Font _ubuntuFont;
	std::list<GameSprite*> _sprites;
public:
	Game(void);
	~Game(void);
	void run(int size, int **initialState);
	void createSprites(int size, int **places);
};
