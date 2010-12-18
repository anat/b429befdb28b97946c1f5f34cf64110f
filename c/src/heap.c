#include <stdlib.h>
#include "taquin.h"
#include "tools.h"
#include "heap.h"

extern t_tq_solver ts;

inline void swap(int a, int b)
{
  t_node *c;
  int tmp;

  /* Swap pointers */
  c = ts.heap[a];
  ts.heap[a] = ts.heap[b];
  ts.heap[b] = c;
  /* Swap index values */
  tmp = ts.heap[a]->ndx;
  ts.heap[a]->ndx = ts.heap[b]->ndx;
  ts.heap[b]->ndx = tmp;
}

void add_to_heap(t_node *node)
{
  unsigned int parent;
  unsigned int child;

  if (ts.hndx & ((unsigned long)-1 << ts.hsize))
    ts.heap = xrealloc(ts.heap, sizeof(*ts.heap) * HEAP_SIZE_INC);
  /* Add to heap */
  ts.heap[ts.hndx] = node;
  node->ndx = ts.hndx;
  if (ts.hndx > 1)
    {
      child = ts.hndx;
      parent = ts.hndx;
      while (parent > 1)
	{
	  parent >>= 1;
	  if (ts.heap[parent]->f >= ts.heap[child]->f)
	    swap(parent, child);
	  else
	    break;
	  child = parent;
	}
    }
  ts.hndx++;
}

/* Take the first element in the heap and reorganize it */
t_node *get_best_node_from_heap()
{
  t_node *best = ts.heap[1];
  unsigned int parent, min;
  unsigned int child1, child2;

  if (ts.heap[1])
    {
      ts.heap[1] = ts.heap[--ts.hndx];
      ts.heap[1]->ndx = 1;
      ts.heap[ts.hndx] = NULL;
      parent = 1;
      child1 = 2;
      child2 = 3;
      while (child1 < ts.hndx)
	{
	  if (child2 < ts.hndx)
	    min = (ts.heap[child1]->f < ts.heap[child2]->f) ? child1 : child2;
	  else
	    min = child1;
	  if (ts.heap[parent]->f >= ts.heap[min]->f)
	    swap(parent, min);
	  else 
	    break;
	  parent = min;
	  child1 = parent << 1;
	  child2 = (parent << 1) + 1;
	}
    }
  return (best);
}

/* Move a node up in the tree if it's new f value is lower than it's parent's */
void update_node_in_heap(unsigned long ndx)
{
  unsigned long parent;
  unsigned long child;

  if (ndx > 1)
    {
      child = ndx;
      parent = ndx;
      while (parent > 1)
	{
	  parent >>= 1;
	  if (ts.heap[parent]->f > ts.heap[child]->f)
	    swap(parent, child);
	  else
	    break;
	  child = parent;
	}
    }  
}
