#include <ncurses.h>

int main(void)
{
    initscr();                  // initialize
    printw("Hello world");      // print hello world
    refresh();                  // print it on the real screen
    getch();                    // wait for user input
    endwin();                   // end 

    return 0;
}
