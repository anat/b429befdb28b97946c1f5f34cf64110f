#include <stdlib.h>
#include <string.h>
#include "taquin.h"

extern t_tq_solver ts;

/* Add a node to the sorted opened list. */
void add_to_opened_list(t_node *node)
{
  t_node *list = ts.op_list;
  t_node *prev = NULL;

  ts.op_size++;
  if (!ts.op_list)
    ts.op_list = node;
  else
    {
      while (list)
	{
	  if (node->f < list->f)
	    {
	      node->next = list;
	      if (!prev)
		ts.op_list = node;
	      else
		prev->next = node;
	      return;
	    }
	  prev = list;
	  list = list->next;
	}
      prev->next = node;
    }
}

/* Add a node to the closed list. */
inline void add_to_closed_list(t_node *node)
{
  ts.cl_size++;
  //printf("\r          ");
  //printf("%d", ts.cl_size);
  //fflush(NULL);
  node->next = ts.cl_list;
  ts.cl_list = node;
}

/* Get the best node from the opened list. */
inline t_node *get_best_node()
{
  t_node *tmp = ts.op_list;

  if (ts.op_list)
    {
      ts.op_size--;
      ts.op_list = ts.op_list->next;
      tmp->next = NULL;
    }
  return (tmp);
}

/* Remove a node from the opened list. */
void remove_this_node(t_node *node)
{
  t_node *tmp = ts.op_list;
  t_node *prev = NULL;

  while (tmp)
    {
      if (tmp == node)
	{
	  ts.op_size--;
	  if (prev)
	    prev->next = tmp->next;
	  else
	    ts.op_list = tmp->next;
	  tmp->next = NULL;
	  break;
	}
      prev = tmp;
      tmp = tmp->next;
    }
}

inline t_node *is_in_list(t_node *list, char *grid)
{
  while (list)
    {
      if (!memcmp(list->grid, grid, ts.grid_size))
	return (list);
      list = list->next;
    }
  return (NULL);
}

void remove_list(t_node *list)
{
  t_node *back;

  while (list)
    {
      back = list;
      list = list->next;
      free(back->grid);
      free(back);
    }
}
