#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "heuristic.h"
#include "taquin.h"
#include "astar.h"
#include "lists.h"
#include "heap.h"
#include "alloc.h"
#include "tools.h"

t_tq_solver ts;
extern t_th_mk threshold[];

/* Return the final state or NULL if no path has been found. */
t_node *astar(t_node *init)
{
  t_node *cur;

  ts.hndx = 1;
  ts.hsize = DEF_HEAP_SIZE;
  ts.heap = xmalloc(sizeof(*ts.heap) * HEAP_SIZE);
  ts.opened_ht = xcalloc(threshold[0].mk+1, sizeof(t_node *));
  ts.closed_ht = xcalloc(threshold[0].mk+1, sizeof(t_node *));

  add_to_opened_list(init);
  if (ts.heuristic == zero)
    return (astar_zero());

  while ((cur = get_best_node()) && cur->h)
    {
      add_to_closed_list(cur);
      create_children(cur);
    }
  return (cur);
}

/* This function is called if heuristic is always set to zero */
t_node *astar_zero()
{
  t_node *cur;

  while ((cur = get_best_node()))
    {
      if (!memcmp(cur->grid, ts.final_state, ts.grid_size))
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

  if (is_in_cl_list(tmp)) /* Dont add it if node is in closed list */
    return;

  if ((existing = is_in_op_list(tmp))) /* Update distance */
    {
      if (cur->g + 1 < existing->g)
	{
	  existing->g = cur->g + 1;
	  existing->f = existing->g + existing->h;
	  existing->parent = cur;
	  update_node_in_heap(existing->ndx);
	}
      return;
    }

  /* Create state, init it and add it to open list */
  child = alloc_node();
  child->grid = alloc_grid();
  memcpy(child->grid, tmp, ts.grid_size);  
  child->parent = cur;
  child->h = ts.heuristic(child->grid);
  child->g = cur->g + 1;
  child->f = child->g + child->h;
  add_to_opened_list(child);
}
