#include <stdlib.h>
#include <string.h>
#include "taquin.h"
#include "lists.h"
#include "heap.h"
#include "tools.h"

#include <stdio.h>
/* When a threshold is reached, hash table size is doubled */
t_th_mk threshold[] =
  {
    {0, HT_MASK},
    {1000000, (HT_MASK<<1)|1},
    {3000000, (HT_MASK<<2)|3},
    {6000000, (HT_MASK<<3)|7},
    {13000000, (HT_MASK<<4)|15}
  };

unsigned long th_ndx; /* Index in the threshold table */
extern t_tq_solver ts;

/*
** This file does not contains linked list manipulating functions.
** Hash tables and heap are used to represent Opened and Closed "lists".
*/

inline unsigned int hash(unsigned char *grid)
{
  unsigned int h = grid[0];
  unsigned int i;

  for (i = 1; i < ts.grid_size; i++)
    h = ((h << 5) - h) + grid[i];
  return (h & threshold[th_ndx].mk);
}

 /* Add node to the opened hash table and to the heap */
inline void add_to_opened_list(t_node *node)
{
  unsigned int h = hash((unsigned char *) node->grid);

  /* Add to opened hash table */
  ts.op_size++;
  if (ts.opened_ht[h])
    node->next = ts.opened_ht[h];
  ts.opened_ht[h] = node;
  /* Add to the heap */
  add_to_heap(node);
}

void update_ht_size(t_node ***ht)
{
  const unsigned long size = threshold[th_ndx].mk + 1;
  t_node *list, *prev, *next;
  unsigned int i;
  unsigned int h;

  *ht = xrealloc(*ht, size * sizeof(t_node *));
  memset(*ht + (size >> 1), 0, (size >> 1) * sizeof(t_node *));
  /* Replace every node */
  for (i = 0; i < (size >> 1); i++)
    {
      list = (*ht)[i];
      prev = NULL;
      while (list)
	{
	  next = list->next;
	  if ((h = hash((unsigned char *) list->grid)) != i)
	    {
	      list->next = ((*ht)[h]) ? (*ht)[h] : NULL;
	      (*ht)[h] = list;
	      if (prev)
		prev->next = next;
	      else
		(*ht)[i] = next;
	    }
	  else
	    prev = list;
	  list = next;
	}
    }
}

/* Add a node to the closed list. */
inline void add_to_closed_list(t_node *node)
{
  unsigned int h;

  ts.cl_size++;
  /*
  ** Realloc closed and opened hash tables when there is too much
  ** elements (collisions) in the closed list. Most of the execution time,
  ** there is more element in the opened list than in the closed list.
  ** So when a threshold is reached by the closed hash table, we realloc it
  ** and also realloc the opened hash table.
  */
  if (th_ndx < (sizeof(threshold) / sizeof(t_th_mk))
      && ts.cl_size == threshold[th_ndx+1].th)
    {
      printf(" [threshold[%lu] reached] New HTs size is %lu.\n",
	     th_ndx, threshold[th_ndx+1].mk+1);
      th_ndx++;
      update_ht_size(&ts.closed_ht);
      update_ht_size(&ts.opened_ht);
    }

  /* Add the node */
  h = hash((unsigned char *) node->grid);
  if (ts.closed_ht[h])
    node->next = ts.closed_ht[h];
  ts.closed_ht[h] = node;
}

/* Get best node from heap and from opened hash table */
t_node *get_best_node()
{
  t_node *best, *tmp, *prev;
  unsigned int h;

  if ((best = get_best_node_from_heap()))
    {
      ts.op_size--;
      h = hash((unsigned char *) best->grid);
      tmp = ts.opened_ht[h];
      if (tmp == best)
	ts.opened_ht[h] = tmp->next;
      else
	{
	  prev = tmp;
	  while ((tmp = tmp->next))
	    {
	      if (tmp == best)
		{
		  prev->next = tmp->next;
		  break;
		}
	      prev = tmp;
	    }
	}
      best->next = NULL;
    }
  return (best);
}

/* Check if node is in the opened hash table */
inline t_node *is_in_op_list(char *grid)
{
  unsigned int h = hash((unsigned char *) grid);
  t_node *list;

  list = ts.opened_ht[h];
  while (list)
    {
      if (!memcmp(list->grid, grid, ts.grid_size))
	return (list);
      list = list->next;
    }
  return (NULL);
}

inline t_node *is_in_cl_list(char *grid)
{
  unsigned int h = hash((unsigned char *) grid);
  t_node *list;

  list = ts.closed_ht[h];
  while (list)
    {
      if (!memcmp(list->grid, grid, ts.grid_size))
	return (list);
      list = list->next;
    }
  return (NULL);
}
