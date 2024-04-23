#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include "menu.h"
#include <vector>
using namespace std;

//Define game window size
int gameWindowSizeY = 30;
int gameWindowSizeX = 60;

//The Player class keeps track of the player's name, score, and remaining lives
class Player {
public:
    //Player name
    string name;
    //Player score
    int score;
    //Player lives
    int lives;

    //Initialize player
    void init(string name, int score, int lives) {
        this -> name = name;
        this -> score = score;
        this -> lives = lives;
    }
};
class Enemy {
public:
    string sprite = ("|0|\n"
                     "\\0/\n");
    int x, y;

    Enemy(int y, int x) {
        this->y = y;
        this->x = x;
    }

    void draw(WINDOW* gameWindow) {
        int lineIndex = 0;
        int startPos = 0;
        int endPos = int(sprite.find('\n'));
        while (endPos != string::npos) {
            mvwprintw(gameWindow, y + lineIndex + 1, x,sprite.substr(startPos, endPos - startPos).c_str());
            startPos = endPos + 1;
            endPos =int( sprite.find('\n', startPos));
            ++lineIndex;
        }
    }
    
    void erase(WINDOW* window){
        for (int i = 0; i < 3; ++i){
            mvwprintw(window, y+i+1, x, "    ");
        }
    }

};

//The Paddle class represents the player's paddle and is responsible for moving it left and right based on user input
class Paddle {
public:
    //Paddle art
    string sprite;
    Paddle(): sprite ( "  .\n"
                       "  |\n"
                       " / \\\n"
                       " |0|\n"
                       "/   \\\n"
                       "U U U\n"), x(0), y(0) {};
    //Paddle position
    int x, y;

    //Initialize paddle
    void init(int y, int x) {
        this -> y = y;
        this -> x = x;
    }

    //Update paddle position according to player input
    void update(int input) {
        switch(input) {
            case KEY_LEFT:
                if(x > 2) {
                    x -= 2;
                }
                break;
            case KEY_RIGHT:
                if(x < gameWindowSizeX - 7) {
                    x += 2;
                }
                break;
            default:
                break;
        }
    }
    void setX(int x){
        this -> x = x;
    }
    void setY(int y){
        this -> y = y;
    }

    //Draw paddle in the game window
    void draw(WINDOW* window) {
        int lineIndex = 0;
        int startPos = 0;
        int endPos = sprite.find('\n');
        while (endPos != string::npos) {
            mvwprintw(window, y + lineIndex, x, sprite.substr(startPos, endPos - startPos).c_str());
            startPos = endPos + 1;
            endPos = sprite.find('\n', startPos);
            ++lineIndex;
        }
    }
    //Erase paddle from the game window
    void erase(WINDOW* window){
        for (int i = 0; i < 6; ++i){
            mvwprintw(window, y+i, x, "     ");
        }
    }
};

//The Ball class is responsible for handling the ball
class Ball {
public:
    //Ball art
    string sprite = "o";
    //Ball position
    int x, y;
    //Ball velocity
    int dy;
    //Initialize ball
    Ball(int y, int x, int dy) {
        this -> y = y;
        this -> x = x;
        this -> dy = dy;
    }
    //Draw ball in the game window
    void draw(WINDOW* window) {
        mvwprintw(window, y, x, sprite.c_str());
    }

    //Erase ball from the game window
    void erase(WINDOW* window) {
        mvwprintw(window, y, x, " ");
    }
};

//The game function runs the main game - it accepts the player name as a parameter and passes it to the player class
int game(string playerName) {

    //Randomize seed
    srand(time(nullptr));

    //Create a window to show player info
    WINDOW* infoWindow = newwin(3, 60, 0, 0);
    //Draw a box around the info window
    box(infoWindow, 0, 0);
    //Refresh the info window initially
    wrefresh(infoWindow);

    //Create a window for the game
    WINDOW* gameWindow = newwin(gameWindowSizeY, gameWindowSizeX, 3, 0);
    //Draw a box around the game window
    box(gameWindow, 0, 0);
    //Refresh the game window initially
    wrefresh(gameWindow);

    //Create a window to show controls
    WINDOW* commandsWindow = newwin(3, 60, 33, 0);
    //Draw a box around the command window
    box(commandsWindow, 0, 0);
    //Print instructions
    mvwprintw(commandsWindow, 1, 1, "[<][>]:Move Paddle        [A]: Shoot            [Q]:Quit");
    //Refresh command window initially
    wrefresh(commandsWindow);

    //Initialize the player, level, ball and paddle
    Player player;
    player.init(playerName, 0, 3);


    Paddle paddle;
    paddle.init(22, 30);
    //Draw all the components and refresh the game window initially
    paddle.draw(gameWindow);
    wrefresh(gameWindow);
    vector<Ball> balls;
    vector<Enemy> enemy;
    //Flags to handle losing a life and player death
    bool restart = false;
    bool died = false;
    int ball_num = 0;
    //Game loop
    while(true) {
        //Randomize seed
        srand(time(nullptr));

        //Get player input
        int input = getch();

        //Quit if user presses 'Q'
        if(input == 'q' || input == 'Q') {
            break;
        }

        //If player dies, exit loop and show Game Over screen
        if(player.lives == 0) {
            died = true;
            break;
        }
         if(true){
            enemy.push_back(Enemy(0, rand()%55 +2));
            
        }
            
            wrefresh(gameWindow);
            
            for(i=0; i <= enemy.size()-1;i++){
                
                if(enemy[i].y >=15)
                {
                    enemy[i].erase(gameWindow);
                    enemy.erase(enemy.begin() + i);
                    continue;
                }
                enemy[i].erase(gameWindow);
                (enemy[i].y)+=1;
                enemy[i].draw(gameWindow);
                wrefresh(gameWindow);
                
                
            }



        //Initialize new ball on losing a life
        if(input == 'a' || input == 'A') {
            balls.push_back(Ball((paddle.y)+5, (paddle.x)+2, -1));
            ball_num++;
            if (ball_num == 50){
                died = true;
                break;
            }
        }
        for(int i = balls.size()-1; i >= 0; i--){
             if (balls[i].y == 2){
                balls[i].erase(gameWindow);
                balls.erase(balls.begin() + i);
                continue;
             }
             balls[i].erase(gameWindow);

        //Update ball position
             balls[i].y += balls[i].dy;
             balls[i].draw(gameWindow);
        }
        //Clears ball from last position to not leave a trail

        //Update paddle position
        paddle.erase(gameWindow);
        paddle.update(input);
        paddle.draw(gameWindow);

        //Update player info
        string playerInfo = "Score:" + to_string(player.score) + "                                       " + "Lives:" + to_string(player.lives);
        mvwprintw(infoWindow, 1, 1, playerInfo.c_str());
        wrefresh(infoWindow);

        //Refresh game window
        wrefresh(gameWindow);

        //Clear buffered input from previous frame
        flushinp();
        //Sleep for 100000 microseconds before updating
        usleep(100000);
    }

    if(died) gameOver(player.name, player.score);
    else mainmenu();

    return 0;
}
