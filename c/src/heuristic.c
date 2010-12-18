#include "taquin.h"
#include "astar.h"
#include "heuristic.h"
#include <math.h>

extern t_tq_solver ts;

/* If heuristic always return zero, A* acts like Dijkstra's algorithm. */
inline int zero(char __attribute__((unused)) *grid)
{
  return (0);
}

/* Manhattan distance */
int manhattan(char *grid)
{
  int cost = 0, tmp;
  unsigned int i, j;

  for (i = 0; i < ts.grid_size; i++)
    {
      j = (unsigned char) ts.final_index[(unsigned char) grid[i]];
      if (grid[i])
	{
	  tmp = (i/ts.side_size) - (j/ts.side_size);
	  cost += ABS(tmp);
	  tmp = (i%ts.side_size) - (j%ts.side_size);
	  cost += ABS(tmp);
	}
    }
  return (cost);
}

/* Euclidian distance */
int euclide(char *grid)
{
  int cost = 0, x, y;
  unsigned int i, j;

  for (i = 0; i < ts.grid_size; i++)
    {
      j = (unsigned char) ts.final_index[(unsigned char) grid[i]];
      if (grid[i])
	{
	  y = (i/ts.side_size) - (j/ts.side_size);
	  x = (i%ts.side_size) - (j%ts.side_size);
	  cost += (int) sqrt((x*x) + (y*y));
	}
    }
  return (cost);
}

/* Misplaced tiles */
int misplaced(char *grid)
{
  int cost = 0;
  unsigned int i, j;

  for (i = 0; i < ts.grid_size; i++)
    {
      j = (unsigned char) ts.final_index[(unsigned char) grid[i]];
      if (grid[i] && i != j)
	cost++;
    }
  return (cost);
}

/* Perso (based on manhattan) */
int perso(char *grid)
{
  int cost = 0, tmp, tmp2;
  unsigned int i, j;

  for (i = 0; i < ts.grid_size; i++)
    {
      j = (unsigned char) ts.final_index[(unsigned char) grid[i]];
      if (grid[i])
	{
	  /* manhattan */
	  tmp = (i/ts.side_size) - (j/ts.side_size);
	  tmp = ABS(tmp);
	  tmp2 = (i%ts.side_size) - (j%ts.side_size);
	  tmp2 = tmp + ABS(tmp2);
	  /* manahattan distance is increased (more realist estimation) */
	  tmp = tmp2 * tmp2;
	  tmp = (tmp > 1) ? tmp >> 1 : tmp;
	  cost += tmp;
	}
    }
  return (cost);
}
