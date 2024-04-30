#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int startMenu();
int name();
int playerguide();
int gameEnd(string player_alias, int player_score);
int highscore();
int credits();

#endif
