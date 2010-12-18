#ifndef ALLOC_H__
# define ALLOC_H_

# define TABLE_SIZE 1024 /* Nb of element = TABLE_SIZE * CHUNK_SIZE */
# define CHUNK_SIZE 200000

typedef struct allocator
{
  void **tab; /* Table which contains chunk addresses */
  int size; /* Table size */
  int nb_chunk; /* Number of chunk in the table */
  int nb_elm; /* Number of node, in the current chunk, that are already used */
} t_alloc;

t_node *alloc_node();
char *alloc_grid();
void free_res();

#endif
