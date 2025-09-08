#include <ncurses.h>
#include <stdlib.h>
#include "food.h"
#include "snake.h"


void spawn_food(Food *food, const Snake *snake, int width, int height)
{
    int valid_pos = 0;

    while (!valid_pos) {
        // generate random coords inside the borders

        int x = rand() % (width - 2) + 1;
        int y = rand() % (height - 2) + 1;

        // assume valid postion, but check against snake
        valid_pos = 1;
        for (int i = 0; i < snake->length; i++) {
            if (snake->pos[i].x == x && snake->pos[i].y == y) {
                valid_pos = 0;  // overlap detected, try again
                break;
            }
        }
        if (valid_pos) {
            food->pos.x = x;
            food->pos.y = y;
            food->spawn_time = time(NULL);
        }
    }
    mvaddch(food->pos.y, food->pos.x, 'o');
}


