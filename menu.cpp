#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include "menu.h"
#include "game.h"
#include "highscore.h"

using namespace std;

int startMenu();
int name();
int instructions1();
int credits();

int startMenu() {

    // Start menu dimensions //
    WINDOW* menuWindow = newwin(36, 60, 0, 0); 
    box(menuWindow, 0, 0);
    wrefresh(menuWindow);

    // Start menu options // 
    string menu0[5]= {"PLAY","PLAYER GUIDE","HIGH SCORE","CREDITS","QUIT"};

    // User Input //
    int choice;
    
    // Selected //
    int selected=0;

    while(TRUE) {
                                               

        mvwprintw(menuWindow, 1,2,"* * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        mvwprintw(menuWindow, 2,2,"*   *   *   *   *   *   *   *   *   *   *   *    *      *");
        mvwprintw(menuWindow, 3,2,"*      _____   ____   _____ _  ________ _______         *");      
        mvwprintw(menuWindow, 4,2,"*     |  __ \\ / __ \\ / ____| |/ /  ____|__   __|        *");    
        mvwprintw(menuWindow, 5,2,"*     | |__) | |  | | |    | ' /| |__     | |           *");     
        mvwprintw(menuWindow, 6,2,"*     |  _  /| |  | | |    |  < |  __|    | |           *");    
        mvwprintw(menuWindow, 7,2,"*     | | \\ \\| |__| | |____| . \\| |____   | |           *");    
        mvwprintw(menuWindow, 8,2,"*     |_|  \\_\\____/ \\___ __|_|\\_\\______|  |_|           *");    
        mvwprintw(menuWindow, 9,2,"*  _____            __  __ _____        _____ ______    *");
        mvwprintw(menuWindow, 10,2,"* |  __ \\     /\\   |  \\/  |  __ \\ /\\   / ____|  ____|   *");
        mvwprintw(menuWindow, 11,2,"* | |__) |   /  \\  | \\  / | |__) /  \\ | |  __| |__      *");
        mvwprintw(menuWindow, 12,2,"* |  _  /   / /\\ \\ | |\\/| |  ___/ /\\ \\| | |_ |  __|     *"); 
        mvwprintw(menuWindow, 13,2,"* | | \\ \\  / ____ \\| |  | | |  / ____ \\ |__| | |____    *");
        mvwprintw(menuWindow, 14,2,"* |_|  \\_\\/_/    \\_\\_|  |_|_| /_/    \\_\\_____|______|   *");
        mvwprintw(menuWindow, 15,2,"*  *  *   *   *   *     *     *   *     *   *   *  *  * *");
        mvwprintw(menuWindow, 16,2,"* *  *   *  *   *    *     *    *    *    *   *  *  *  **"); 
        mvwprintw(menuWindow, 17,2,"* * * * * * * * * * * * * * * * * * * * * * * * * * * * *");  
       
        // Menu Design // 

        for(int i=0;i<5;i++) {
            wattron(menuWindow, A_BOLD);

            if(i==selected) {
                wattron(menuWindow, A_REVERSE);
            }

            mvwprintw(menuWindow, 18+i+1, ((60-menu0[i].length())/2), menu0[i].c_str());//printing options
            wattroff(menuWindow, A_REVERSE);//de-highlightinging the non selected options
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
        wrefresh(menuWindow);
    }
    // Select //
    if(selected==0) {
        name();
    } else if(selected==1) {
        instructions1();
    } else if(selected==2) {
        highscores();
    } else if(selected==3) {
        credits();
    }

    return 0;
}

int name() {

    // Input Dimensions //
    WINDOW* win = newwin(36, 60, 0, 0);

    box(win, 0, 0);

    // Play //
    string playButton= "PLAY GAME";

    // Design //
    wattron(win, A_BOLD);

    wattron(win, A_REVERSE);

    // Plays //
    mvwprintw(win, 19, ((60-playButton.length())/2), playButton.c_str());
    
    wattroff(win, A_REVERSE);


    // Store player name //
    string playerName;
    // Input until 'Enter' //
    int ch;
    // declare and initialise variable to count and subsequently limit character count for name
    int char_limit = 0;
    // print a prompt to enter name
    mvwprintw(win, 11, 21, "Enter your name:");
    mvwprintw(win, 14, 23, "-----------");
    while ((ch = wgetch(win)) != '\n') {
        
        if (ch == KEY_BACKSPACE || ch == 127) {
            // Handle backspace key
            if (!playerName.empty()) {
                playerName.erase(playerName.size() - 1, 1);
                mvwprintw(win, 13, 25, "       ");
                mvwprintw(win, 13, 25, playerName.c_str());
                //account for backspace in character count
                char_limit--;
            }
        } else if (isprint(ch)) {
            // Handle printable characters
            //set character count limit to 7
            if (char_limit!=7){
                playerName += ch;
                mvwprintw(win, 13, 25, playerName.c_str()); 
                //account for increment in character count
                char_limit++;
            }
            

        }
        //refresh window
        wrefresh(win);
        
    }
    //setting default name to "NONAME"
    if(playerName.empty()) {
        playerName = "NONAME";
    }
    game(playerName);
    return 0;
}

int instructions1() {
    //instruction window initialization (rows,cols,y,x)
    WINDOW* instrucionWindow = newwin(26, 60, 0, 0); 
    box(instrucionWindow, 0, 0);
    wrefresh(instrucionWindow);
    int choice;
    int selected3=1;
    for(;;) {   
        //instructions on how to play the game
        mvwprintw(instrucionWindow, 5, 13, "1.");
        mvwprintw(instrucionWindow, 5, 15, "Use the left and right arrow keys to");
        mvwprintw(instrucionWindow, 6, 15, "move the missile.");
        mvwprintw(instrucionWindow, 8, 13, "2.");
        mvwprintw(instrucionWindow, 8, 15, "The goal is to destroy enemies with");
        mvwprintw(instrucionWindow, 9, 15, "your missile.");
        mvwprintw(instrucionWindow, 11, 13, "3.");
        mvwprintw(instrucionWindow, 11, 15, "Earn points each time a missile");
        mvwprintw(instrucionWindow, 12, 15, "hits an enemy.");
        mvwprintw(instrucionWindow, 14, 13, "4.");
        mvwprintw(instrucionWindow, 14, 15, "You have 1 minute to accumulate");
        mvwprintw(instrucionWindow, 16, 13, "as many points as possible.");
        mvwprintw(instrucionWindow, 16, 15, "5.");
        mvwprintw(instrucionWindow, 17, 15, "Your score is the total number of");
        mvwprintw(instrucionWindow, 20, 22, "enemies defeated with each level.");
        //making all options bold 
        wattron(instrucionWindow, A_BOLD);
        //highlighting "BACK TO MENU" option
        wattron(instrucionWindow, A_REVERSE);
        //printing "BACK TO MENU->" option
        mvwprintw(instrucionWindow, 24, 45, "BACK TO MENU->");
        //switching off the highlight function
        wattroff(instrucionWindow, A_REVERSE);
        //refresh window
        wrefresh(instrucionWindow);
        //getting user input
        choice = getch();
        //checking whether user pressed enter
        if(choice==10) {
            break;
        }
    }
    //going back to main menu
    startMenu();
    return 0;
}

int credits() {
    //credits window initialization (rows,cols,y,x)
    WINDOW* endWindow = newwin(26, 60, 0, 0); 
    box(endWindow, 0, 0);
    wrefresh(endWindow);

    //variable to get user input
    int choice;

    // Adding the names under the ASCII art
    mvwprintw(endWindow, 13, 24, "Divyansh Tulsyan");
    mvwprintw(endWindow, 14, 23, " ");
    mvwprintw(endWindow, 15, 23, "Jaehun Chun");
    mvwprintw(endWindow, 16, 23, " ");
    mvwprintw(endWindow, 17, 23, "Meeth Jaswani");
    mvwprintw(endWindow, 18, 23, " ");
    mvwprintw(endWindow, 19, 22, "Shreyansh Mishra");
    mvwprintw(endWindow, 20, 23, " ");
    mvwprintw(endWindow, 21, 23, "Cheung HonLung");

    for(;;) {
        //printing "Credits" on the screen
        mvwprintw(endWindow, 1,2,"* * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        mvwprintw(endWindow, 2,2,"*   *   *   *   *   *   *   *   *   *   *   *   *   *   *");
        mvwprintw(endWindow, 3,2,"*  ________       *     *   *  *_   _*  __  *  * *      *");
        mvwprintw(endWindow, 4,2,"* /   __   |  *    *  *   *    | | (_) |  |   *    * *  *");
        mvwprintw(endWindow, 5,2,"* |  |  |__| _ ___   ___    ___| |  _  |  |   _____     *");
        mvwprintw(endWindow, 6,2,"* |  |  ___ | ' __| / _ \\  /  _  | | | | __| / ____| *  *");
        mvwprintw(endWindow, 7,2,"* |  | |   ||  /   | ___/ |  (_| | | | | |   \\__  \\ *   *");
        mvwprintw(endWindow, 8,2,"*  \\_______||__|    \\___|  \\__,__| |_| \\___| |____/  *  *");
        mvwprintw(endWindow, 9,2,"*   *     *     *     *     *     *     *     *     *   *");
        mvwprintw(endWindow, 10,2,"*     *     *     *     *     *     *     *     *    *  *");
        mvwprintw(endWindow, 11,2,"* * * * * * * * * * * * * * * * * * * * * * * ** * * *  *");
        
        // printing BACK TO HOME option
        //making all options bold
        wattron(endWindow, A_BOLD);
        //highlighting BACK TO HOME option
        wattron(endWindow,A_REVERSE);
        mvwprintw(endWindow, 24, 24, "BACK TO HOME");
        wattroff(endWindow,A_REVERSE);
        //switching off highlight function
        
        //getting user input
        choice=getch();

        //if user presses enter break
        if(choice==10) {
            break;
        }
        wrefresh(endWindow);
    }
    //going back to the main menu page
    startMenu();
    return 0;
}
    

int gameOver(string playerName, int playerScore) {
    //gameover window initialization (rows,cols,y,x)
    WINDOW* endWindow = newwin(36, 60, 0, 0); 
    box(endWindow, 0, 0);
    wrefresh(endWindow);

    //sending player name and player score to store it in the file for high score screen
    InputToFile(playerName, playerScore);

    //getting user input
    int choice;
    for(;;) {
        //printing "Game Over" on the screen
        mvwprintw(endWindow, 1,2,"* * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        mvwprintw(endWindow, 2,2,"*   *   *   *   *   *   *   *   *   *   *   *   *   *   *");
        mvwprintw(endWindow, 3,2,"       *    ______    *       *         *     *    *  *");
        mvwprintw(endWindow, 4,2,"   *     * /  ____|      *      *    *     *     *    *");
        mvwprintw(endWindow, 5,2,"  *    *  |  |  ___   _____  _________     ___     *  *");
        mvwprintw(endWindow, 6,2,"    *   * |  | |_  | /  _  | |  _   _ \\  / _  \\  *    *");
        mvwprintw(endWindow, 7,2," *       *|  |__|  | | (_| | | | | | | ||  __/    *   *");
        mvwprintw(endWindow, 8,2," *     *   \\_______|  \\____| |_| |_| |_| \\____|    *  *");
        mvwprintw(endWindow, 9,2,"    *     *     *     *     *     *     *     *     *   *");
        mvwprintw(endWindow, 10,2,"*     *     *     *     *     *     *     *     *     *");
        mvwprintw(endWindow, 11,2,"  *      *   ______   *      *     *   *      *    * *");
        mvwprintw(endWindow, 12,2,"     *    * /  __  \\   *      *         *       *   *");
        mvwprintw(endWindow, 13,2,"  *     *  |  |  |  | __    __  ___   __ ___  *      *");
        mvwprintw(endWindow, 14,2,"     *    *|  |  |  | \\ \\  / / / _ \\ | '___|   *    *");
        mvwprintw(endWindow, 15,2,"         * |  `--'  |  \\ \\/ / |  __/ | /    *     *  *");
        mvwprintw(endWindow, 16,2," *     *    \\______/    \\__/   \\___| |_|   *   *    *");
        mvwprintw(endWindow, 17,2,"*     *     *     *     *     *     *     *     *    * *");
        mvwprintw(endWindow, 18,2,"   *     *     *     *     *     *     *     *    *    *"); 
        mvwprintw(endWindow, 19,2,"*     *     *     *     *     *     *     *     *    * *"); 
        mvwprintw(endWindow, 20,2,"   *     *     *     *     *     *     *     *    *    *");
        mvwprintw(endWindow, 21,2,"* * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        
        //making "BACK TO HOME" bold
        wattron(endWindow, A_BOLD);
        //highlighting "BACK TO HOME" option
        wattron(endWindow,A_REVERSE);
        mvwprintw(endWindow, 24, 27, "BACK TO HOME");
        wattroff(endWindow,A_REVERSE);
        //switching off the highlight function

        //geting input from user
        choice=getch();

        //checking whether the user pressed enter
        if(choice==10) {
            break;
        }
        // refreshing window
        wrefresh(endWindow);
    }
    startMenu();
    return 0;
}
