#ifndef UTILS_H
#define UTILS_H

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

typedef struct {
    int x;
    int y;
} Point;

void get_size(int *width, int *height);

#endif /* ifndef UTILS_H */
