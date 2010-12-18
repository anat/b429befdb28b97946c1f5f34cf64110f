#include <stdlib.h>
#include <stdio.h>
#include "taquin.h"
#include "tools.h"

extern t_tq_solver ts;

void *xmalloc(size_t size)
{
  void *p = malloc(size);

  if (p == NULL)
    display_error("Error: can not allocate memory.\n");
  return (p);
}

void *xrealloc(void *ptr, size_t size)
{
  void *p = realloc(ptr, size);
  
  if (p == NULL)
    display_error("Error: can not realloc memory.\n");
  return (p);
}

void *xcalloc(size_t n, size_t size)
{
  void *p = calloc(n, size);
  
  if (p == NULL)
    display_error("Error: can not realloc memory.\n");
  return (p);
}

void sigint_handler(int __attribute__((unused)) n)
{
  printf("\r\n");
  printf("[OPENED] list size:  %u\n", ts.op_size);
  printf("[CLOSED] list size:  %u\n", ts.cl_size);
  printf("[ BOTH ] list size:  %u\n", ts.op_size + ts.cl_size);
  exit(EXIT_FAILURE);
}

void display_error(char *msg)
{
  fprintf(stderr, "%s", msg);
  exit(EXIT_FAILURE);
}
