#include <ncurses.h>

#include "display.h"

int main() {

    // curses //
    initscr();
    
    // curses settings //
    cbreak(); 

    keypad(stdscr, TRUE);

    noecho(); 

    curs_set(0); 

    refresh(); 

    nodelay(stdscr, TRUE); 

    // start game //
    startMenu();

    // clear terminal settings //
    endwin();

    return 0;
}
