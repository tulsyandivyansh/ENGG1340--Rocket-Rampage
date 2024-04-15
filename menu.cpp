#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include "menu.h"
#include "game.h"
#include "highscore.h"

using namespace std;

int mainmenu();
int inputName();
int instructions1();
int credits();

int mainmenu() {

    //main menu window initialization (rows,cols,y,x)
    WINDOW* menuWindow = newwin(26, 60, 0, 0); 
    box(menuWindow, 0, 0);
    wrefresh(menuWindow);

    //main menu options
    string menu1[5]= {"PLAY GAME","HOW TO PLAY","HIGH SCORE","CREDITS","QUIT"};
    //variable to get user input
    int choice;
    //variable to store the current option selected
    int highlight=0;

    while(TRUE) {
        //printing main menu screen
      mvwprintw(menuWindow, 1, 2, "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
      mvwprintw(menuWindow, 2, 2, "*                                                         *");
      mvwprintw(menuWindow, 3, 2, "*    M       M  IIIII  SSSSS  SSSSS  IIIII  L      EEEEE  *");
      mvwprintw(menuWindow, 4, 2, "*    MM     MM    I    S      S        I    L      E      *");
      mvwprintw(menuWindow, 5, 2, "*    M M   M M    I     SSS    SSS     I    L      EEEE   *");
      mvwprintw(menuWindow, 6, 2, "*    M  M M  M    I        S      S    I    L      E      *");
      mvwprintw(menuWindow, 7, 2, "*    M   M   M  IIIII  SSSSS  SSSSS  IIIII  LLLLL  EEEEE  *");
      mvwprintw(menuWindow, 8, 2, "*                                                         *");
      mvwprintw(menuWindow, 9, 2, "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");

        for(int i=0;i<5;i++) {
            //making all options bold
            wattron(menuWindow, A_BOLD);
            //highlighting the selected choice
            if(i==highlight) {
                wattron(menuWindow, A_REVERSE);
            }
            //printing the choices
            mvwprintw(menuWindow, 18+i+1, ((60-menu1[i].length())/2), menu1[i].c_str());//printing options
            wattroff(menuWindow, A_REVERSE);//de-highlighting the non selected options
        }
        //getting user input
        choice = getch();
        //changing highlighted option according to user option
        switch(choice) {
            case KEY_UP:
                highlight--;
                //checking whether the choice is going out of bounds
                if(highlight<0)
                    highlight=4;
                break;
            case KEY_DOWN:
                highlight++;
                //checking whether the choice is going out of bounds
                if(highlight>4)
                    highlight=0;
                break;
            default:
                break;
        }
        //checking whether enter is pressed
        if(choice==10) { 
            break;
        }
        //refresh window
        wrefresh(menuWindow);
    }
    //traversing to the screen as per the user's choice
    if(highlight==0) {
        inputName();
    } else if(highlight==1) {
        instructions1();
    } else if(highlight==2) {
        highscores();
    } else if(highlight==3) {
        credits();
    }

    return 0;
}

int inputName() {

    // input window initialization (rows, columns, y, x)
    WINDOW* win = newwin(26, 60, 0, 0);

    // Draw a box around the window
    box(win, 0, 0);


    //creating a play button:

    //create a string that stores text displayed on the button
    string playButton= "PLAY GAME";

    //makes text bold 
    wattron(win, A_BOLD);

    //highlighting the play button
    wattron(win, A_REVERSE);

    //prints play button
    mvwprintw(win, 19, ((60-playButton.length())/2), playButton.c_str());
    
    //turn off highlighting
    wattroff(win, A_REVERSE);


    // Create a string to store the player name
    string playerName;
    // Get input from the user until they press enter
    int ch;
    //declare and initialise variable to count and subsequently limit character count for name
    int char_limit = 0;
    //print a prompt to enter name
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
    int highlight3=1;
    for(;;) {   
        //instructions on how to play the game
        mvwprintw(instrucionWindow, 5, 13, "1.");
        mvwprintw(instrucionWindow, 5, 15, "Press the left and right arrow");
        mvwprintw(instrucionWindow, 6, 15, "to move the missile.");
        mvwprintw(instrucionWindow, 8, 13, "2.");
        mvwprintw(instrucionWindow, 8, 15, "Your objective is to kill the");
        mvwprintw(instrucionWindow, 9, 15, "enemies using the missile.");
        mvwprintw(instrucionWindow, 11, 13, "3.");
        mvwprintw(instrucionWindow, 11, 15, "You will get points each time");
        mvwprintw(instrucionWindow, 12, 15, "missile hits the enemies.");
        mvwprintw(instrucionWindow, 14, 13, "4.");
        mvwprintw(instrucionWindow, 14, 15, "You have a time limit for 1 minute.");
        mvwprintw(instrucionWindow, 16, 13, "5.");
        mvwprintw(instrucionWindow, 16, 15, "During 1 minute, the number of");
        mvwprintw(instrucionWindow, 17, 15, "enemies you killed is your score.");
        mvwprintw(instrucionWindow, 20, 22, "Happy gaming!");
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
    mainmenu();
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
    mvwprintw(endWindow, 13, 24, "Cheung HonLung");
    mvwprintw(endWindow, 14, 23, " ");
    mvwprintw(endWindow, 15, 23, "Divyansh Tulsyan");
    mvwprintw(endWindow, 16, 23, " ");
    mvwprintw(endWindow, 17, 23, "Jaehun Chun");
    mvwprintw(endWindow, 18, 23, " ");
    mvwprintw(endWindow, 19, 22, "Meeth Jaswani");
    mvwprintw(endWindow, 20, 23, " ");
    mvwprintw(endWindow, 21, 23, "Shrey");

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
    mainmenu();
    return 0;
}
    

int gameOver(string playerName, int playerScore) {
    //gameover window initialization (rows,cols,y,x)
    WINDOW* endWindow = newwin(26, 60, 0, 0); 
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
        //refreshing window
        wrefresh(endWindow);
    }
    mainmenu();
    return 0;
}
