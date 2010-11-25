#ifndef ARGUMENTS_H__
# define ARGUMENTS_H__

# define INCORRECT_FILE_FORMAT "Error: file is not correctly formatted.\n"
# define CANNOT_OPEN_FILE      "Error: can not open file.\n"
# define CANNOT_SOLVE_PROBLEM  "Error: can not solve problem.\n"
# define USAGE_MESSAGE         "Usage: %s file [-h heuristic] [-o file]\n"  \
                               "       -h 0 uses no heuristic (Dijkstra)\n" \
                               "       -h 1 uses manhattan heuristic\n"

typedef struct
{
  char *input_file;
  char *output_file;
} t_args;

t_args *get_arguments(int argc, char **argv);
t_node *get_init_state(char *in_f);

#endif
