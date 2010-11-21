#include <iostream>
#include "Parser.h"
#include "AStar.h"
#define N 5
int		main(int ac, char** av)
{
	Parser p("niv1-3x3.taquin");
	int** base = p.getInitialState();
int size = p.getSize();

	int aa;
	int bb;
	for (aa = 0; aa < size; aa++)
	{
		for (bb = 0; bb < size; bb++)
		{
			std::cout << base[aa][bb] << "\t";
		}
		std::cout << std::endl;
	}
	if (base)
	{
		AStar a(p.getSize(), p.getInitialState());
		a.run();
	}


	//int test[3][3] = {0};
	//int size = 3;
	//int i = 1;
	//int x = 0;	
	//int y = 0;
	//int dirx = 1;
	//int diry = 0;
	//while (i >= 8)
	//{
	//	test[x][y] = i;
	//	x += dirx;
	//	y += diry;
	//	if (x == size && y == 0)
	//	{
	//		dirx = 0;
	//		diry = -1;
	//	}

	//	if (x == size && y == 0)
	//	{
	//		dirx = 0;
	//		diry = -1;
	//	}

	//}

	//int aa;
	//int bb;
	//for (aa = 0; aa < size; aa++)
	//{
	//	for (bb = 0; bb < size; bb++)
	//	{
	//		std::cout << test[aa][bb] << "\t";
	//	}
	//	std::cout << std::endl;
	//}
	system("pause");
}