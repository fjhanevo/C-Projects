#ifndef SNAKE_H
#define SNAKE_H

#include "utils.h"

#define SNAKE_SIZE 100

typedef struct {
    Point pos[SNAKE_SIZE];
    int length;
    Direction dir;
} Snake;

void init_snake(Snake *snake, int width, int height);
void draw_snake(Snake *snake);
void update_direction(Snake *snake, int ch);
void update_snake(Snake *snake);

#endif // !SNAKE_H
