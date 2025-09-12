#include <ncurses.h>
#include <stdlib.h>
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

    while (1) {
        nodelay(stdscr, TRUE);
        play_snake(&state);

        // clear possible trailing input
        flushinp();
        clear();
        mvprintw(0, 0, "Game over! Score: %d", state.score);
        mvprintw(2, 0, "Play again? (y/N)");
        refresh();

        nodelay(stdscr, FALSE);
        int opt = getch();
        if (opt != 'y' && opt != 'Y') break;

    }
    endwin();
    return 0;
}
