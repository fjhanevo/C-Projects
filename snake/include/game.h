#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"

typedef struct {
    Snake snake;
    Food food;
    int score;
    int height;
    int width;
} GameState;

void play_snake(GameState *state);

#endif // !GAME_H
