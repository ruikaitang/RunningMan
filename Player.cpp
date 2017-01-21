#include <allegro.h>

#include "RunningMan.h"

//resets the level when the player dies
void death(Character &player)
{
    player.xpos = 0;    //player is reset to left side of level near the bottom
    player.ypos = 640;
    player.death = 0;   //player is "revived"
    player.laser = 1;   //lasers are switched back on
    BITMAP *deathscreen = load_bitmap("deathscreen.bmp", NULL); //loads, shows, and destroys the deathscreen
    blit(deathscreen, screen, 0, 0, 0, 0, WinWidth, WinHeight);
    destroy_bitmap(deathscreen);
    clear_keybuf(); 
    readkey();          //waits for a key to be pressed before continuing
    player.deathcount++;//increments the death count of the player by 1
}

//draws the player onto the buffer
void drawplayer(BITMAP *buffer, Character &player)
{
    draw_sprite(buffer, player.sprite[player.spritenum], player.xpos, player.ypos);
}

//initializes the properties of the player character
void initializechar(Character &player)
{
    player.sprite[0] = load_bitmap("Character0.bmp", NULL);     //loads the sprites used to animate the character
    player.sprite[1] = load_bitmap("Character1.bmp", NULL);
    player.sprite[2] = load_bitmap("Character2.bmp", NULL);
    player.sprite[3] = load_bitmap("Character3.bmp", NULL);
    player.sprite[4] = load_bitmap("Character4.bmp", NULL);
    player.sprite[5] = load_bitmap("Character5.bmp", NULL);
    player.sprite[6] = load_bitmap("Character6.bmp", NULL);
    player.sprite[7] = load_bitmap("Character7.bmp", NULL);
    player.sprite[8] = load_bitmap("Character8.bmp", NULL);
    player.sprite[9] = load_bitmap("Character9.bmp", NULL);
    player.sprite[10] = load_bitmap("Character10.bmp", NULL);
    player.sprite[11] = load_bitmap("Character11.bmp", NULL);
    player.sprite[12] = load_bitmap("Character12.bmp", NULL);
    player.sprite[13] = load_bitmap("Character13.bmp", NULL);
    player.sprite[14] = load_bitmap("Character14.bmp", NULL);
    player.sprite[15] = load_bitmap("Character15.bmp", NULL);
    player.sprite[16] = load_bitmap("Character16.bmp", NULL);
	player.xpos = 32;
	player.ypos = 640;
	player.yspeed = 0;
	player.jumptime = 0;
	player.death = 0;
	player.deathcount = 0;
	player.laser = 1;
	player.spritenum = 0;
}

//moves the player in accordance to gravity
void passivemovement(Character &player)

{
    //casts player.yspeed as an int because it is originally a float and adds it to the player's current y position
    player.ypos += (int)player.yspeed;  
}

//allows for keyboard input to move the character
void playermove(Character &player)
{
    //checks for a key input of the up arrow or space and makes sure the player is able to jump
    if ((key[KEY_UP] || key[KEY_SPACE]) && player.jumptime == 0) 
	{ 
		player.yspeed = jumpspeed;          //changes the player velocity to an upwards direction
        player.jumptime = constjumptime;    //sets a cooldown for the jump timer
        return;                             //makes sure only one input is read at a time
	} 
	//checks for a key input of the right arrow
    if (key[KEY_RIGHT])
	{ 
        player.xpos += movespeed;           //moves the player to the right by a set amount
        player.xspeed = movespeed;          //flags the player as moving to the right
        //code to animate the player while running
        if (player.spritenum >= 7) player.spritenum = 0;
        else player.spritenum++;
        return;
	} 
	//see comments for above if statment
	if (key[KEY_LEFT])
	{ 
        player.xpos -= movespeed;
        player.xspeed = -movespeed;
        if (player.spritenum >= 15 || player.spritenum < 8) player.spritenum = 8;
        else player.spritenum++;
        return;
	}
	player.spritenum = 16; //if no input is received, the player defaults to its standing, unmoving sprite
}

//causes player to accelerate downwards if they are not standing on a platform
void playergravity(Character &player, int collision)
{
    if (collision == 0) player.yspeed += gravity;	   
}


