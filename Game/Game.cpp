#include "Game.h"
#include <iostream>
#include <sstream>

Game::Game(int size, int **initialState, std::list<std::string*> & solution) : 
_main(sf::VideoMode(800, 600, 32), "\"Taquin\""),
Solution(solution), 
_animClock(0),
_size(size),
_grid(initialState),
_ubuntuFont(new sf::Font())
{
	_tileSize = size * 30;
	_from[0] = -1;
	_from[1] = -1;

	_to[0] = -1;
	_to[1] = -1;


	_it = Solution.begin();
	std::cout << Solution.size() << " Coups" << std::endl;
}


Game::~Game(void)
{
}

void Game::run()
{
	if (!_ubuntuFont->LoadFromFile("../res/Ubuntu-R.ttf"))
	{
		std::cerr << "Ne peux pas charger la police ubuntu."<< std::endl;
		return;
	}

	//sf::Clock Clock;
	while (_main.IsOpened())
	{
		//float Framerate = 1.f / Clock.GetElapsedTime();
		sf::Event Event;
		while (_main.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				_main.Close();
			if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::Right))
				next();
		}
		_main.Clear();
		showBoard();
		_main.Display();
	}
}


void Game::showBoard()
{
	for (int i = 0 ; i < _size ; i++)
	{
		for (int j = 0 ; j < _size ; j++)
		{
			if (_grid[j][i] != 0)
			{
				//if (_currentN == _grid[j][i] && _to[0] != -1)
				{
					//std::cout << "Depart:" << _from[0] << ","<< _from[1] << "    Arrive:";
					//std::cout << _to[0] << "," << _to[1] << std::endl;
					//std::cout << _main.GetFrameTime() << std::endl;
					//if (_from[0] != _to[0] && _from[1] != _to[1])
					//{
					//	std::cout << "Ici" << std::endl;
					//	showText(_grid[j][i], _from[0], _from[1]);
					//	_from[0] += 0.000000001f * _main.GetFrameTime();
					//	_from[1] += 0.000000001f * _main.GetFrameTime();
					//}
				}
				//else
				{
					showText(_grid[j][i], (100 * i) + 50, (100 * j) + 50);
				}
			}
		}
	}
}

template<typename TEXT>
void Game::showText(TEXT Textable, int x, int y)
{
	sf::String n;
	std::string s;
	std::stringstream  ssnb(s);
	ssnb << Textable;
	n.SetText(ssnb.str());
	n.SetFont(*_ubuntuFont);//sf::Font::GetDefaultFont());
	n.SetSize(20);
	n.SetPosition(x, y);
	_main.Draw(n);
}

void Game::next()
{
	if (_it != Solution.end())
	{
		//		
		for (int i = 0 ; i < _size ; i++)
		{
			for (int j = 0 ; j < _size ; j++)
			{
				if (_grid[i][j] == 0)
				{
					std::cout << "-" << (**_it) << "-" << std::endl;
					if (std::string((**_it)) == "Left")
					{
						_from[0] = (i * _tileSize) + (_tileSize / 2);
						_from[1] = ((j + 1) * _tileSize) + (_tileSize / 2);

						_to[0] = (i * _tileSize) + (_tileSize / 2);
						_to[1] = (j * _tileSize) + (_tileSize / 2) + _tileSize;

						
						
						_grid[i][j] = _grid[i][j + 1];
						_grid[i][j + 1] = 0;
						_currentN = _grid[i][j];
						++_it;
						_animClock = new sf::Clock();
						return;
					}
					if (std::string((**_it)) == "Right")
					{
						_from[0] = (i * _tileSize) + (_tileSize / 2);
						_from[1] = ((j - 1) * _tileSize) + (_tileSize / 2);

						_to[0] = (i * _tileSize) + (_tileSize / 2);
						_to[1] = (j * _tileSize) + (_tileSize / 2) - _tileSize;;


						_grid[i][j] = _grid[i][j - 1];
						_grid[i][j - 1] = 0;
						_currentN = _grid[i][j];
						++_it;

						_animClock = new sf::Clock();

						return;
					}

					if (std::string((**_it)) == "Up")
					{
						_from[0] = ((i + 1) * _tileSize) + (_tileSize / 2);
						_from[1] = (j * _tileSize) + (_tileSize / 2);

						_to[0] = (i * _tileSize) + (_tileSize / 2) + _tileSize;;
						_to[1] = (j * _tileSize) + (_tileSize / 2);

						_grid[i][j] = _grid[i + 1][j];
						_grid[i + 1][j] = 0;
						_currentN = _grid[i][j];
						++_it;
						_animClock = new sf::Clock();
						return;
					}
					if (std::string((**_it)) == "Down")
					{
						_from[0] = ((i - 1) * _tileSize) + (_tileSize / 2);
						_from[1] = (j * _tileSize) + (_tileSize / 2);

						_to[0] = (i * _tileSize) + (_tileSize / 2) - _tileSize;;
						_to[1] = (j * _tileSize) + (_tileSize / 2);

						_grid[i][j] = _grid[i - 1][j];
						_grid[i - 1][j] = 0;
						_currentN = _grid[i][j];
						++_it;
						_animClock = new sf::Clock();
						return;
					}
				}
			}

		}

	}
}