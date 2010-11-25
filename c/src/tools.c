#include <stdlib.h>
#include <stdio.h>
#include "tools.h"

void *xmalloc(size_t size)
{
  void *p = malloc(size);

  if ((char *)p == NULL)
    display_error("Error: can not allocate memory.\n");
  return (p);
}

void display_error(char *msg)
{
  fprintf(stderr, "%s", msg);
  exit(EXIT_FAILURE);
}
