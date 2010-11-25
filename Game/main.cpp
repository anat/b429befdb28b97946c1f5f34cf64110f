
#include "Game.h"

#include "Parser.h"

int main(int ac, char** av)
{
	Game g;
	Parser p("../niv8-3x3.taquin");
	int ** initialState = 0;
	p.getSolution(g.Solution);
	g.run(p.getSize(), p.getInitialState());
}
