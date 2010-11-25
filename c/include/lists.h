#ifndef LISTS_H__
# define LISTS_H__

# include "taquin.h"

t_node *get_best_node();
t_node *is_in_list(t_node *list, char *node);
void remove_this_node(t_node *node);
void remove_list(t_node *list);
void add_to_closed_list(t_node *node);
void add_to_opened_list(t_node *node);

#endif
