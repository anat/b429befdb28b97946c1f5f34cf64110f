#include <iostream>
#include "IHeuristic.h"
#include "Manhattan.h"
#include "MisplacedTiles.h"
#include "Parser.h"
#include "AStar.h"

int		main(int ac, char** av)
{
  //if (ac == 1)
  //  {
	char const * file;
	//file = av[1];
	//file = "../tests/niv1-3x3.taquin";
	//file = "../tests/niv2-3x3.taquin";
	//file = "../tests/niv3-3x3.taquin";
	//file = "../tests/niv4-4x4.taquin";
	//file = "../tests/niv5-3x3.taquin";
	//file = "../tests/niv6-5x5.taquin";
	//file = "../tests/niv7-6x6.taquin";
	//file = "../tests/niv8-3x3.taquin";
	//file = "../tests/niv9-4x4.taquin"; //31ms
	//file = "../tests/niv10-3x3.taquin";
	//file = "../tests/niv11-5x5.taquin";
	//file = "../tests/niv12-4x4.taquin";
	//file = "../tests/niv13-4x4.taquin";

	//file = "../tests/2_6.tq";
	//file = "../tests/3_6.tq";
	//file = "../tests/3_13.tq";
	//file = "../tests/3_21.tq";
	//file = "../tests/4_.tq";		//*
	//file = "../tests/4_31.tq";
	//file = "../tests/5_.tq";		//*
	//file = "../tests/16_1.tq";	//*
	//file = "../tests/UNS_2.tq";
	//file = "../tests/UNS_3.tq";

	Parser p(file);
	unsigned char * base = p.getInitialState();
	if (base)
	{
		IHeuristic* strategy = new MisplacedTiles();
		AStar a(p.getSize(), p.getInitialState(), strategy);
		a.run(file);
	}
	//}
 // else
 //   {
 //     std::cerr << "Please select a grid file and strategy" << std::endl 
	//	<< "Usage :" << std::endl
	//<< "taquin{.exe} Strategy Gridfile" << std::endl
	//<< "Stategies :" << std::endl
	//<< "1\tManhattan distance" << std::endl
	//<< "2\tMisplaced tiles" << std::endl;
 //   }
}
