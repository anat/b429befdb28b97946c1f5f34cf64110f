#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "taquin.h"
#include "astar.h"
#include "lists.h"
#include "alloc.h"
#include "tools.h"

t_tq_solver ts;

/* Return the final state or NULL if no path has been found. */
t_node *astar(t_node *init)
{
  t_node *cur;
  
  add_to_opened_list(init);
  while ((cur = get_best_node()))
    {
      if (!cur->h && cur != init)
	break;
      add_to_closed_list(cur);
      create_children(cur);
    }
  return (cur);
}

/* Try to create adjacent nodes */
inline void create_children(t_node *cur)
{
  create_child(cur, C_UP);
  create_child(cur, C_DOWN);
  create_child(cur, C_LEFT);
  create_child(cur, C_RIGHT);
}

void create_child(t_node *cur, int n)
{
  char tmp[ts.grid_size];
  t_node *child;
  t_node *existing;
  int c, i;

  memcpy(tmp, cur->grid, ts.grid_size);
  for (i = 0; tmp[i]; i++) /* Find blank */
    ;
  /* Move blank if possible */
  if (n == C_UP && ((signed int)(i-ts.side_size)) >= 0)
    SWAP(tmp[i], tmp[i-ts.side_size])
  else if (n == C_DOWN && (i+ts.side_size) < ts.grid_size)
    SWAP(tmp[i], tmp[i+ts.side_size])
  else if (n == C_LEFT && i && (i/ts.side_size) == ((i-1)/ts.side_size))
    SWAP(tmp[i], tmp[i-1])
  else if (n == C_RIGHT && (unsigned int)i < ts.grid_size-1
	   && (i/ts.side_size) == ((i+1)/ts.side_size))
    SWAP(tmp[i], tmp[i+1])
  else
    return;

  if (is_in_list(ts.cl_list, tmp)) /* Dont add it if node is in closed list */
    return;
  if ((existing = is_in_list(ts.op_list, tmp))) /* Update distance */
    {
      if (cur->g + 1 < existing->g)
	{
	  existing->g = cur->g + 1;
	  existing->f = existing->g + existing->h;
	  existing->parent = cur;
	  remove_this_node(existing);
	  add_to_opened_list(existing);
	}
      return;
    }

  /* Create state, init it and add it to open list */
  child = alloc_node();
  cur->c[n] = child;
  child->grid = alloc_grid();
  //child->grid = xmalloc(sizeof(*(child->grid)) * ts.grid_size);
  memcpy(child->grid, tmp, ts.grid_size);  
  child->parent = cur;
  child->h = ts.heuristic(child->grid);
  child->g = cur->g + 1;
  child->f = child->g + child->h;
  add_to_opened_list(child);
}
