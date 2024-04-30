#include <vector>
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <algorithm>
#include <string>
#include "display.h"

using namespace std;

// stores player name and score //
struct player_scores 
{

    int player_score;
    string player_alias;
};

// input player name and score into score file //
void file_input(string player_alias, int player_score) 
{
    player_scores player1;
    player1.player_score = player_score;
    player1.player_alias = player_alias;
    ofstream score_file;

    score_file.open("scores", ios_base::app);
    if (score_file.is_open()) {
        score_file << player1.player_score << " " << player1.player_alias << endl;
        score_file.close();
    }
}

// sort scores in order and return score
vector<player_scores> sort_file() 
{
    vector<player_scores> scores;
    // temp_score variable -> store the score in the inputfile in a variable //
    player_scores temp_score; 
    ifstream input_file("scores");
    // opening scores file to retieve the values
    if (input_file.is_open()) { 
        while (input_file >> temp_score.player_alias >> temp_score.player_score) {
            scores.push_back(temp_score);
        }
        input_file.close();
        // using the sort() function and using the compare_scores as defined above to sort in descending order
        sort(scores.begin(), scores.end(), compare_scores); 
    } 
    return scores;
}

// check which score is higher //
bool compare_scores(const player_scores& score1, const player_scores& score2) 
{
    return score1.player_score > score2.player_score;
}

//function to display and output the top 5 highscores
int highscores() 
{

    WINDOW* score_window = newwin(26,60,0,0);
    // highscore window //
    box(score_window, 0, 0);
    wrefresh(score_window);

    // Getting and sorting the scores in order using sort_file() function
    vector<player_scores> sortedScores = sort_file();

    //Printing the sorted scores in a window page using ncurses
    int row = 12;
    int choice;
        wattron(score_window, A_BOLD);
        mvwprintw(score_window, 10, 21, "SCORE        NAME");
        mvwprintw(score_window, 3, 24, "TOP  SCORES");
        wattroff(score_window, A_BOLD);
        int i=0;
        //adding only the top 5 names and scores
        while (i < 5 && i < sortedScores.size()) {
            mvwprintw(score_window, row, 21, sortedScores[i].player_alias.c_str());
            mvwprintw(score_window, row++, 33, to_string(sortedScores[i].player_score).c_str());
            i+=1;
        }
        // highlighting "BACK TO MENU" option
        wattron(score_window, A_REVERSE);
        mvwprintw(score_window, 24, 24, "BACK TO MENU");
        wattroff(score_window, A_REVERSE);
        // switching off highlight option
        wrefresh(score_window);
        while(true)
        {
            // getting user input
            choice=getch();
            // checking whether user pressed enter
            if(choice==10)
            {
                break;
            }
        }
    startMenu();
    return 0;
}
