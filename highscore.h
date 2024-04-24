#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <vector>
#include <string>
#include <ncurses.h>
using namespace std;

struct PlayerScores
{
    string PlayerName;
    int PlayerScore;
};

void InputToFile(string playerName, int playerScore);

bool ScoreComparison(const PlayerScores& s1, const PlayerScores& s2);

vector<PlayerScores> SortFile();

int highscores();

#endif
