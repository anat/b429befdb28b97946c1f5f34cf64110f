#include "Game.h"
#include <iostream>

Game::Game(void)
{
}

Game::~Game(void)
{
}

void Game::run(int size, int **initialState)
{
	_main = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "Hello");
	if (!_ubuntuFont.LoadFromFile("../res/Ubuntu-R.ttf"))
	{
		std::cerr << "Ne peux pas charger la police ubuntu."<< std::endl;
		return;
	}

	// Ex�cution de la boucle principale
	while (_main->IsOpened())
	{
		// Traitement des �v�nements
		sf::Event Event;
		while (_main->GetEvent(Event))
		{
			// Fen�tre ferm�e : on quitte
			if (Event.Type == sf::Event::Closed)
				_main->Close();
		}

		// Efface l'�cran (remplissage avec du noir)
		_main->Clear();

		// Affichage du contenu de la fen�tre � l'�cran
		_main->Display();
	}
}

void Game::createSprites(int size, int **places)
{
for (int i = 0 ; i < size ; i++)
{
for (int j = 0 ; j < size ; j++)
{
	std::string s;
	//places[i][j] >> s;
	sf::Sprite* sprite = new sf::Sprite();

	sprite->SetColor(sf::Color(0, 255, 255, 128));
	//_sprites.push_back(
}
}


}