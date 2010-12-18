#ifndef TOOLS_H__
# define TOOLS_H__

void *xmalloc(size_t size);
void *xrealloc(void *ptr, size_t size);
void *xcalloc(size_t n, size_t size);
void sigint_handler(int);
void display_error(char *msg);

#endif
