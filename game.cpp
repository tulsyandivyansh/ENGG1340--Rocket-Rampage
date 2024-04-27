#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "menu.h"
#include <vector>
using namespace std;

//Define game window size
int gameWindowSizeY = 30;
int gameWindowSizeX = 60;
int iteration = 0;
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
int level(int iteration){
    if (iteration < 200){
        return 1; 
    }
    else if (iteration < 600){
        return 2;
    }
    else if (iteration < 1200){
        return 3;
    }
    else if (iteration < 1800){
        return 4;
    }
    else if (iteration < 2400){
        return 5;
    }
    else {
        return 6;
    }
}
// Rocket class -> user input changes rocket direction left and right //
class Rocket {
public:
    // Rocket design //
    string sprite;
    Rocket(): sprite ( "  .\n"
                       "  |\n"
                       " / \\\n"
                       " |0|\n"
                       "/   \\\n"
                       "U U U\n"), x(0), y(0) {};
    // Rocket pos //
    int x, y;

    // Initialize Rocket //
    void init(int y, int x) {
        this -> y = y;
        this -> x = x;
    }

    // Update Rocket position based on input // 
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

    // Display Rocket in the game window //
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
    // Erase Rocket from the game window 
    void erase(WINDOW* window){
        for (int i = 0; i < 6; ++i){
            mvwprintw(window, y+i, x, "     ");
        }
    }
};

// Class for handling bullets // 
class Bullet {
public:
    // Bullet art //
    string sprite = "o";
    // Bullet pos //
    int x, y;
    // Bullet speed //
    int dx, dy;
    // Initialize Bullet
    Bullet(int y, int x, int dy) {
        this -> y = y;
        this -> x = x;
        this -> dy = dy;
    }
    // Display Bullet in the game window //
    void draw(WINDOW* window) {
        mvwprintw(window, y, x, sprite.c_str());
    }

    // Erase Bullet from the game window
    void erase(WINDOW* window) {
        mvwprintw(window, y, x, " ");
    }
};

// The game function runs the main game - it accepts the player name as a parameter and passes it to the player class
int game(string player_alias) {

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
    mvwprintw(commandsWindow, 1, 1, "[<][>]:Move Rocket        [A]: Shoot            [Q]:Quit");
    //Refresh command window initially
    wrefresh(commandsWindow);

    //Initialize the player, level, Bullet and Rocket
    Player player;
    player.init(player_alias, 0, 5);


    Rocket Rocket;
    Rocket.init(22, 30);
    //Draw all the components and refresh the game window initially
    Rocket.draw(gameWindow);
    wrefresh(gameWindow);
    vector<Bullet> Bullets;
    vector<Enemy> enemy;
    //Flags to handle losing a life and player death
    bool restart = false;
    bool died = false;
    int Bullet_num = 0;
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
        
        else if (iteration < 600){
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
        }
        else if (iteration < 1200){
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
        }
        else if (iteration < 1800){
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
        }
        else if (iteration < 2400){
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
        }
        
        else {
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
        }




        // Initialize new Bullet on Bullet Erase
        if(input == 'a' || input == 'A') {
            Bullets.push_back(Bullet((Rocket.y), (Rocket.x)+2, -1.));

        }
        for(int i = Bullets.size()-1; i >= 0; i--){
             if ((Bullets[i].y == 2) || (Bullets[i].x == 1) || (Bullets[i].x == 58)){
                Bullets[i].erase(gameWindow);
                wrefresh(gameWindow);
                Bullets.erase(Bullets.begin() + i);
                continue;
             }
             Bullets[i].erase(gameWindow);
             wrefresh(gameWindow);

        // Update Bullet position
             Bullets[i].y += Bullets[i].dy;
             Bullets[i].draw(gameWindow);
             wrefresh(gameWindow);
        }

// Handle collision of player with the enemy rockets //
        for(int j = enemy.size()-1; j >= 0; j--){
            string rocket=Rocket.sprite;
            int rockety=Rocket.y ;
            int rocketx=Rocket.x;
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
    
        
        


        // Handle collision with the enemy rockets //
        for(int i = Bullets.size()-1; i >= 0; i--){
            for(int j = enemy.size()-1; j >= 0; j--){
                if(Bullets[i].x == enemy[j].x || Bullets[i].x == (enemy[j].x )+1 || Bullets[i].x == (enemy[j].x )+2)
                { 
                    if(Bullets[i].y == ((enemy[j].y)+1) || Bullets[i].y == (enemy[j].y) || Bullets[i].y == (enemy[j].y)+2){
                        Bullets[i].erase(gameWindow);
                        wrefresh(gameWindow);
                        Bullets.erase(Bullets.begin() + i);
                        enemy[j].erase(gameWindow);
                        wrefresh(gameWindow);
                        enemy.erase(enemy.begin() + j);
                        player.score+=10;
                        
                    }
                }
                
            }
        }
        
        // Update Rocket position //
        Rocket.erase(gameWindow);
        Rocket.update(input);
        Rocket.draw(gameWindow);

        // Update player info //
        string playerInfo = "Score:" + to_string(player.score) + "           Level:" + to_string(level(iteration)) + "          " + "Lives:" + to_string(player.lives);
        mvwprintw(infoWindow, 1, 1, playerInfo.c_str());                                                 
        wrefresh(infoWindow);

        // Refresh game window // 
        wrefresh(gameWindow);

        // Clear buffered input from previous frame //
        flushinp();
        // Sleep for 100000 microseconds before updating //
        usleep(100000);
        iteration++;
    }
    iteration = 0;

    if(died) gameEnd(player.name, player.score);
    else startMenu();
    return 0;
}
