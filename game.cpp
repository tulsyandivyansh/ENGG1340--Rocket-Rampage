#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "menu.h"
#include <vector>
using namespace std;

//Defining the window size for the game
int gameY = 30;
int gameX = 60;
//To count number of iterations to decide level
int iteration = 0;
//The Player class keeps track of the player's name, points, and remaining lives
class Player{
public:
    //Player name
    string name;
    //Player lives
    int lives;
    //Player Points
    int Points;

    //Initialize player
    void init(string name, int Points, int lives) {
        this -> name = name;
        this -> Points = Points;
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
int level(int iteration){
    if (iteration < 600){
        return 1;
    }
    else if (iteration < 1200){
        return 2;
    }
    else if (iteration < 1800){
        return 3;
    }
    else if (iteration < 2400){
        return 4;
    }
    else {
        return 5;
    }
}
//The Player Rocket class represents the player's rocket and is responsible for moving it left and right based on user input
class PlayerRocket {
public:
    //Rocket art
    string sprite;
    PlayerRocket(): sprite ( "  .\n"
                       "  |\n"
                       " / \\\n"
                       " |0|\n"
                       "/   \\\n"
                       "U U U\n"), x(0), y(0) {};
    //Pposition
    int x, y;

    //Initialize PlayerRocket
    void init(int y, int x) {
        this -> y = y;
        this -> x = x;
    }

    //Update PlayerRocket position according to player input
    void update(int input) {
        switch(input) {
            case KEY_LEFT:
                if(x > 2) {
                    x -= 2;
                }
                break;
            case KEY_RIGHT:
                if(x < gameX - 7) {
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

    //Draw PlayerRocket in the game window
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
    //Erase PlayerRocket from the game window
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
    int dx, dy;
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
    WINDOW* gameWindow = newwin(gameY, gameX, 3, 0);
    //Draw a box around the game window
    box(gameWindow, 0, 0);
    //Refresh the game window initially
    wrefresh(gameWindow);

    //Create a window to show controls
    WINDOW* commandsWindow = newwin(3, 60, 33, 0);
    //Draw a box around the command window
    box(commandsWindow, 0, 0);
    //Print instructions
    mvwprintw(commandsWindow, 1, 1, "[<][>]:Move Rocket        [A]: Shoot            [Q]:Quit");
    //Refresh command window initially
    wrefresh(commandsWindow);

    //Initialize the player, level, ball and Rocket
    Player player;
    player.init(playerName, 0, 5);


    PlayerRocket playerRocket;
    playerRocket.init(22, 30);
    //Draw all the components and refresh the game window initially
    playerRocket.draw(gameWindow);
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
        
        switch(level(iteration)){
            case 1:
            if(iteration % 20 == 0){
                enemy.push_back(Enemy(0, rand()%50 +2));    
            }

            wrefresh(gameWindow);

            for(int i = enemy.size()-1; i >= 0; i--){

                if(enemy[i].y ==25)
                {
                    enemy[i].erase(gameWindow);
                    wrefresh(gameWindow);
                    player.lives -= 1;
                    enemy.erase(enemy.begin() + i);
                    continue;
                }
                if((iteration+1)%7 == 0){
                    enemy[i].erase(gameWindow);
                    wrefresh(gameWindow);
                    (enemy[i].y)+=1;
                    enemy[i].draw(gameWindow);
                    wrefresh(gameWindow);
                }
            }
            break;

            case 2:
            if(iteration % 14 == 0){
                enemy.push_back(Enemy(0, rand()%50 +2));    
            }

            wrefresh(gameWindow);

            for(int i = enemy.size()-1; i >= 0; i--){

                if(enemy[i].y ==25)
                {
                    enemy[i].erase(gameWindow);
                    wrefresh(gameWindow);
                    player.lives -= 1;
                    enemy.erase(enemy.begin() + i);
                    continue;
                }
                if((iteration+1)%5 == 0){
                    enemy[i].erase(gameWindow);
                    wrefresh(gameWindow);
                    (enemy[i].y)+=1;
                    enemy[i].draw(gameWindow);
                    wrefresh(gameWindow);
                }
            }
            break;
            
            case 3:
            if(iteration % 12 == 0){
                enemy.push_back(Enemy(0, rand()%50 +2));    
            }

            wrefresh(gameWindow);

            for(int i = enemy.size()-1; i >= 0; i--){

                if(enemy[i].y ==25)
                {
                    enemy[i].erase(gameWindow);
                    wrefresh(gameWindow);
                    player.lives -= 1;
                    enemy.erase(enemy.begin() + i);
                    continue;
                }
                if((iteration+1)%4 == 0){
                    enemy[i].erase(gameWindow);
                    wrefresh(gameWindow);
                    (enemy[i].y)+=1;
                    enemy[i].draw(gameWindow);
                    wrefresh(gameWindow);
                }
            }
            break;

            case 4:
            if(iteration % 10 == 0){
                enemy.push_back(Enemy(0, rand()%50 +2));    
            }

            wrefresh(gameWindow);

            for(int i = enemy.size()-1; i >= 0; i--){

                if(enemy[i].y ==25)
                {
                    enemy[i].erase(gameWindow);
                    wrefresh(gameWindow);
                    player.lives -= 1;
                    enemy.erase(enemy.begin() + i);
                    continue;
                }
                if((iteration+1)%4 == 0){
                    enemy[i].erase(gameWindow);
                    wrefresh(gameWindow);
                    (enemy[i].y)+=1;
                    enemy[i].draw(gameWindow);
                    wrefresh(gameWindow);
                }
            }
            break;
        
            case 5:
            if(iteration % 8 == 0){
                enemy.push_back(Enemy(0, rand()%50 +2));    
            }

            wrefresh(gameWindow);

            for(int i = enemy.size()-1; i >= 0; i--){

                if(enemy[i].y ==25)
                {
                    enemy[i].erase(gameWindow);
                    wrefresh(gameWindow);
                    player.lives -= 1;
                    enemy.erase(enemy.begin() + i);
                    continue;
                }
                if((iteration+1)%3 == 0){
                    enemy[i].erase(gameWindow);
                    wrefresh(gameWindow);
                    (enemy[i].y)+=1;
                    enemy[i].draw(gameWindow);
                    wrefresh(gameWindow);
                }
                
            }
            break;
        }




        //Initialize new ball on losing a life
        if(input == 'a' || input == 'A') {
            balls.push_back(Ball((playerRocket.y), (playerRocket.x)+2, -1.));

        }
        for(int i = balls.size()-1; i >= 0; i--){
             if ((balls[i].y == 2) || (balls[i].x == 1) || (balls[i].x == 58)){
                balls[i].erase(gameWindow);
                wrefresh(gameWindow);
                balls.erase(balls.begin() + i);
                continue;
             }
             balls[i].erase(gameWindow);
             wrefresh(gameWindow);

        //Update ball position
             balls[i].y += balls[i].dy;
             balls[i].draw(gameWindow);
             wrefresh(gameWindow);
        }

    //Handle collision of player with the enemy rockets
        for(int j = enemy.size()-1; j >= 0; j--){
            string rocket=playerRocket.sprite;
            int rockety=playerRocket.y ;
            int rocketx=playerRocket.x;
            int lineIndex = 0;
            int startPos = 0;
            int endPos = rocket.find('\n');
            while (endPos != string::npos) {
                if (rockety+ lineIndex== enemy[j].y ||rockety+ lineIndex== (enemy[j].y )+ 1 ){
                    string line = rocket.substr(startPos, endPos - startPos);
                
                    for (int i=0;i<line.length(); i++){
                  if ((rocketx)+i== enemy[j].x || (rocketx)+i== (enemy[j].x) + 1 || (rocketx)+i== (enemy[j].x) + 2 ){
                    enemy[j].erase(gameWindow);
                    wrefresh(gameWindow);
                    enemy.erase(enemy.begin() + j);  
                    player.lives-=1; 
                    break;
                    }
                }
                }
            startPos = endPos + 1;
            endPos = rocket.find('\n', startPos);
            ++lineIndex;
            
        }
    }
    
        
        


        //Handle collision with the enemy rockets
        for(int i = balls.size()-1; i >= 0; i--){
            for(int j = enemy.size()-1; j >= 0; j--){
                if(balls[i].x == enemy[j].x || balls[i].x == (enemy[j].x )+1 || balls[i].x == (enemy[j].x )+2)
                { 
                    if(balls[i].y == ((enemy[j].y)+1) || balls[i].y == (enemy[j].y) || balls[i].y == (enemy[j].y)+2){
                        balls[i].erase(gameWindow);
                        wrefresh(gameWindow);
                        balls.erase(balls.begin() + i);
                        enemy[j].erase(gameWindow);
                        wrefresh(gameWindow);
                        enemy.erase(enemy.begin() + j);
                        player.Points+=10;
                        
                    }
                }
                
            }
        }
        
        //Update PlayerRocket position
        playerRocket.erase(gameWindow);
        playerRocket.update(input);
        playerRocket.draw(gameWindow);

        //Update player info
        string playerInfo = "Points:" + to_string(player.Points) + "           Level:" + to_string(level(iteration)) + "          " + "Lives:" + to_string(player.lives);
        mvwprintw(infoWindow, 1, 1, playerInfo.c_str());                                                 
        wrefresh(infoWindow);

        //Refresh game window
        wrefresh(gameWindow);

        //Clear buffered input from previous frame
        flushinp();
        //Sleep for 100000 microseconds before updating
        usleep(100000);
        iteration++;
    }
    iteration = 0;

    if(died) gameOver(player.name, player.Points);
    else startMenu();
    return 0;
}
