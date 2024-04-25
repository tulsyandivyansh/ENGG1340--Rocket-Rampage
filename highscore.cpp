#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <cstring>
#include "menu.h"

using namespace std;

// Structure to store player's name and score
struct PlayerScores {
    string PlayerName;
    int PlayerScore;
};

// Function to input the player name and score into a file
void InputToFile(const string& playerName, int playerScore) {
    ofstream scorefile("scores", ios_base::app);
    if (scorefile.is_open()) {
        scorefile << playerName << " " << playerScore << "\n";
    }
}

// Comparator for sorting scores in descending order
bool ScoreComparison(const PlayerScores& s1, const PlayerScores& s2) {
    return s1.PlayerScore > s2.PlayerScore;
}

// Function to sort the scores in descending order and return them as a vector
vector<PlayerScores> SortFile() {
    vector<PlayerScores> scores;
    ifstream inputFile("scores");

    if (inputFile.is_open()) {
        PlayerScores tempScore;
        while (inputFile >> tempScore.PlayerName >> tempScore.PlayerScore) {
            scores.push_back(tempScore);
        }
    }

    sort(scores.begin(), scores.end(), ScoreComparison);
    return scores;
}

// Function to display and output the high scores using ncurses
int highscores() {
    WINDOW* hsWindow = newwin(26, 60, 0, 0);
    box(hsWindow, 0, 0);
    wrefresh(hsWindow);

    vector<PlayerScores> sortedScores = SortFile();

    int row = 12;
    int choice;
    wattron(hsWindow, A_BOLD);
    mvwprintw(hsWindow, 3, 24, "HIGH SCORES");
    mvwprintw(hsWindow, 10, 21, "NAME        SCORE");
    wattroff(hsWindow, A_BOLD);

    for (const auto& score : sortedScores) {
        mvwprintw(hsWindow, row, 21, score.PlayerName.c_str());
        mvwprintw(hsWindow, row++, 33, to_string(score.PlayerScore).c_str());
    }

    wattron(hsWindow, A_REVERSE);
    mvwprintw(hsWindow, 24, 24, "BACK TO MENU");
    wattroff(hsWindow, A_REVERSE);
    wrefresh(hsWindow);

    do {
        choice = getch();
    } while (choice != 10); // 10 is the ASCII code for Enter

    startMenu();
    return 0;
}
