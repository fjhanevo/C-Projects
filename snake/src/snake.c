#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "snake.h"

#define MAX_INPUT 128
#define MAX_WIDTH 116
#define MAX_HEIGHT 60
#define MIN_SIZE 2
#define FOOD_TIME 10
 

static void draw_borders(GameState *state)
// make sure initscr is called first
{
    const char char_width = '-';
    const char char_height = '|';

    // draw top and bottom
    for (int x = 0; x <state->width; x++) {
        mvaddch(0, x, char_width);
        mvaddch(state->height-1, x, char_width);
    }

    // draw left and right columns
    for (int y = 0; y < state->height; y++) {
        // position 0 is already drawn
        mvaddch(y, 0, char_height);
        mvaddch(y, state->width-1, char_height);
    }
}

static int get_valid_int(const char *msg, int max)
/* helper function for get_size to get valid input for height and width */
{
    char buf[MAX_INPUT];
    char *end;
    long val;

    while (1) {
        printf("%s", msg);
        if (!fgets(buf, sizeof(buf), stdin)) exit(1);

        val = strtol(buf, &end, 10);
        if (end == buf || (*end != '\n' && *end != '\0')) {
            printf("Invalid number!\n\n");
            continue;
        }
        if (val < MIN_SIZE || val > max) {
            printf("Value must be between %d and %d\n\n", MIN_SIZE, max);
            continue;
        }
        return (int)val;
    }
}

static void get_size(int *width, int *height) 
{
    *width = get_valid_int("Please type in border width: ", MAX_WIDTH); 
    *height = get_valid_int("Please type in border height: ", MAX_HEIGHT);
}

static void spawn_food(GameState *state)
{
    state->food.pos.x = rand() % (state->width - 2) + 1;    // avoid borders 
    state->food.pos.y = rand() % (state->height - 2) + 1;    // avoid borders 
    state->food.spawn_time = time(NULL);
    mvaddch(state->food.pos.y, state->food.pos.x, 'o');
}

static void init_snake(GameState *state)
// spawn the snake in the middle of the screen
{
    state->snake.pos[0].x = (state->width) / 2;
    state->snake.pos[0].y = (state->height) / 2;
    state->snake.length = 1;
    state->score = 0;
}

static void draw_snake(GameState *state)
{
    for (int i = 0; i < state->snake.length; i++) {
        mvaddch(state->snake.pos[i].y, state->snake.pos[i].x, '#');
    }
}

static void update_direction(Snake *snake, int ch)
{
    switch (ch) {
        case 'w': snake->dir = UP; break;
        case 'a': snake->dir = LEFT; break;
        case 's': snake->dir = DOWN; break;
        case 'd': snake->dir = RIGHT; break;
        default: break;
    }
}

static void update_snake(Snake *snake)
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

static void setup_game(GameState *state)
{
    get_size(&state->width, &state->height);
    // initialize
    initscr();
    noecho();
    draw_borders(state);
    refresh();
    init_snake(state);
    draw_snake(state);
    refresh();
    spawn_food(state);
    refresh();


}

void play_snake()
// main function to play the game
{
    // variables
    srand(time(NULL));
    GameState state;

    setup_game(&state);

    // main game loop
    while (1) {
        //TODO: Fix how movement works...
        int ch = getch();
        if (ch == 'q') break;
        update_direction(&state.snake, ch);
        //TODO: Add update_snake and test!


        // check if food timed out
        if (difftime(time(NULL), state.food.spawn_time) > FOOD_TIME) {
            spawn_food(&state);
        }

        //TODO: Check snake collision

        refresh();
        napms(100);     // slow down loop
    }
    endwin();
}

