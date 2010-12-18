#ifndef TAQUIN_H__
# define TAQUIN_H__

typedef char bool;
# define FALSE 0
# define TRUE  !FALSE

/* if MAX_GRID_SIZE > 16, t_node->grid must handle value > 256 */
# define MIN_GRID_SIZE 2
# define MAX_GRID_SIZE 16

# define DEF_HEAP_SIZE 15
# define HEAP_SIZE     ((unsigned long)1 << ts.hsize) /* (1<<X) == X floor(s) */
# define HEAP_SIZE_INC ((unsigned long)1 << ++(ts.hsize))

# define HT_MASK 1048575 /* Hash table maximum index */
# define HT_MASK_FAST(x) ((8388607<<(x))				\
			  |((unsigned long)-1>>(((sizeof(long)<<3))-(x))))

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
  unsigned long ndx; /* Index used when node is in the heap */
  char *grid; /* state */
  t_node *parent;
  t_node *next; /* used in opened/closed lists */
};

/*
** The following structure contains all informations needed by A*.
** Hash tables, Heap, grid, their sizes and the heuristic to use.
**
** The closed list is actually a hash table, because the hash
** function uses the grid as the key. And we only need to add
** nodes and to search if a grid is already in the closed list.
**
** The opened list is actually composed of a hash table and a heap.
** The opened list must permit to add an element, get the best element
** using it's cost and remove it from this list (the heap is organized
** by cost), and check if a grid is already is the opened list
** (the hash table is organized by grid).
*/
typedef struct
{
  t_node **heap; /* Opened heap. First element is at index 1 */
  t_node **opened_ht; /* Opened hash table */
  t_node **closed_ht; /* Closed hash table */
  unsigned long hndx; /* Heap index */
  unsigned long hsize; /* Default heap size is 15 (2^15 = 1<<15) */
  unsigned int op_size;
  unsigned int cl_size;
  unsigned int grid_size;
  unsigned int side_size;
  int (*heuristic)();
  char final_state[MAX_GRID_SIZE * MAX_GRID_SIZE];
  char final_index[MAX_GRID_SIZE * MAX_GRID_SIZE];
} t_tq_solver;

void display_path(t_node *final_state);

#endif
