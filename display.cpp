#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include "display.h"
#include "rocket.h"
#include "scoreboard.h"

using namespace std;

int startMenu();
int playerguide();
int credits();
int name();


int startMenu() {

    // Start menu dimensions //
    WINDOW* menu_Display = newwin(36, 60, 0, 0); 
    box(menu_Display, 0, 0);
    wrefresh(menu_Display);

    // Start menu options // 
    string menu0[5]= {"PLAY","PLAYER GUIDE","SCOREBOARD","CREDITS","QUIT"};

    // User Input //
    int choice;
    
    // Selected //
    int selected=0;

    while(TRUE) {
                                               

        mvwprintw(menu_Display, 1,2,"                                                         ");
        mvwprintw(menu_Display, 2,2,"                                                         ");
        mvwprintw(menu_Display, 3,2,"                                                         "); 
        mvwprintw(menu_Display, 4,2,"         _____   ____   _____ _  ________ _______        ");
        mvwprintw(menu_Display, 5,2,"        |  __ \\ / __ \\ / ____| |/ /  ____|__   __|       ");
        mvwprintw(menu_Display, 6,2,"        | |__) | |  | | |    | ' /| |__     | |          ");
        mvwprintw(menu_Display, 7,2,"        |  _  /| |  | | |    |  < |  __|    | |          ");
        mvwprintw(menu_Display, 8,2,"        | | \\ \\| |__| | |____| . \\| |____   | |          ");
        mvwprintw(menu_Display, 9,2,"        |_|  \\_ \\____/\\___ __|_|\\_\\______|  |_|          ");
        mvwprintw(menu_Display, 10,2,"                                                         ");
        mvwprintw(menu_Display, 11,2,"                                                         ");
        mvwprintw(menu_Display, 12,2,"                                                         ");
        mvwprintw(menu_Display, 13,2,"   _____            __  __ _____        _____ ______     ");
        mvwprintw(menu_Display, 14,2,"  |  __ \\     /\\   |  \\/  |  __ \\ /\\   / ____|  ____|    ");
        mvwprintw(menu_Display, 15,2,"  | |__) |   /  \\  | \\  / | |__) /  \\ | |  __| |__       ");
        mvwprintw(menu_Display, 16,2,"  |  _  /   / /\\ \\ | |\\/| |  ___/ /\\ \\| | |_ |  __|      ");
        mvwprintw(menu_Display, 17,2,"  | | \\ \\  / ____ \\| |  | | |  / ____ \\ |__| | |____     ");
        mvwprintw(menu_Display, 18,2,"  |_|  \\_\\/_/    \\_\\_|  |_|_| /_/    \\_\\_____|______|    ");
        mvwprintw(menu_Display, 19,2,"                                                         ");
        mvwprintw(menu_Display, 20,2,"                                                         ");
        mvwprintw(menu_Display, 21,2,"                                                         ");
       
        // Menu Design // 

        for(int i=0;i<5;i++) {
            wattron(menu_Display, A_BOLD);

            if(i==selected) {
                wattron(menu_Display, A_REVERSE);
            }

            mvwprintw(menu_Display, 25+i+1, ((60-menu0[i].length())/2), menu0[i].c_str());//printing options
            wattroff(menu_Display, A_REVERSE);//de-highlightinging the non selected options
        }
        // User Input //
        choice = getch();

        // Hover Over Highlights //
        switch(choice) {
            case KEY_UP:
                selected--;
                // Menu Boundary //
                if(selected<0)
                    selected=4;
                break;
            case KEY_DOWN:
                selected++;
                // Menu Boundary //
                if(selected>4)
                    selected=0;
                break;
            default:
                break;
        }
        // Check User Input //
        if(choice==10) { 
            break;
        }
        // End //
        wrefresh(menu_Display);
    }
    // Select //
    if(selected==0) {
        name();
    } else if(selected==1) {
        playerguide();
    } else if(selected==2) {
        highscores();
    } else if(selected==3) {
        credits();
    }

    return 0;
}

int playerguide() {
    // player guide window //
    WINDOW* playerguidewindow = newwin(26, 60, 0, 0); 
    box(playerguidewindow, 0, 0);
    wrefresh(playerguidewindow);
    int choice;
    int selected3=1;
    for(;;) {   
        // player guide //
        mvwprintw(playerguidewindow, 5, 13, "1.");
        mvwprintw(playerguidewindow, 5, 15, "Use the left and right arrow keys to");
        mvwprintw(playerguidewindow, 6, 15, "move the Rocket and [A] key to shoot.");
        mvwprintw(playerguidewindow, 8, 13, "2.");
        mvwprintw(playerguidewindow, 8, 15, "The goal is to destroy enemies with");
        mvwprintw(playerguidewindow, 9, 15, "your missiles.");
        mvwprintw(playerguidewindow, 11, 13, "3.");
        mvwprintw(playerguidewindow, 11, 15, "Earn points each time a missile");
        mvwprintw(playerguidewindow, 12, 15, "hits an enemy.");
        mvwprintw(playerguidewindow, 14, 13, "4.");
        mvwprintw(playerguidewindow, 14, 15, "You have 5 Lives to accumulate");
        mvwprintw(playerguidewindow, 15, 15, "as many points as possible.");
        mvwprintw(playerguidewindow, 17, 13, "5.");
        mvwprintw(playerguidewindow, 17, 15, "Your score is the total number of");
        mvwprintw(playerguidewindow, 18, 15, "enemies defeated.");
        mvwprintw(playerguidewindow, 20, 13, "6.");
        mvwprintw(playerguidewindow, 20, 15, "And most importantly- ENJOY!!");
        
        // Text format // 

        // making all options bold //
        wattron(playerguidewindow, A_BOLD);
        wattron(playerguidewindow, A_REVERSE);
        mvwprintw(playerguidewindow, 24, 45, "BACK TO MENU->");
        wattroff(playerguidewindow, A_REVERSE);
        wrefresh(playerguidewindow);
        // user input //
        choice = getch();
        if(choice==10) {
            break;
        }
    }
    // going back to main menu 
    startMenu();
    return 0;
}

int credits() {
    // credits window //
    WINDOW* end_window = newwin(26, 60, 0, 0); 
    box(end_window, 0, 0);
    wrefresh(end_window);

    // input //
    int choice;

    // credits //
    mvwprintw(end_window, 13, 23, "Divyansh Tulsyan");
    mvwprintw(end_window, 14, 23, " ");
    mvwprintw(end_window, 15, 23, "Jaehun Chun");
    mvwprintw(end_window, 16, 23, " ");
    mvwprintw(end_window, 17, 23, "Meeth Jaswani");
    mvwprintw(end_window, 18, 23, " ");
    mvwprintw(end_window, 19, 23, "Shreyansh Mishra");
    mvwprintw(end_window, 20, 23, " ");
    mvwprintw(end_window, 21, 23, "Cheung HonLung");

    for(;;) {
        // credits display //
        mvwprintw(end_window, 1,2,"                                                         ");
        mvwprintw(end_window, 2,2,"                                                         ");
        mvwprintw(end_window, 3,2,"     ________                     _   _   __             ");
        mvwprintw(end_window, 4,2,"    /   __   |                   | | (_) |  |            ");
        mvwprintw(end_window, 5,2,"    |  |  |__| _ ___   ___    ___| |  _  |  |   _____    ");
        mvwprintw(end_window, 6,2,"    |  |  ___ | ' __| / _ \\  /  _  | | | | __| / ____|   ");
        mvwprintw(end_window, 7,2,"    |  | |   ||  /   | ___/ |  (_| | | | | |   \\__  \\    ");
        mvwprintw(end_window, 8,2,"     \\_______||__|    \\___|  \\__,__| |_| \\___| |____/  ");
        mvwprintw(end_window, 9,2,"                                                         ");
        mvwprintw(end_window, 10,2,"                                                         ");
        mvwprintw(end_window, 11,2,"                                                         ");
        
      
        // window formatting //

        wattron(end_window, A_BOLD);
        wattron(end_window,A_REVERSE);
        mvwprintw(end_window, 24, 24, "BACK TO HOME");
        wattroff(end_window,A_REVERSE);
        
        
        // input //
        choice=getch();
        if(choice==10) {
            break;
        }
        wrefresh(end_window);
    }
    // back to main menu //
    startMenu();
    return 0;
}

int name() {

    // Input Dimensions //
    WINDOW* win = newwin(36, 60, 0, 0);

    box(win, 0, 0);

    // Play //

    string play_option= "PLAY GAME";

    // Design //

    wattron(win, A_BOLD);

    wattron(win, A_REVERSE);

    // Plays //

    mvwprintw(win, 19, ((60-play_option.length())/2), play_option.c_str());
    
    wattroff(win, A_REVERSE);


    // Store player name //
    string player_alias;
    // Input until 'Enter' //
    int ch;
    int char_limit = 0;
    
    // Enter Name and edit //

    mvwprintw(win, 11, 21, "Enter your name:");
    mvwprintw(win, 14, 23, "-----------");
    while ((ch = wgetch(win)) != '\n') {
        
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (!player_alias.empty()) {
                player_alias.erase(player_alias.size() - 1, 1);
                mvwprintw(win, 13, 25, "       ");
                mvwprintw(win, 13, 25, player_alias.c_str());
                char_limit--;
            }
        } else if (isprint(ch)) {
            // char  limit = 7 //
            if (char_limit!=7){
                player_alias += ch;
                mvwprintw(win, 13, 25, player_alias.c_str()); 
                char_limit++;
            }
            

        }
        // Refresh //
        wrefresh(win);
        
    }
    // default name //
    if(player_alias.empty()) {
        player_alias = "*no_name*";
    }
    game(player_alias);
    return 0;
}   

int gameEnd(string player_alias, int player_score) {

    // gameEnd window //
    WINDOW* end_window = newwin(36, 60, 0, 0); 
    box(end_window, 0, 0);
    wrefresh(end_window);

    // store in file at game end // 
    file_input(player_alias, player_score);

    int choice;
    for(;;) {
        mvwprintw(end_window, 1,2,"                                                         ");
        mvwprintw(end_window, 2,2,"                                                         ");
        mvwprintw(end_window, 3,2,"                                                         "); 
        mvwprintw(end_window, 4,2,"                                                         ");
        mvwprintw(end_window, 5,2,"            ______                                       ");
        mvwprintw(end_window, 6,2,"           /  ____|                                      ");
        mvwprintw(end_window, 7,2,"          |  |  ___   _____  _________     ___           ");
        mvwprintw(end_window, 8,2,"          |  | |_  | /  _  | |  _   _ \\  / _  \\        ");
        mvwprintw(end_window, 9,2,"          |  |__|  | | (_| | | | | | | ||  __/           ");
        mvwprintw(end_window, 10,2,"          \\_______|  \\____| |_| |_| |_| \\____|       ");
        mvwprintw(end_window, 11,2,"                                                        ");
        mvwprintw(end_window, 12,2,"                                                        ");
        mvwprintw(end_window, 13,2,"                                                        ");
        mvwprintw(end_window, 14,2,"                                                        ");
        mvwprintw(end_window, 15,2,"              ______                                    ");
        mvwprintw(end_window, 16,2,"            /  __  \\                                   ");
        mvwprintw(end_window, 17,2,"           |  |  |  | __    __  ___   __ ___            ");
        mvwprintw(end_window, 18,2,"           |  |  |  | \\ \\  / / / _ \\ | '___|         ");
        mvwprintw(end_window, 19,2,"           |  `--'  |  \\ \\/ / |  __/ | /              ");
        mvwprintw(end_window, 20,2,"            \\______/    \\__/   \\___| |_|             ");
        mvwprintw(end_window, 21,2,"                                                        ");
        mvwprintw(end_window, 22,2,"                                                        "); 
        mvwprintw(end_window, 23,2,"                                                        ");
        mvwprintw(end_window, 24,2,"                                                        "); 
        mvwprintw(end_window, 25,2,"                                                        "); 
        mvwprintw(end_window, 26,2,"                                                        ");
        mvwprintw(end_window, 27,2,"                                                        ");
        
        // menu formatting //
        wattron(end_window, A_BOLD);
        wattron(end_window,A_REVERSE);
        mvwprintw(end_window, 30, 24, "BACK TO HOME");
        wattroff(end_window,A_REVERSE);

        // input //
        choice=getch();

        if(choice==10) {
            break;
        }
        wrefresh(end_window);
    }
    startMenu();
    return 0;
}
