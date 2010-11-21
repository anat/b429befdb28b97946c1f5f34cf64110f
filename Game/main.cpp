
#include "Game.h"

#include "Parser.h"

int main(int ac, char** av)
{
	Game g;
	Parser p("../niv1-3x3.taquin");
	int ** initialState = 0;
	g.run(p.getSize(), p.getInitialState());
}

//#include<stdio.h>
//#include<stdlib.h>
//
//int** allocMatrix (int w, int h) {
//int** m = (int**)malloc(h * sizeof(int*));
//for (int i=0; i<h; i++) 
//	m[i] = (int*)malloc(w * sizeof(int));
//return m;
//}
//
//void freeMatrix (int** m, int w, int h) {
//for (int i=0; i<h; i++) free(m[i]);
//free(m);
//}
//
//int getMatrixValue (int y, int x, int w, int h) {
//int p = 2*h + 2*w;
//if (x>=y) {
//if (y<w-x) return x + y*p - ((1+4*y)*y);
//else return y + w + (w-x-1)*p - (1+(3+4*(w-x-1))*(w-x-1));
//}
//else {
//if (y<w-x) return (h-y-4) + h  + 2*w + x*p - ((7+4*x)*x);
//else return (w-x-3) + w + h + (h-y-1)*p - ((5+4*(h-y-1))*(h-y-1));
//}}
//
//void fillMatrix (int** m, int w, int h) {
//for (int i=0; i<h; i++) {
//for (int j=0; j<w; j++) {
//m[i][j] = getMatrixValue(i, j, w, h);
//}}}
//
//int main (int argc, char** argv) {
//int w = 5, h = 5;
//int** matrix = allocMatrix(w, h);
//fillMatrix(matrix, w, h);
//for (int i=0; i<h; i++) {
//for (int j=0; j<w; j++) {
//printf("%-4d ", matrix[i][j]);
//}
//printf("\r\n");
//}
//freeMatrix(matrix, w, h);
//}
