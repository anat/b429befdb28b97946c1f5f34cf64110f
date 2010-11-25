#ifndef ASTAR_H__
# define ASTAR_H__

# define COST 1

# define C_UP    0
# define C_DOWN  1
# define C_LEFT  2
# define C_RIGHT 3

/*# define ABS(a) (((a) > 0) ? (a) : -(a))*/
# define MASK_32B(a) ((a) >> 31)
# define ABS(a) (((a) ^ MASK_32B(a)) - MASK_32B(a))
# define SWAP(a, b) {             \
                       c = (a);   \
                       (a) = (b); \
                       (b) = c;   \
                     }

t_node *astar(t_node *a);
void create_children(t_node *cur);
void create_child(t_node *cur, int n);

unsigned int display_path(char *out_f, t_node *final_state);

#endif
