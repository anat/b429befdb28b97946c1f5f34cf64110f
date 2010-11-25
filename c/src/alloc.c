#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "taquin.h"
#include "alloc.h"
#include "tools.h"

extern t_tq_solver ts;

# define CHUNK_SIZE 200000

t_node *alloc_node()
{
  static t_node *ptr;

  //t_node *n = xmalloc(sizeof(*n));
  //memset(n, 0, sizeof(*n));
  //return (n);
  if (!ptr)
    {
      ptr = xmalloc(sizeof(t_node) * CHUNK_SIZE);
      memset(ptr, 0, sizeof(t_node) * CHUNK_SIZE);
    }
  return (ptr++);
}

char *alloc_grid()
{
  static char *ptr;
  char *tmp;

  if (!ptr)
    ptr = xmalloc(sizeof(char) * ts.grid_size * CHUNK_SIZE);
  tmp = ptr;
  ptr += ts.grid_size;
  return (tmp);
}
