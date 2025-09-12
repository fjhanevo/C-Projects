#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "utils.h"
int main(void)
{
    GameState state; 
    srand(time(NULL));

    get_size(&state.width, &state.height);

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    bool is_playing = true;
    while (is_playing) {
        nodelay(stdscr, TRUE);
        play_snake(&state);

        // clear possible trailing input
        clear();
        mvprintw(0, 0, "Game over! Score: %d", state.score);
        mvprintw(2, 0, "Play again? (y/N)");
        refresh();

        nodelay(stdscr, FALSE);
        int ch;
        while ((ch = getch()) != EOF) {
            if (ch == 'y' || ch == 'Y') {
                break;
            } else if (ch == 'n' || ch == 'N') {
                is_playing = false;
                break;
            }
        }
    }
    endwin();
    return 0;
}
