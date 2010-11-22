#include <iostream>
#include "Parser.h"
#include "AStar.h"




int		main(int ac, char** av)
{
	Parser p("niv1-3x3.taquin");
	//Parser p("niv2-3x3.taquin");
	//Parser p("niv3-3x3.taquin");
	//Parser p("niv4-4x4.taquin");


	int** base = p.getInitialState();
	int size = p.getSize();
	if (base)
	{
		AStar a(p.getSize(), p.getInitialState());
		a.run();
	}
	system("pause");
}