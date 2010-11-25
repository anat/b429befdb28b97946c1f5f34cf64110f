#include <stdlib.h>
#include <stdio.h>
#include "taquin.h"
#include "lists.h"

extern t_tq_solver ts;

unsigned int display_path(char *out_f, t_node *final_state)
{
  t_node *tmp = final_state;
  unsigned int n = 0;
  unsigned int i;

  (void) out_f;
  tmp->c[0] = NULL;

  /* Reverse links */
  while (tmp->parent)
    {
      tmp->parent->c[0] = tmp;
      tmp = tmp->parent;
    }

  /* Display */
  while (tmp)
    {
      //printf(">> %d <<\n", tmp->h);
      for (i = 0; i < ts.grid_size; i++)
	{
	  if (!(i % ts.side_size))
	    printf("\n");
	  printf("%3d ", (unsigned char) tmp->grid[i]);
	}
      printf("\n");
      //!char buff[2];read(0, buff, 2);
      tmp = tmp->c[0];
      n++;
    }

  //remove_list(ts.op_list);
  //remove_list(ts.cl_list);
  return (n-1); /* n is the number of node from A to B (included) */
}
