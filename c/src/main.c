#include <stdio.h>
#include <stdlib.h>

#include "taquin.h"
#include "astar.h"
#include "arguments.h"
#include "tools.h"

extern t_tq_solver ts;

int main(int argc, char **argv)
{
  t_args *args;
  t_node *init_state;
  t_node *final_state;
  int nb_move;

  if (!(args = get_arguments(argc, argv)))
    display_error(USAGE_MESSAGE);

  init_state = get_init_state(args->input_file);
  final_state = astar(init_state);

  if (!final_state)
    printf("[ !! ]  Taquin cannot be solved!\n");
  else
    {
      nb_move = display_path(args->output_file, final_state);
      printf("[PERF]  Number of move:    %u\n", nb_move);
    }
  printf("[TIME]  Closed list size:  %u\n", ts.cl_size);
  printf("[SIZE]  Both list size:    %u\n", ts.op_size + ts.cl_size);
  free(args);
  return (EXIT_SUCCESS);
}
