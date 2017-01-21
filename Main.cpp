#include <allegro.h>
#include <stdio.h>

#include "RunningMan.h"

//global variables relating to timing
volatile long speed_counter = 0;
int game_timer = 0;

//main function
int main(int argc, char *argv[]) 
{
    //mandatory allegral functions
    allegro_init();
    install_keyboard();
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, WinWidth, WinHeight, 0, 0);
    
    //initializing the timer
    install_timer();
    LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);
	install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));

	//iniitalizing the player character and the laser
	Character player, laser;
	initializechar(player);
	laser.xpos = laserstart;
	laser.ypos = 0;
	laser.sprite[0] = load_bitmap("laser.bmp", NULL);
	
	//creating the buffer
	BITMAP *buffer = create_bitmap(WinWidth, WinHeight);
	
	//initializing the tile set
	Tile tileset[numoftiles];
	loadtiles(tileset);
	
    //initializing some variables and the map    
    //variables for the level the user is on, if the game should load a new level, and if the player has beat the game
    int collision = 0, level = 1, ifnewlvl = 1, win = 0; 
    Tile map[40][22];
    initializemap(map);
    
    //main game loop
    while (!key[KEY_ESC])
	{
        if (level == 13)//win condition
        {
            win = 1;    //sets a flag that the game was won and not quit
            break;      //breaks the main game loop if the game is won
        }
        
        //loads a new level if the player has entered a new level/resets the level if the player has died
        if (ifnewlvl == 1) loadmap(map, ifnewlvl, level);   
        
        //loop to ensure the game runs at a consistent speed/timed loop
		while (speed_counter > 0)
		{
            //checks if the player is touching the right of the screen
            if(player.xpos + player.sprite[0]->w > WinWidth)
	        {
                level++;                //moves the player to the next level
                if (level == 13) break; //if the player reaches the end, the loop is broken and the if statement checking win conditions
                ifnewlvl = 1;           //is immediately executed. also sets a flag that a new level needs to be loaded
                player.xpos = 0;        //the player is moved to the left of the screen
                laser.xpos = laserstart;//the laser is set to its starting position off the left side of the screen
                player.laser = 1;       //reactivates all lasers on the level
                break;
            }
            //checks if the player is touching the left of the screen
            if(player.xpos < 0) 
	        {
                player.xpos = 0;        //prevents the player from going back to already beaten levels
                break;
            }
            
            collision = 0;              //assumes the player is not colliding with something until the collision check
            
    		playermove(player);         //allows the player to move
    
            passivemovement(player);    //moves the player according to gravity
            
            if (level != 1 && player.xpos != 0)laser.xpos += 2;     //makes the laser obstacle move across the screen except on the instruction level
            
	        pcollision(player, collision, map);    //checks for player collision with map tiles
           
            if (laser.xpos + 10 > player.xpos) player.death = 1;    //checks for collision with the laser and flags the player as dead
            if (player.death == 1)      //checks if the player is dead either from collision with laser or from a tile in pcollision
            //if (key[KEY_D])           //testing mode where player can't die unless you press the D button
            {
                death(player);          //shows death screen and resets level when player dies
                laser.xpos = laserstart; 
                ifnewlvl = 1;
                break;
            }	    
            
            playergravity(player, collision);  //increases player vertical velocity if he's not touching a platform
                 	    
    	    speed_counter--;   //part of the timing system
        }
        drawbg(buffer, map, tileset, player, level);                      //draws the background onto the buffer
		drawplayer(buffer, player);                                       //draws the player to the buffer
		draw_sprite(buffer, laser.sprite[0], laser.xpos, laser.ypos);     //draws the laser to the buffer
		drawtoscreen(buffer, screen, game_timer, player);                 //draws the HUD to the buffer and then draws the buffer to the screen and clears the buffer
	}						
    
    //checks the flag for winning and displays a different message based on if the player won or quit
    if (win == 1) allegro_message("GG! You beat the Running Man in %d minutes and %d seconds with %d deaths!",
    (game_timer/60)/60, (game_timer/60)%60, player.deathcount); //tells the player how long they took and how many times they died
    else allegro_message("You have successfully quit the Running Man.");

    destroytiles(tileset, player);  //destroys the assets used to prevent memory leaks
    
    return 0;                       //program finished executing without error
}
END_OF_MAIN()

//function used to increment a variable for use in a timer and keep track of game time
void increment_speed_counter()
{
	speed_counter++; 
	game_timer++;
}
END_OF_FUNCTION(increment_speed_counter);

