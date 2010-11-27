#include <iostream>
#include "Parser.h"
#include "AStar.h"

int		main(int ac, char** av)
{
	char const * file;
	
	//file = "niv1-3x3.taquin";
	//file = "niv2-3x3.taquin";
	//file = "niv3-3x3.taquin";
	//file = "niv4-4x4.taquin";
	//file = "niv5-3x3.taquin";
	//file = "niv6-5x5.taquin";
	//file = "niv7-6x6.taquin";
	//file = "niv8-3x3.taquin";
	file = "niv9-4x4.taquin"; //31ms
	//file = "niv10-3x3.taquin";
	Parser p(file);
	int** base = p.getInitialState();
	int size = p.getSize();
	if (base)
	{
		AStar a(p.getSize(), p.getInitialState());
		a.run(file);
	}
	system("pause");
}