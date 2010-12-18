#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "taquin.h"
#include "heuristic.h"
#include "arguments.h"
#include "lists.h"
#include "alloc.h"
#include "tools.h"

extern t_tq_solver ts;
extern t_th_mk threshold[];
extern unsigned long th_ndx;

void get_arguments(t_args *args, int argc, char **argv)
{
  int (*hptr[])() = {zero, manhattan, misplaced, euclide, perso};
  int h = H_DEFAULT, i;
  bool err = FALSE;
  
  args->fast = 0;
  args->input_file = NULL;
  for (i = 1; i < argc; i++)
    {
      if (!strcmp(argv[i], "-h") && argv[i+1])
	h = atoi(argv[++i]);
      else if (!strcmp(argv[i], "-f") && argv[i+1])
	args->fast = atoi(argv[++i]);
      else if (argv[i][0] != '-')
	args->input_file = argv[i];
      else
	err = TRUE;
    }
  if (!err && args->input_file && (h >= H_MIN && h <= H_MAX))
    ts.heuristic = hptr[h];
  else
    display_error(USAGE_MESSAGE);
}

void compute_final_state()
{
  unsigned int i = 0, j = 0, mov = 4, n;
  unsigned int minh = 0, maxh = 0, minv = 1, maxv = 0;

  for (n = 1; n < ts.grid_size; n++)
    {
      ts.final_index[n] = i * ts.side_size + j;
      ts.final_state[(unsigned char)ts.final_index[n]] = n;
      if (mov == 4)
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
      else if (mov == 2)
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
      else if (mov == 3)
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
      else
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
	      n->grid = alloc_grid();
	      n->g = 0;
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

void set_mode(t_args *args)
{
  /* Set fast mode only if n-puzzle size is greater than 3*3 */
  if (args->fast >= 1 && args->fast <= 4 && ts.side_size > 3)
    {
      threshold[0].mk = HT_MASK_FAST(args->fast);
      th_ndx = args->fast;
    }
}
