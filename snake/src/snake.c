#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "snake.h"

#define MAX_INPUT 128
#define MAX_WIDTH 116
#define MAX_HEIGHT 60
#define MIN_SIZE 2
 

void draw_borders(int width, int height)
// make sure initscr is called first
{
    // coord variables
    const char wall = '0';

    // draw top and bottom
    for (int x = 0; x < width; x++) {
        mvaddch(0, x, wall);
        mvaddch(height-1, x, wall);
    }

    // draw left and right columns
    for (int y = 0; y < height; y++) {
        // position 0 is already drawn
        mvaddch(y, 0, wall);
        mvaddch(y, width-1, wall);
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
            printf("Ivalid number!\n\n");
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
    printf("\n");
    *height = get_valid_int("Please type in border height: ", MAX_HEIGHT);
}

void play_snake()
// main function to play the game
{
    // ask user for size of screen
    int width, height;
    get_size(&width, &height);
    // initialize
    initscr();
    clear();
    draw_borders(width, height);
    refresh();
    getch();
    endwin();
    clear();

}

