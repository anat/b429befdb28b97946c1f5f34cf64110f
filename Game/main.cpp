
#include "Game.h"

#include "Parser.h"

int main(int ac, char** av)
{

	Parser p("../niv8-3x3.taquin");
	std::list<std::string*> solution;
	p.getSolution(solution);
	Game g(p.getSize(), p.getInitialState(), solution);
	g.run();
}
