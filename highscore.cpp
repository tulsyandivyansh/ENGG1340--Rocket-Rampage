#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <cstring>
#include "menu.h"

using namespace std;

// Making a PlayerScores structure which stores the name and score of the player
struct PlayerScores 
{
    string PlayerName;
    int PlayerScore;
};

// Function to input the player name and score into the scores file
void InputToFile(string playerName, int playerScore) 
{
    PlayerScores player1;
    player1.PlayerName = playerName;
    player1.PlayerScore = playerScore;
    ofstream scorefile;
    // Opening scores file to input values
    scorefile.open("scores", ios_base::app);
    if (scorefile.is_open()) {
        scorefile << player1.PlayerName << " " << player1.PlayerScore << endl;
        scorefile.close();
    }
}

// Return a boolean value, true if the score in s1 is greater than score in s2; will be used in sort() in the SortFile()
bool ScoreComparison(const PlayerScores& s1, const PlayerScores& s2) 
{
    return s1.PlayerScore > s2.PlayerScore;
}

// Function to sort the scores in descending order and returning the sorted scores in vector data type
vector<PlayerScores> SortFile() 
{
    vector<PlayerScores> scores;
    PlayerScores tempScore; 
    ifstream inputFile("scores");
    // Opening scores file to retrieve the values
    if (inputFile.is_open()) { 
        while (inputFile >> tempScore.PlayerName >> tempScore.PlayerScore) {
            scores.push_back(tempScore);
        }
        inputFile.close();

        sort(scores.begin(), scores.end(), ScoreComparison);
    } 
    return scores;
}

// Function to display and output the high scores
int highscores() 
{
    WINDOW* hsWindow = newwin(26,60,0,0);
    // Drawing the box
    box(hsWindow, 0, 0);
    wrefresh(hsWindow);

    // Getting and sorting the scores in descending order using SortFile() function
    vector<PlayerScores> sortedScores = SortFile();

    // Printing the sorted scores in a window page using ncurses
    int row = 12;
    int choice;
    wattron(hsWindow, A_BOLD);
    mvwprintw(hsWindow, 3, 24, "HIGH SCORES");
    mvwprintw(hsWindow, 10, 21, "NAME        SCORE");
    wattroff(hsWindow, A_BOLD);

    // Print all the scores
    for (int i = 0; i < sortedScores.size(); i++) {
        mvwprintw(hsWindow, row, 21, sortedScores[i].PlayerName.c_str());
        mvwprintw(hsWindow, row++, 33, to_string(sortedScores[i].PlayerScore).c_str());
    }

    // Highlighting "BACK TO MENU" option
    wattron(hsWindow, A_REVERSE);
    mvwprintw(hsWindow, 24, 24, "BACK TO MENU");
    wattroff(hsWindow, A_REVERSE);
    // Switching off highlight option
    wrefresh(hsWindow);
    for (;;) {
        // Getting user input
        choice = getch();
        // Checking whether user pressed enter
        if (choice == 10) {
            break;
        }
    }
    startMenu();
    return 0;
}
