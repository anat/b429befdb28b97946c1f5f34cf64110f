#ifndef HEAP_H__
# define HEAP_H__

# include "taquin.h"

void add_to_heap(t_node *node);
t_node *get_best_node_from_heap();
void update_node_in_heap(unsigned long ndx);
void swap(int a, int b);

#endif
