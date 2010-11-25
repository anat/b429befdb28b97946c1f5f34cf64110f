#include "taquin.h"
#include "astar.h"
#include "heuristic.h"

extern t_tq_solver ts;

/* If heuristic always return zero, A* acts like Dijkstra's algorithm. */
int dijkstra(char __attribute__ ((unused)) *grid)
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
      //for (j = 0; ts.final_state[j] != grid[i]; j++);
      j = (unsigned char) ts.final_index[(unsigned char) grid[i]];
      if (grid[i])
	{
	  tmp = (i/3) - (j/3);
	  cost += ABS(tmp);
	  tmp = (i%3) - (j%3);
	  cost += ABS(tmp);
	}
    }
  return (cost);
}
