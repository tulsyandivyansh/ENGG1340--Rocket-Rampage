#include <string>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include "menu.h"
#include <vector>
using namespace std;

// game window size
int gameY = 30;
int gameX = 60;
// level count system //
int iteration = 0;
// player name lives and points //
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
    string ship = ("|0|\n"
                     "\\0/\n");
    int x, y;

    Enemy(int y, int x) {
        this->y = y;
        this->x = x;
    }

    void draw(WINDOW* gameWindow) {
        int lineIndex = 0;
        int startPos = 0;
        int endPos = int(ship.find('\n'));
        while (endPos != string::npos) {
            mvwprintw(gameWindow, y + lineIndex + 1, x,ship.substr(startPos, endPos - startPos).c_str());
            startPos = endPos + 1;
            endPos =int( ship.find('\n', startPos));
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
// Rocket class -> user input changes rocket direction left and right //
class PlayerRocket {
public:
    // Rocket design //
    string ship;
    PlayerRocket(): ship ( "  .\n"
                       "  |\n"
                       " / \\\n"
                       " |0|\n"
                       "/   \\\n"
                       "U U U\n"), x(0), y(0) {};
    // Rocket pos //
    int x, y;

    // Initialize PlayerRocket // 
    void init(int y, int x) {
        this -> y = y;
        this -> x = x;
    }

    // Update PlayerRocket position based on input //
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

    // Display PlayerRocket in the game window //
    void draw(WINDOW* window) {
        int lineIndex = 0;
        int startPos = 0;
        int endPos = ship.find('\n');
        while (endPos != string::npos) {
            mvwprintw(window, y + lineIndex, x, ship.substr(startPos, endPos - startPos).c_str());
            startPos = endPos + 1;
            endPos = ship.find('\n', startPos);
            ++lineIndex;
        }
    }
    // Erase PlayerRocket from the game window
    void erase(WINDOW* window){
        for (int i = 0; i < 6; ++i){
            mvwprintw(window, y+i, x, "     ");
        }
    }
};

// Class for handling bullets //
class bullet {
public:
    // Bullet design //
    string ship = "o";
    // Bullet pos //
    int x, y;
    // Bullet speed //
    int dx, dy;
    //Initialize bullet
    bullet(int y, int x, int dy) {
        this -> y = y;
        this -> x = x;
        this -> dy = dy;
    }
    // Display Bullet in the game window //
    void draw(WINDOW* window) {
        mvwprintw(window, y, x, ship.c_str());
    }

    // Erase Bullet from the game window //
    void erase(WINDOW* window) {
        mvwprintw(window, y, x, " ");
    }
};

// main game func //
int game(string playerName) {

    // random seed //
    srand(time(nullptr));

    // show player info //
    WINDOW* infoWindow = newwin(3, 60, 0, 0);
    box(infoWindow, 0, 0);
    // refresh the info window //
    wrefresh(infoWindow);

    // game window //
    WINDOW* gameWindow = newwin(gameY, gameX, 3, 0);
    box(gameWindow, 0, 0);
    // refresh the game window //
    wrefresh(gameWindow);

    // window for controls //
    WINDOW* instruction_tab = newwin(3, 60, 33, 0);
    box(instruction_tab, 0, 0);
    // instructions //
    mvwprintw(instruction_tab, 1, 1, "[<][>]:Move Rocket        [A]: Shoot            [Q]:Quit");
    // refresh instructions tab //
    wrefresh(instruction_tab);

    // initialize all components //
    Player player;
    player.init(playerName, 0, 5);
    PlayerRocket playerRocket;
    playerRocket.init(22, 30);
    // display all the components and refresh the game window //
    playerRocket.draw(gameWindow);
    wrefresh(gameWindow);
    vector<bullet> bullets;
    vector<Enemy> enemy;
    // life and player death flags // 
    bool restart = false;
    bool died = false;
    int bullet_num = 0;
    // main game loop
    while(true) {
        //Randomize seed
        srand(time(nullptr));

        // player input //
        int input = getch();

        // quit - 'Q' //
        if(input == 'q' || input == 'Q') {
            break;
        }

        // game over - exit loop and show end screen //
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




        // Initialize new bullet on losing a life
        if(input == 'a' || input == 'A') {
            bullets.push_back(bullet((playerRocket.y), (playerRocket.x)+2, -1.));

        }
        for(int i = bullets.size()-1; i >= 0; i--){
             if ((bullets[i].y == 2) || (bullets[i].x == 1) || (bullets[i].x == 58)){
                bullets[i].erase(gameWindow);
                wrefresh(gameWindow);
                bullets.erase(bullets.begin() + i);
                continue;
             }
             bullets[i].erase(gameWindow);
             wrefresh(gameWindow);

        // Update bullet position
             bullets[i].y += bullets[i].dy;
             bullets[i].draw(gameWindow);
             wrefresh(gameWindow);
        }

    // Handle collision of player with the enemy rockets
        for(int j = enemy.size()-1; j >= 0; j--){
            string rocket=playerRocket.ship;
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
    
        
        


        // Handle collision with the enemy rockets
        for(int i = bullets.size()-1; i >= 0; i--){
            for(int j = enemy.size()-1; j >= 0; j--){
                if(bullets[i].x == enemy[j].x || bullets[i].x == (enemy[j].x )+1 || bullets[i].x == (enemy[j].x )+2)
                { 
                    if(bullets[i].y == ((enemy[j].y)+1) || bullets[i].y == (enemy[j].y) || bullets[i].y == (enemy[j].y)+2){
                        bullets[i].erase(gameWindow);
                        wrefresh(gameWindow);
                        bullets.erase(bullets.begin() + i);
                        enemy[j].erase(gameWindow);
                        wrefresh(gameWindow);
                        enemy.erase(enemy.begin() + j);
                        player.Points+=10;
                        
                    }
                }
                
            }
        }
        
        // Update PlayerRocket position
        playerRocket.erase(gameWindow);
        playerRocket.update(input);
        playerRocket.draw(gameWindow);

        // Update player info
        string playerInfo = "Points:" + to_string(player.Points) + "           Level:" + to_string(level(iteration)) + "          " + "Lives:" + to_string(player.lives);
        mvwprintw(infoWindow, 1, 1, playerInfo.c_str());                                                 
        wrefresh(infoWindow);

        // Refresh game window
        wrefresh(gameWindow);

        flushinp();
        // Sleep for 100000 microseconds before updating
        usleep(100000);
        iteration++;
    }
    iteration = 0;

    if(died) gameEnd(player.name, player.Points);
    else startMenu();
    return 0;
}
