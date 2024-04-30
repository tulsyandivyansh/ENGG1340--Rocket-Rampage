#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <vector>
#include <string>
#include <ncurses.h>
using namespace std;

struct player_scores
{
    string player_alias;
    int player_score;
};

void file_input(string player_alias, int player_score);

bool compare_scores(const player_scores& score1, const player_scores& score2);

vector<player_scores> sort_file();

int highscores();

#endif
