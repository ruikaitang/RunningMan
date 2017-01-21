//header file to organize constants, structures, and functions
//constants allow for easy tweaking of the game
#ifndef _RunningMan_H
#define _RunningMan_H

#define WinWidth 1280       //should not be changed sue to fixed number of tiles in map
#define WinHeight 704       //should not be changed sue to fixed number of tiles in map
#define gravity 0.5         //can be a float
#define movespeed 7         //player's movement speed
#define jumpspeed -10       //player's jump speed
#define constjumptime 500   //a "cooldown" for the jump ability
#define numoftiles 64       //the number of tiles in the tileset used
#define laserstart -150     //how far offstage the laser obstacle starts

//data structures
//structure for the player character
struct Character {
    BITMAP *sprite[17]; //sprites used for animation
    int xpos;           //player's horizontal position 
    int ypos;           //player's vertical position
    float xspeed;       //player's horizontal speed
    float yspeed;       //player's vertical speed
    int jumptime;       //how much time the player has left before they can jump
    int death;          //variable for if player is dead or not
    int deathcount;     //counts the number of deaths
    int laser;          //determines if laser is disabled or not
    int spritenum;      //used for switching between sprites for animation
};

//structure for the tiles in the game
struct Tile {
    BITMAP *sprite;     //the tile's appearance
    int id;             //a number the game uses to determine what type of tile it is
    int xpos;           //the tile's horizontal position
    int ypos;           //the tile's vertical position
};


//functions in the game
//resets the level when the player dies
void death(Character &player);
//destroys assets used before the program exits
void destroytiles(Tile tileset[numoftiles], Character &player);
//draws the background
void drawbg(BITMAP *buffer, Tile map[40][22], Tile tileset[numoftiles], Character player, int level);
//draws the player onto the buffer
void drawplayer(BITMAP *buffer, Character &player);
//draws the number of deaths and timer onto the buffer, and then blits the buffer to the screen
void drawtoscreen(BITMAP *buffer, BITMAP *screen, int game_timer, Character player);
//function used to increment a variable for use in a timer and keep track of game time
void increment_speed_counter();
//initializes the properties of the player character
void initializechar(Character &player);
//initializes the map array (blank bitmaps created for their sprite)
void initializemap(Tile map[40][22]);
//loads the map from the text file
void loadmap(Tile map[40][22], int &ifnewlevel, int level);
//loads the tiles in from a spritesheet
void loadtiles(Tile tileset[numoftiles]);
//moves the player in accordance to gravity
void passivemovement(Character &player);
//function that chaecks the player's collision with map elements
void pcollision(Character &player, int &collision, Tile map[40][22]);
//allows for keyboard input to move the character
void playermove(Character &player);
//causes player to accelerate downwards if they are not standing on a platform
void playergravity(Character &player, int collision);

#endif
