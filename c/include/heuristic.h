#ifndef HEURISTIC_H__
# define HEURISTIC_H__

# define H_DIJKSTRA  0 /* if heuristic always returns a cost of zero */
# define H_MANHATTAN 1
# define H_DEFAULT   H_MANHATTAN

int dijkstra(char *grid);
int manhattan(char *grid);

#endif
