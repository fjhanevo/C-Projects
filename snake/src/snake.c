#include <ncurses.h>
#include "snake.h"

void init_snake(Snake *snake, int width, int height)
// spawn the snake in the middle of the screen
{
    snake->pos[0].x = (width) / 2;
    snake->pos[0].y = (height) / 2;
    snake->length = 1;
}

void draw_snake(Snake *snake)
{
    for (int i = 0; i < snake->length; i++) {
        mvaddch(snake->pos[i].y, snake->pos[i].x, (i == 0) ? '@' : '#');
    }
}

void update_direction(Snake *snake, int ch)
{
    switch (ch) {
        case 'w': snake->dir = UP; break;
        case 'a': snake->dir = LEFT; break;
        case 's': snake->dir = DOWN; break;
        case 'd': snake->dir = RIGHT; break;
        default: break;
    }
}

void update_snake(Snake *snake)
{
    // shift body backwards
    for (int i = snake->length - 1; i > 0; i--) {
        snake->pos[i] = snake->pos[i-1];
    }

    // move head based on direction
    switch (snake->dir) {
        case UP: snake->pos[0].y--; break;
        case DOWN: snake->pos[0].y++; break;
        case LEFT: snake->pos[0].x--; break;
        case RIGHT: snake->pos[0].x++; break;
    }
}


