#include <ncurses.h>
#include <stdlib.h>
#include "food.h"


void spawn_food(Food *food, int width, int height)
{
    food->pos.x = rand() % (width - 2) + 1;    // avoid borders 
    food->pos.y = rand() % (height - 2) + 1;    // avoid borders 
    food->spawn_time = time(NULL);
    mvaddch(food->pos.y, food->pos.x, 'o');
}


