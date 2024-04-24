#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <cstring>
#include "menu.h"

using namespace std;

//making a PlayerScores structure which stores the name and score of the player
struct PlayerScores 
{
    string PlayerName;
    int PlayerScore;
};

//function to input the player name and score into the scores file
void InputToFile(string playerName, int playerScore) 
{
    PlayerScores player1;
    player1.PlayerName = playerName;
    player1.PlayerScore = playerScore;
    ofstream scorefile;
    //opening scores file to input values0
    scorefile.open("scores", ios_base::app);
    if (scorefile.is_open()) {
        scorefile << player1.PlayerName << " " << player1.PlayerScore << endl;
        scorefile.close();
    }
}

//return a boolean value, true if the score in s1 is greater than score in s2; will be used in sort() in the SortFile()
bool ScoreComparison(const PlayerScores& s1, const PlayerScores& s2) 
{
    return s1.PlayerScore > s2.PlayerScore;
}

//function to sort the scores in descending order and returning the sorted scores in vector data type
vector<PlayerScores> SortFile() 
{
    vector<PlayerScores> scores;
    //making tempScore variable to temporarily store the score in the inputfile in a variable
    PlayerScores tempScore; 
    ifstream inputFile("scores");
    //opening scores file to retieve the values
    if (inputFile.is_open()) { 
        while (inputFile >> tempScore.PlayerName >> tempScore.PlayerScore) {
            scores.push_back(tempScore);
        }
        inputFile.close();
        //using the sort() function and using the ScoreComparison as defined above to sort in descending order
        sort(scores.begin(), scores.end(), ScoreComparison); 
    } 
    return scores;
}

//function to display and output the top 5 highscores
int highscores() 
{

    WINDOW* hsWindow = newwin(26,60,0,0);
    //Drawing the box
    box(hsWindow, 0, 0);
    wrefresh(hsWindow);

    //Getting and sorting the scores in descending order using SortFile() function
    vector<PlayerScores> sortedScores = SortFile();

    //Printing the sorted scores in a window page using ncurses
    int row = 12;
    int choice;
        wattron(hsWindow, A_BOLD);
        mvwprintw(hsWindow, 3, 24, "TOP 5 SCORES");
        mvwprintw(hsWindow, 10, 21, "NAME        SCORE");
        wattroff(hsWindow, A_BOLD);

        //adding only the top 5 names and scores
        for (int i = 0; i < 5 && i < sortedScores.size(); i++) {
            mvwprintw(hsWindow, row, 21, sortedScores[i].PlayerName.c_str());
            mvwprintw(hsWindow, row++, 33, to_string(sortedScores[i].PlayerScore).c_str());
        }
        //high;ighting "BACK TO MENU" option
        wattron(hsWindow, A_REVERSE);
        mvwprintw(hsWindow, 24, 24, "BACK TO MENU");
        wattroff(hsWindow, A_REVERSE);
        //switching off highlight option
        wrefresh(hsWindow);
        for(;;)
        {
            //getting user input
            choice=getch();
            //checking whether user pressed enter
            if(choice==10)
            {
                break;
            }
        }
    startMenu();
    return 0;
}
