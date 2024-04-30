# ENGG1340-RocketRampage

### Identification of Team Members
This project was made by:
* Meeth Jaswani
* Jaehue Chun
* Divyansh Tulsyan  
* Shreyansh Mishra  
* Cheung HonLung

### Game Description and Rules
A rocket-missle game implemented in C++ and ncurses for the Linux command line, for the final project of HKU's ENGG1340.
#### Instructions
* Use the left and right arrow keys to move the rocket and [A] key to shoot.  
* The goal is to destroy enemies with your missiles. 
* The player earns points each time a missile hits an enemy.
* The player has 5 Lives to accumulate as many points as possible.
* The player will lose a life if either enemy touches the rocket or goes beyond it. 
* The player gets 10 points for each enemy destroyed.
* As time goes on, the level of the game increases. If the player reaches level 6, it is considered as impossible stage, and the game continues until the player loses all life.

### Gameplay
https://github.com/tulsyandivyansh/ENGG1340--Rocket-Shooter/assets/62593950/761700d7-05b2-4b3e-9005-e5d6a6cfbd49

### Project Requirements
#### Generation of random game sets or events: 
    We randomised the generation of the enemy ships at the top of the screen, when the game starts.
#### Data structures for storing game status: 
    We use different classes to store the status of in-game objects like the missles, the rocket, and the level. 
    The player data is also stored in a class at any given point.
#### Dynamic memory management:
    We utilize dynamic memory allocation to create and change instances of the gameWindow, instructions_window, 
    infoWindows and in each round of gameplay.
#### File input/output:
     To save scores on the leaderboard, a save file with player name and score is used.
#### Program codes in multiple files:
    Multiple files are used.



### Project Requirements

| Coding Requirements                      | Feature                                                                                                    |
| ---------------------------------------- | ---------------------------------------------------------------------------------------------------------- |
| Generation of Random Events.              | We randomised the generation of the enemy ships at the top of the screen, when the game starts.             |   
| Data Structures for Storing Game Status  | We use different classes to store the status of in-game objects like the missles, the rocket, and the level. The player data is also stored in a class at any given point.                                                                                               |
| Dynamic Memory Management (DMM)          | We utilize dynamic memory allocation to create and change instances of the gameWindow, commandsWindow, infoWindows and in each round of gameplay. |
| File Input/Output                        | We use file handling to maintain a record of the top scores in the leaderboard.                          |
| Multiple Files of Program Code           | We use separate files for handling different parts of the game - the gameplay, the menu, and the highscores functionality, which are joined together by main.cpp.                                                                                                   |


### External Libraries
`ncurses` - The ncurses library was used to draw console graphics smoothly instead of having to redraw the whole window every time the game updates.

### Instructions for Building
* Clone the project repository: `git clone https://github.com/tulsyandivyansh/ENGG1340--Rocket-Rampage.git`
* Navigate to the project directory: `cd ENGG1340--Rocket-Rampage/`
* Make the game: `make rocket`
* Execute the game: `./rocket`
* To remove the game, run `make clean`
