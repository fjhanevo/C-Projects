#include <ncurses.h>
#include "snake.h"

int main(void)
{
    initscr();                  // initialize
    snake_test();               // print something
    refresh();                  // print it on the real screen
    getch();                    // wait for user input
    endwin();                   // end 

    return 0;
}
