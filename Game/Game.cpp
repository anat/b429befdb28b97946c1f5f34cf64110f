#include "Game.h"
#include <iostream>
#include <sstream>
Game::Game(void)
{
}

Game::~Game(void)
{
}

void Game::run(int size, int **initialState)
{
	_size = size;
	_it = Solution.begin();
	std::cout << Solution.size() << " Coups" << std::endl;
	_grid = new int*[size];
	for (int i = 0 ; i < size ; i++)
		_grid[i] = new int[size];
	_grid = initialState;

	_main = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Hello");
	if (!_ubuntuFont.LoadFromFile("../res/Ubuntu-R.ttf"))
	{
		std::cerr << "Ne peux pas charger la police ubuntu."<< std::endl;
		return;
	}

	while (_main->IsOpened())
	{
		sf::Event Event;
		while (_main->GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				_main->Close();
			if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::Right))
				next();
		}

		_main->Clear();

		show();
		_main->Display();
	}
}


void Game::show()
{
	for (int i = 0 ; i < _size ; i++)
	{
		for (int j = 0 ; j < _size ; j++)
		{
			if (_grid[j][i] != 0)
			{
				sf::String n;
				std::string s;
				std::stringstream  ssnb(s);
				ssnb << _grid[j][i];
				n.SetText(ssnb.str());
				n.SetFont(_ubuntuFont);
				n.SetSize(20);
				n.SetPosition((100 * i) + 50, (100 * j) + 50);
				_main->Draw(n);
			}
		}
	}
}

void Game::next()
{
	if (_it != Solution.end())
	{
		for (int i = 0 ; i < _size ; i++)
		{
			for (int j = 0 ; j < _size ; j++)
			{
				if (_grid[i][j] == 0)
				{
					//std::cout << "La" << std::endl;
					std::cout << "-" << (**_it) << "-" << std::endl;
					if (std::string((**_it)) == "Left")
					{
						std::cout << "iciL" << std::endl;
						_grid[i][j] = _grid[i][j + 1];
						_grid[i][j + 1] = 0;
						++_it;
						return;
					}
					if (std::string((**_it)) == "Right")
					{
						std::cout << "iciR" << std::endl;
						_grid[i][j] = _grid[i][j - 1];
						_grid[i][j - 1] = 0;
						++_it;
						return;
					}

					if (std::string((**_it)) == "Up")
					{
						std::cout << "iciU" << std::endl;
						_grid[i][j] = _grid[i + 1][j];
						_grid[i + 1][j] = 0;
						++_it;
						return;
					}
					if (std::string((**_it)) == "Down")
					{
						std::cout << "iciD" << std::endl;
						_grid[i][j] = _grid[i - 1][j];
						_grid[i - 1][j] = 0;
						++_it;
						return;
					}
				}
			}

		}

	}
}