#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "game.h"
#include "snake.h"

#define FOOD_TIME 10
#define GAME_SPEED 200

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

static int check_food_collision(GameState *state) 
{
    if (state->snake.pos[0].x == state->food.pos.x &&
        state->snake.pos[0].y == state->food.pos.y) {
        return 1;
    } 
    return 0;
}

static int check_collision(GameState *state)
{
    int x = state->snake.pos[0].x;
    int y = state->snake.pos[0].y;

    // check border collision
    if (x <= 0 || x >= state->width - 1 ||
        y <= 0 || y >= state->height - 1) {
        return 1;
    }

    // check self collision
    for (int i = 1; i < state->snake.length - 1; i++) {
        if (x == state->snake.pos[i].x && 
            y == state->snake.pos[i].y) {
            return 1;
        }
    }
    return 0;
}

static void setup_game(GameState *state)
{
    get_size(&state->width, &state->height);
    // initialize
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    curs_set(0);    // hide cursor
    draw_borders(state);
    init_snake(&state->snake, state->width, state->height);
    draw_snake(&state->snake);
    refresh();
}

void play_snake(GameState *state)
// main function to play the game
{
    srand(time(NULL));
    setup_game(state);

    // main game loop
    while (1) {
        int ch = getch();
        // make snake move regardless of input
        //TODO: Fix long keypresses
        if (ch != ERR) {
            if (ch == 'q') break;
            update_direction(&state->snake, ch);
        }
        update_snake(&state->snake);

        // check if food timed out
        if (difftime(time(NULL), state->food.spawn_time) > FOOD_TIME) {
            spawn_food(&state->food, &state->snake, state->width, state->height);
        }

        // check if snake head collides with food
        if (check_food_collision(state)) {
            state->score++;
            state->snake.length++;
            spawn_food(&state->food, &state->snake, state->width, state->height);
        }

        if (check_collision(state)) {
            break;
        }
        clear();
        draw_borders(state);
        draw_snake(&state->snake);
        mvaddch(state->food.pos.y, state->food.pos.x, 'o');

        // add score to display
        mvprintw(state->height + 1, 0, "Score: %d", state->score);
        refresh();
        // speed up loop based on increasing score
        int delay = GAME_SPEED - state->score;
        if (delay < 20) delay = 20; // set 20 to min speed
        //TODO: Add play again option
        napms(delay);     // slow down loop
    }
    endwin();
}

