#ifndef SNAKE_H
#define SNAKE_H
#include <time.h>

#define SNAKE_SIZE 100

typedef struct {
    int x;
    int y;
} Point; 

typedef struct {
    Point pos;
    time_t spawn_time;
} Food;

typedef struct {
    Point pos[SNAKE_SIZE];
    int length;
} Snake;

typedef struct {
    Snake snake;
    Food food;
    int score;
    int height;
    int width;
} GameState;

void play_snake();

#endif // !SNAKE_H
