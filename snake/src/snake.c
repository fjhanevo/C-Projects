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

static void spawn_food(Food *food, int width, int height)
{
    food->pos.x = rand() % (width - 2) + 1;    // avoid borders 
    food->pos.y = rand() % (height - 2) + 1;    // avoid borders 
    food->spawn_time = time(NULL);
    mvaddch(food->pos.y, food->pos.x, 'o');
}

static void init_snake(GameState *state)
{
    state->snake.pos[0].x = (state->width) / 2;
    state->snake.pos[0].y = (state->height) / 2;
    state->snake.length = 1;
}

static void draw_snake(GameState *state)
{
    for (int i = 0; i < state->snake.length; i++) {
        mvaddch(state->snake.pos[i].y, state->snake.pos[i].x, '#');
    }
}


void play_snake()
// main function to play the game
{
    // variables
    srand(time(NULL));
    GameState state;
    Food food;
    Snake snake; 

    get_size(&state.width, &state.height);
    // initialize
    initscr();
    clear();
    draw_borders(state.width, state.height);
    /* refresh(); */
    /* init_snake(&snake, state.width, state.height); */
    /* draw_snake(&snake); */
    /* refresh(); */
    /* spawn_food(&food, width, height); */
    /* refresh(); */

    // main game loop
    while (1) {
        int ch = getch();
        if (ch == 'q') break;

        // check if food timed out
        if (difftime(time(NULL), food.spawn_time) > FOOD_TIME) {
            spawn_food(&food, width, height);
        }

        //TODO: Check snake collision

        refresh();
        napms(100);     // slow down loop
    }
    endwin();
    clear();

}

