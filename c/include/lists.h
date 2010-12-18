#ifndef LISTS_H__
# define LISTS_H__

# include "taquin.h"

typedef struct
{
  unsigned long th;
  unsigned long mk;
} t_th_mk; /* threshold - mask */

t_node *get_best_node();
t_node *is_in_op_list(char *node);
t_node *is_in_cl_list(char *node);

void update_ht_size(t_node ***ht);
void add_to_closed_list(t_node *node);
void add_to_opened_list(t_node *node);

#endif
