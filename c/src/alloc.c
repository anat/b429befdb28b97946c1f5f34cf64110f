#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "taquin.h"
#include "alloc.h"
#include "tools.h"

extern t_tq_solver ts;
static t_alloc nda; /* Node allocator */
static t_alloc gda; /* Grid allocator */

t_node *alloc_node()
{
  if (nda.tab == NULL)
    {
      nda.size = TABLE_SIZE;
      nda.tab = xmalloc(TABLE_SIZE * sizeof(void **));
      nda.tab[0] = xmalloc(sizeof(t_node) * CHUNK_SIZE);
    }
  if (nda.nb_elm >= CHUNK_SIZE)
    {
      nda.nb_elm = 0;
      if (nda.nb_chunk == nda.size-1)
	{
	  nda.size = ((nda.nb_chunk + 1) << 1);
	  nda.tab = xrealloc(nda.tab, nda.size * sizeof(void **));
	}
      nda.tab[++(nda.nb_chunk)] = xmalloc(sizeof(t_node) * CHUNK_SIZE);
      printf("\rchunk[%d] allocated.", nda.nb_chunk);
      fflush(NULL);
    }
  (((t_node*)nda.tab[nda.nb_chunk]) + nda.nb_elm)->next = NULL;
  return (((t_node*)nda.tab[nda.nb_chunk]) + nda.nb_elm++);
}

char *alloc_grid()
{
  if (gda.tab == NULL)
    {
      gda.size = TABLE_SIZE;
      gda.tab = xmalloc(TABLE_SIZE * sizeof(void **));
      gda.tab[0] = xmalloc(ts.grid_size * CHUNK_SIZE);
    }
  if (gda.nb_elm >= CHUNK_SIZE)
    {
      gda.nb_elm = 0;
      if (gda.nb_chunk == gda.size-1)
	{
	  gda.size = ((gda.nb_chunk + 1) << 1);
	  gda.tab = xrealloc(gda.tab, gda.size * sizeof(void **));
	}
      gda.tab[++(gda.nb_chunk)] = xmalloc(ts.grid_size * CHUNK_SIZE);
    }
  return (((char*)gda.tab[gda.nb_chunk]) + (gda.nb_elm++ * ts.grid_size));
}

/* Free all ressources: nodes, grids, heap, hash tables */
void free_res()
{
  int i;

  for (i = 0; i <= nda.nb_chunk; i++)
    free(nda.tab[i]);
  for (i = 0; i <= gda.nb_chunk; i++)
    free(gda.tab[i]);
  free(nda.tab);
  free(gda.tab);
  free(ts.heap);
  free(ts.opened_ht);
  free(ts.closed_ht);
}
