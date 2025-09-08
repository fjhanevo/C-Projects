#ifndef FOOD_H
#define FOOD_H

#include <time.h>
#include "utils.h"

typedef struct {
    Point pos;
    time_t spawn_time;
} Food;

void spawn_food(Food *food, int width, int height);

#endif // !FOOD_H
