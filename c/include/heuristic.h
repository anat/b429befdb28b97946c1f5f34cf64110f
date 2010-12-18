#ifndef HEURISTIC_H__
# define HEURISTIC_H__

# define H_ZERO      0 /* This heuristic always returns a cost of zero */
# define H_MANHATTAN 1
# define H_MISPLACED 2
# define H_EUCLIDE   3
# define H_PERSO     4

# define H_DEFAULT   H_MANHATTAN
# define H_MIN       H_ZERO
# define H_MAX       H_PERSO

int zero(char *grid);
int manhattan(char *grid);
int misplaced(char *grid);
int euclide(char *grid);
int perso(char *grid);

#endif
