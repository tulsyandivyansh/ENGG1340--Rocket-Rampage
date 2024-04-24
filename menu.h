#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int startMenu();
int name();
int instructions1();
int instructions2();
int instructions3();
int instructions4();
int gameOver(string playerName, int playerScore);
int highscore();
int credits();

#endif
