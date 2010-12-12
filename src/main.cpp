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
	//file = "niv1-3x3.taquin";
	//file = "niv2-3x3.taquin";
	//file = "niv3-3x3.taquin";
	//file = "niv4-4x4.taquin";
	//file = "niv5-3x3.taquin";
	//file = "niv6-5x5.taquin";
	//file = "niv7-6x6.taquin";
	//file = "niv8-3x3.taquin";
	//file = "niv9-4x4.taquin"; //31ms
	//file = "niv10-3x3.taquin";
	//file = "niv11-5x5.taquin";
	//file = "niv12-4x4.taquin";
	file = "niv13-4x4.taquin";
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
 //     std::cerr << "Please select a map file" << std::endl;
 //   }
}
