#include <iostream>
#include "Parser.h"

int		main(int ac, char** av)
{
	Parser p("niv1-3x3.taquin");
	int** base = p.getInitialState();
	
	if (base)
	{
		std::cout << "Good \"Taquin\" File of " << p.getSize() << std::endl;
	}

}