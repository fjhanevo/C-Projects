#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "game.h"

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

static void setup_game(GameState *state)
{
    get_size(&state->width, &state->height);
    // initialize
    initscr();
    noecho();
    draw_borders(state);
    init_snake(&state->snake, state->width, state->height);
    draw_snake(&state->snake);
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
        update_snake(&state.snake);


        // check if food timed out
        if (difftime(time(NULL), state.food.spawn_time) > FOOD_TIME) {
            spawn_food(&state.food, state.width, state.height);
        }

        clear();
        draw_borders(&state);
        draw_snake(&state.snake);
        mvaddch(state.food.pos.y, state.food.pos.x, 'o');


        //TODO: Check snake collision

        refresh();
        napms(100);     // slow down loop
    }
    endwin();
}

