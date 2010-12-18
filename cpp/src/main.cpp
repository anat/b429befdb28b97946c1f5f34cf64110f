#include <iostream>
#include "IHeuristic.h"
#include "Manhattan.h"
#include "MisplacedTiles.h"
#include "Euclide.h"
#include "Parser.h"
#include "OutOf.h"
#include "Homemade.h"
#include "AStar.h"

int		main(int ac, char** av)
{
	if (ac == 3 && ::atoi(av[1]) > 0 && ::atoi(av[1]) < 5)
	{
		char const * file;
		file = av[2];
		Parser p(file);
		unsigned char * base = p.getInitialState();
		if (base)
		{
			IHeuristic* strategy;
			switch (::atoi(av[1]))
			{
			case 1 :
				strategy = new Manhattan();
				break;
			case 2 :
				strategy = new Homemade();
				break;
			case 3 :
				strategy = new Euclide();
				break;
			case 4 :
				strategy = new MisplacedTiles();
				break;
			}
			
			AStar a(p.getSize(), p.getInitialState(), strategy);
			a.run(file);
		}
	}
	else
	{
		std::cerr << "Please select a grid file and strategy" << std::endl 
			<< "Usage :" << std::endl
			<< av[0] << " Strategy Gridfile" << std::endl
			<< "Stategies :" << std::endl
			<< "1\tManhattan distance" << std::endl
			<< "3\tHomemade" << std::endl
			<< "2\tEuclidean" << std::endl
			<< "4\tMisplaced tiles" << std::endl;
	}
}
