#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "taquin.h"
#include "heuristic.h"
#include "arguments.h"
#include "alloc.h"
#include "tools.h"

extern t_tq_solver ts;

t_args *get_arguments(int argc, char **argv)
{
  int (*hptr[])() = {dijkstra, manhattan};
  char *in_f = NULL, *out_f = NULL;
  t_args *p = NULL;
  bool err = FALSE;
  int h = H_DEFAULT, i;
  
  for (i = 1; i < argc; i++)
    {
      if (!strcmp(argv[i], "-h") && argv[i+1])
	h = atoi(argv[++i]);
      else if (!strcmp(argv[i], "-o") && argv[i+1])
	out_f = argv[++i];
      else if (argv[i][0] != '-')
	in_f = argv[i];
      else
	err = TRUE;
    }
  if (!err && in_f && (h >= 0 && h <= 1))
    {
      p = xmalloc(sizeof(*p));
      ts.heuristic = hptr[h];
      p->input_file = in_f;
      p->output_file = out_f;
    }
  return (p);
}

void compute_final_state()
{
  unsigned int i = 0, j = 0, mov = 4, n;
  unsigned int minh = 0, maxh = 0, minv = 1, maxv = 0;

  for (n = 1; n < ts.grid_size; n++)
    {
      ts.final_index[n] = i * ts.side_size + j;
      ts.final_state[(unsigned char)ts.final_index[n]] = n;
      if (mov == 4) // RIGHT
	{
	  if (j < ts.side_size - 1 - maxh)
	    j++;
	  else
	    {
	      maxh++;
	      i = minv;
	      mov = 2;
	    }
	}
      else if (mov == 2) // DOWN
	{
	  if (i < ts.side_size - 1 - maxv)
	    i++;
	  else
	    {
	      maxv++;
	      j = ts.side_size - 1 - maxh;
	      mov = 3;
	    }
	}
      else if (mov == 3) // LEFT
	{
	  if (j > 0 + minh)
	    j--;
	  else
	    {
	      minh++;
	      i = ts.side_size - 1 - maxv;
	      mov = 1;
	    }
	}
      else // UP
	{
	  if (i > 0 + minv)
	    i--;
	  else
	    {
	      minv++;
	      j = minh;
	      mov = 4;
	    }
	}
    }
  ts.final_index[0] = i * ts.side_size + j;
  ts.final_state[(unsigned char)ts.final_index[0]] = 0;
}

t_node *get_init_state(char *in_f)
{
  int fd = open(in_f, O_RDONLY);
  t_node *n = alloc_node();
  char buff[2048];
  unsigned int tmp, line, col, j, i = 0;
  int cc;
  
  if (fd != -1)
    {
      cc = read(fd, buff, 2047);
      if (cc > 0)
	{
	  buff[cc] = '\0';
	  ts.side_size = atoi(buff);
	  if (ts.side_size >= MIN_GRID_SIZE && ts.side_size <= MAX_GRID_SIZE)
	    {
	      /* Initialization */
	      ts.grid_size = ts.side_size * ts.side_size;
	      compute_final_state();
	      n->grid = xmalloc(sizeof(*(n->grid)) * ts.grid_size);
	      while (buff[i] && buff[i] != '\n')
		i++;
	      if (!buff[i++])
		display_error(INCORRECT_FILE_FORMAT);

	      /* Extract numbers */
	      for (line = 0; line < ts.side_size; line++)
		for (col = 0; col < ts.side_size; col++)
		  {
		    if ((tmp = atoi(buff + i)) >= ts.grid_size)
		      display_error(INCORRECT_FILE_FORMAT);
		    n->grid[line * ts.side_size + col] = tmp;
		    while (buff[i] && buff[i] != ' ' && buff[i] != '\n')
		      i++;
		    if (!buff[i++] && !(col+1 == ts.side_size
					&& line+1 == ts.side_size))
		      display_error(INCORRECT_FILE_FORMAT);
		  }

	      /* Verify that numbers are in the correct range */
	      for (i = 0; i < ts.grid_size; i++)
		for (j = 0; j < ts.grid_size; j++)
		  if (i != j && n->grid[i] == n->grid[j])
		    display_error(INCORRECT_FILE_FORMAT);
	      n->h = ts.heuristic(n->grid);
	      return (n);
	    }
	}
      close(fd);
      display_error(INCORRECT_FILE_FORMAT);
    }
  display_error(CANNOT_OPEN_FILE);
  return (NULL);
}
