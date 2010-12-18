#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "taquin.h"
#include "lists.h"

extern t_tq_solver ts;

void display_path(t_node *state)
{
  unsigned int i;

  if (state)
    {
      state->next = NULL;
      while (state->parent) /* Reverse links */
	{
	  state->parent->next = state;
	  state = state->parent;
	}
      
      while (state) /* Display */
	{
	  for (i = 0; i < ts.grid_size; i++)
	    {
	      if (i && !(i % ts.side_size))
		printf("\n");
	      printf("%3d ", (unsigned char) state->grid[i]);
	      if (i+1 == ts.side_size)
		printf("  [ F=%d G=%d H=%d ]", state->f, state->g, state->h);
	    }
	  printf("\n\n");

#ifdef STEP_MODE
	  {
	    char buff[2];
	    read(0, buff, 1);
	  }
#endif
	  state = state->next;
	}
    }
}
