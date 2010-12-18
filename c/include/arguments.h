#ifndef ARGUMENTS_H__
# define ARGUMENTS_H__

# define INCORRECT_FILE_FORMAT "Error: file is not correctly formatted.\n"
# define CANNOT_OPEN_FILE      "Error: can not open file.\n"
# define CANNOT_SOLVE_PROBLEM  "Error: can not solve problem.\n"
# define USAGE_MESSAGE         "Usage: ./taquin file [-h heuristic] [-f]\n"      \
                               "       -h 0 = no heuristic\n"                    \
                               "       -h 1 = manhattan heuristic\n"             \
                               "       -h 2 = misplaced heuristic\n"             \
                               "       -h 3 = euclide heuristic\n"               \
                               "       -h 4 = homemade heuristic\n"       \
                               "       -f 1-4 = fast mode (memory-consumming)\n" 

typedef struct
{
  char *input_file;
  int fast;
} t_args;

void get_arguments(t_args *args, int argc, char **argv);
t_node *get_init_state(char *in_f);
void set_mode(t_args *args);

#endif
