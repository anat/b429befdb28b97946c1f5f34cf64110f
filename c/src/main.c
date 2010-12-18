#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "taquin.h"
#include "astar.h"
#include "arguments.h"
#include "alloc.h"
#include "tools.h"

extern t_tq_solver ts;

int main(int argc, char **argv)
{
  t_node *init_state;
  t_node *final_state;
  t_args args;

  signal(SIGINT, sigint_handler);
  get_arguments(&args, argc, argv);

  init_state = get_init_state(args.input_file);
  set_mode(&args);
  final_state = astar(init_state);
  display_path(final_state);

  if (!final_state)
    printf("[ !! ]  Taquin cannot be solved!\n");
  else
    printf("[PERF]  Number of move:    %u\n", final_state->g);
  printf("[TIME]  Closed list size:  %u\n", ts.cl_size);
  printf("[SIZE]  Both list size:    %u\n", ts.op_size + ts.cl_size);

  free_res();
  return (EXIT_SUCCESS);
}
