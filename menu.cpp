#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include "menu.h"
#include "game.h"
#include "highscore.h"

using namespace std;

int displayMainMenu();
int promptForName();
int showInstructions();
int displayCredits();

// Function to display the main menu using ncurses
int displayMainMenu() {
    // Create a new window for the menu
    WINDOW* mainWin = newwin(26, 60, 0, 0);
    // Draw a box around the window
    box(mainWin, 0, 0);
    wrefresh(mainWin);

    // Array of menu options
    string options[] = {"PLAY GAME", "HOW TO PLAY", "HIGH SCORE", "CREDITS", "QUIT"};
    // Current menu selection
    int currentSelection = 0;
    int userInput;

    while(true) {
        // Displaying the game title and decoration
      mvwprintw(mainWin, 1, 2, "* * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
      mvwprintw(mainWin, 2, 2, "*                                                         *");
      mvwprintw(mainWin, 3, 2, "*    M       M  IIIII  SSSSS  SSSSS  IIIII  L      EEEEE  *");
      mvwprintw(mainWin, 4, 2, "*    MM     MM    I    S      S        I    L      E      *");
      mvwprintw(mainWin, 5, 2, "*    M M   M M    I     SSS    SSS     I    L      EEEE   *");
      mvwprintw(mainWin, 6, 2, "*    M  M M  M    I        S      S    I    L      E      *");
      mvwprintw(mainWin, 7, 2, "*    M   M   M  IIIII  SSSSS  SSSSS  IIIII  LLLLL  EEEEE  *");
      mvwprintw(mainWin, 8, 2, "*                                                         *");
      mvwprintw(mainWin, 9, 2, "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");

        // Iterate over options to display them
        for(int i = 0; i < 5; ++i) {
            // Apply bold font style
            wattron(mainWin, A_BOLD);
            // Highlight the current selection
            if(i == currentSelection) {
                wattron(mainWin, A_REVERSE);
            }
            // Display the option centered
            mvwprintw(mainWin, 18 + i + 1, (60 - options[i].length()) / 2, options[i].c_str());
            wattroff(mainWin, A_REVERSE); // Remove highlight from other options
        }

        // Get user input
        userInput = getch();

        // Update the current selection based on user input
        switch(userInput) {
            case KEY_UP:
                currentSelection = (currentSelection - 1 + 5) % 5;
                break;
            case KEY_DOWN:
                currentSelection = (currentSelection + 1) % 5;
                break;
            default:
                break;
        }

        // Check if Enter key is pressed
        if(userInput == 10) { 
            break; // Exit the loop
        }

        // Refresh the window to update the menu display
        wrefresh(mainWin);
    }

    // Execute the action based on selected option
    switch(currentSelection) {
        case 0: 
            promptForName();
            break;
        case 1: 
            showInstructions();
            break;
        case 2:
            highscores();
            break;
        case 3:
            displayCredits();
            break;
        case 4:
            return 0; // Quit the application
    }

    return 0;
}


int promptForName() {
    // Initialize the window for name input
    WINDOW* inputWindow = newwin(26, 60, 0, 0);

    // Draw a border around the window
    box(inputWindow, 0, 0);

    // Declare a string for the play button label
    string playButtonLabel = "PLAY GAME";

    // Make the play button text bold and highlighted
    wattron(inputWindow, A_BOLD);
    wattron(inputWindow, A_REVERSE);
    mvwprintw(inputWindow, 19, (60 - playButtonLabel.length()) / 2, playButtonLabel.c_str());
    wattroff(inputWindow, A_REVERSE);  // Turn off highlight after drawing the button

    // String to collect the player's name
    string playerName;

    // Print a prompt for the player to enter their name
    mvwprintw(inputWindow, 11, 21, "Enter your name:");
    mvwprintw(inputWindow, 14, 23, "-----------");

    // Variables to handle character input and impose character limit
    int charInput;
    int maxChars = 7;

    while ((charInput = wgetch(inputWindow)) != '\n') { // Continue until 'Enter' key is pressed
        if (charInput == KEY_BACKSPACE || charInput == 127) {
            // Handle backspace operation
            if (!playerName.empty()) {
                playerName.pop_back(); // Remove last character
                mvwprintw(inputWindow, 13, 25, "       "); // Clear previous input
                mvwprintw(inputWindow, 13, 25, playerName.c_str()); // Update the display
            }
        } else if (isprint(charInput) && playerName.length() < maxChars) {
            // Add character to playerName if it doesn't exceed the limit
            playerName.push_back(charInput);
            mvwprintw(inputWindow, 13, 25, playerName.c_str());
        }
        // Refresh window after each input to update the display
        wrefresh(inputWindow);
    }

    // Use default name if no name was entered
    if (playerName.empty()) {
        playerName = "NONAME";
    }

    // Pass the playerName to the game function
    game(playerName);
    return 0;
}


int showInstructions() {
    // Initialize the window for game instructions
    WINDOW* instructionWin = newwin(26, 60, 0, 0);
    box(instructionWin, 0, 0);  // Draw a box around the window
    wrefresh(instructionWin);   // Refresh to show the box

    // Loop indefinitely until 'Enter' is pressed
    while(true) {
        // Detailed instructions on how to play the game
        mvwprintw(instructionWin, 5, 13, "1. Use the left and right arrow keys to");
        mvwprintw(instructionWin, 6, 13, "   move the missile.");
        mvwprintw(instructionWin, 8, 13, "2. The goal is to destroy enemies with");
        mvwprintw(instructionWin, 9, 13, "   your missile.");
        mvwprintw(instructionWin, 11, 13, "3. Earn points each time a missile");
        mvwprintw(instructionWin, 12, 13, "   hits an enemy.");
        mvwprintw(instructionWin, 14, 13, "4. You have 1 minute to accumulate");
        mvwprintw(instructionWin, 15, 13, "   as many points as possible.");
        mvwprintw(instructionWin, 17, 13, "5. Your score is the total number of");
        mvwprintw(instructionWin, 18, 13, "   enemies defeated within the time.");
        mvwprintw(instructionWin, 20, 22, "Enjoy the game!");

        // Display "BACK TO MENU" option with highlighting
        wattron(instructionWin, A_BOLD);  // Apply bold to the text
        wattron(instructionWin, A_REVERSE);  // Highlight the text
        mvwprintw(instructionWin, 24, 45, "BACK TO MENU->");
        wattroff(instructionWin, A_REVERSE);  // Turn off highlight

        // Refresh the window to update display
        wrefresh(instructionWin);

        // Wait for user input
        int userInput = getch();
        if (userInput == '\n') {  // Check if 'Enter' is pressed
            break;  // Exit the loop if 'Enter' is pressed
        }
    }

    // Return to main menu after instructions
    displayMainMenu();
    return 0;
}

int displayCredits() {
    // Initialize a window for displaying credits
    WINDOW* creditsWindow = newwin(26, 60, 0, 0);
    box(creditsWindow, 0, 0);  // Draw a box around the window
    wrefresh(creditsWindow);   // Refresh the window to show the box

    // Credits for the development team
    mvwprintw(creditsWindow, 13, 24, "Cheung HonLung");
    mvwprintw(creditsWindow, 15, 24, "Divyansh Tulsyan");
    mvwprintw(creditsWindow, 17, 24, "Jaehun Chun");
    mvwprintw(creditsWindow, 19, 24, "Meeth Jaswani");
    mvwprintw(creditsWindow, 21, 24, "Shrey");

    // Loop to handle navigation back to main menu
    while (true) {
        // Display ASCII art title "Credits"
        mvwprintw(creditsWindow, 1,2,"* * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        mvwprintw(creditsWindow, 2,2,"*   *   *   *   *   *   *   *   *   *   *   *   *   *   *");
        mvwprintw(creditsWindow, 3,2,"*  ________       *     *   *  *_   _*  __  *  * *      *");
        mvwprintw(creditsWindow, 4,2,"* /   __   |  *    *  *   *    | | (_) |  |   *    * *  *");
        mvwprintw(creditsWindow, 5,2,"* |  |  |__| _ ___   ___    ___| |  _  |  |   _____     *");
        mvwprintw(creditsWindow, 6,2,"* |  |  ___ | ' __| / _ \\  /  _  | | | | __| / ____| *  *");
        mvwprintw(creditsWindow, 7,2,"* |  | |   ||  /   | ___/ |  (_| | | | | |   \\__  \\ *   *");
        mvwprintw(creditsWindow, 8,2,"*  \\_______||__|    \\___|  \\__,__| |_| \\___| |____/  *  *");
        mvwprintw(creditsWindow, 9,2,"*   *     *     *     *     *     *     *     *     *   *");
        mvwprintw(creditsWindow, 10,2,"*     *     *     *     *     *     *     *     *    *  *");
        mvwprintw(creditsWindow, 11,2,"* * * * * * * * * * * * * * * * * * * * * * * ** * * *  *");

        // Display the "BACK TO HOME" option with bold and reverse video (highlight)
        wattron(creditsWindow, A_BOLD);
        wattron(creditsWindow, A_REVERSE);
        mvwprintw(creditsWindow, 24, 24, "BACK TO HOME");
        wattroff(creditsWindow, A_REVERSE);  // Turn off highlight

        // Wait for user input
        int userInput = getch();

        // Break the loop and return to main menu if 'Enter' is pressed
        if (userInput == '\n') {
            break;
        }

        wrefresh(creditsWindow);  // Refresh the window to update display
    }

    // Call to the main menu function
    displayMainMenu();
    return 0;
}

int concludeGameSession(const string& playerName, int playerScore) {
    // Initialize the game over window
    WINDOW* gameOverWindow = newwin(26, 60, 0, 0);
    box(gameOverWindow, 0, 0);  // Draw a border around the window
    wrefresh(gameOverWindow);   // Refresh the window to show the border

    // Record player's name and score in a file for high score tracking
    InputToFile(playerName, playerScore);

    // Variable to store user input
    int userInput;

    // Loop until the user presses 'Enter'
    while(true) {
        // Display "Game Over" graphics using ASCII art
        mvwprintw(gameOverWindow, 1,2,"* * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        mvwprintw(gameOverWindow, 2,2,"*   *   *   *   *   *   *   *   *   *   *   *   *   *   *");
        mvwprintw(gameOverWindow, 3,2,"       *    ______    *       *         *     *    *  *");
        mvwprintw(gameOverWindow, 4,2,"   *     * /  ____|      *      *    *     *     *    *");
        mvwprintw(gameOverWindow, 5,2,"  *    *  |  |  ___   _____  _________     ___     *  *");
        mvwprintw(gameOverWindow, 6,2,"    *   * |  | |_  | /  _  | |  _   _ \\  / _  \\  *    *");
        mvwprintw(gameOverWindow, 7,2," *       *|  |__|  | | (_| | | | | | | ||  __/    *   *");
        mvwprintw(gameOverWindow, 8,2," *     *   \\_______|  \\____| |_| |_| |_| \\____|    *  *");
        mvwprintw(gameOverWindow, 9,2,"    *     *     *     *     *     *     *     *     *   *");
        mvwprintw(gameOverWindow, 10,2,"*     *     *     *     *     *     *     *     *     *");
        mvwprintw(gameOverWindow, 11,2,"  *      *   ______   *      *     *   *      *    * *");
        mvwprintw(gameOverWindow, 12,2,"     *    * /  __  \\   *      *         *       *   *");
        mvwprintw(gameOverWindow, 13,2,"  *     *  |  |  |  | __    __  ___   __ ___  *      *");
        mvwprintw(gameOverWindow, 14,2,"     *    *|  |  |  | \\ \\  / / / _ \\ | '___|   *    *");
        mvwprintw(gameOverWindow, 15,2,"         * |  `--'  |  \\ \\/ / |  __/ | /    *     *  *");
        mvwprintw(gameOverWindow, 16,2," *     *    \\______/    \\__/   \\___| |_|   *   *    *");
        mvwprintw(gameOverWindow, 17,2,"*     *     *     *     *     *     *     *     *    * *");
        mvwprintw(gameOverWindow, 18,2,"   *     *     *     *     *     *     *     *    *    *"); 
        mvwprintw(gameOverWindow, 19,2,"*     *     *     *     *     *     *     *     *    * *"); 
        mvwprintw(gameOverWindow, 20,2,"   *     *     *     *     *     *     *     *    *    *");
        mvwprintw(gameOverWindow, 21,2,"* * * * * * * * * * * * * * * * * * * * * * * * * * * *");

        // Display the "BACK TO HOME" option with highlighting
        wattron(gameOverWindow, A_BOLD);  // Apply bold to the text
        wattron(gameOverWindow, A_REVERSE);  // Highlight the text
        mvwprintw(gameOverWindow, 24, 27, "BACK TO HOME");
        wattroff(gameOverWindow, A_REVERSE);  // Turn off highlight

        // Wait for user input
        userInput = getch();

        // If 'Enter' is pressed, exit the loop
        if (userInput == '\n') {
            break;
        }

        wrefresh(gameOverWindow);  // Refresh the window to update the display
    }

    // Return to the main menu after displaying the game over screen
    displayMainMenu();
    return 0;
}
