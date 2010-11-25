#ifndef TAQUIN_H__
# define TAQUIN_H__

typedef char bool;
# define FALSE 0
# define TRUE  !FALSE

/* if MAX_GRID_SIZE > 16, t_node->grid must handle value > 256 */
# define MIN_GRID_SIZE 2
# define MAX_GRID_SIZE 16

struct node;
typedef struct node t_node;

/*
** Each node contains a state
**
** f = g + h.
** g = distance from initial state.
** h = estimation of the distance to the final state.
*/
struct node
{
  int f, g, h;
  char *grid; /* state */
  t_node *c[4]; /* children */
  t_node *parent;
  t_node *next; /* used in opened/closed lists */
};

typedef struct
{
  t_node *op_list;
  t_node *cl_list;
  unsigned int op_size;
  unsigned int cl_size;
  unsigned int grid_size;
  unsigned int side_size;
  int (*heuristic)();
  char final_state[MAX_GRID_SIZE * MAX_GRID_SIZE];
  char final_index[MAX_GRID_SIZE * MAX_GRID_SIZE];
} t_tq_solver;

t_node *alloc_node();

#endif
