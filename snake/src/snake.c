#include <ncurses.h>
#include "snake.h"

void draw_snake(Snake *snake)
{
    for (int i = 0; i < snake->length; i++) {
        mvaddch(snake->pos[i].y, snake->pos[i].x, (i == 0) ? '@' : '#');
    }
}

void update_direction(Snake *snake, int ch)
{
    Direction new_dir = snake->dir;
    if (ch == 'w' || ch == KEY_UP) new_dir = UP;
    else if (ch == 'a' || ch == KEY_LEFT) new_dir = LEFT;
    else if (ch == 's' || ch == KEY_DOWN) new_dir = DOWN;
    else if (ch == 'd' || ch == KEY_RIGHT) new_dir = RIGHT;

    // prevent reversing
    if (!((snake->dir == UP && new_dir == DOWN) ||
          (snake->dir == DOWN && new_dir == UP) ||
          (snake->dir == LEFT && new_dir == RIGHT) ||
          (snake->dir == RIGHT && new_dir == LEFT))) {
        snake->dir = new_dir;
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


