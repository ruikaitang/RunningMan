#include <allegro.h>
#include <stdio.h>
#include <string.h>

#include "RunningMan.h"

//destroys assets used before the program exits
void destroytiles(Tile tileset[numoftiles], Character &player)
{
    int i = 0;
    
    for (i = 0 ; i < 64 ; i++) destroy_bitmap(tileset[i].sprite);   //uses a for loop to destroy all the tiles
    
    for (i = 0 ; i < 17 ; i++) destroy_bitmap(player.sprite[i]);    //uses a for loop to destroy all the player sprites
    
}

//draws the number of deaths and timer onto the buffer, and then blits the buffer to the screen
void drawtoscreen(BITMAP *buffer, BITMAP *screen, int game_timer, Character player)
{
    //blits the time elapsed and the number of deaths onto the buffer as an HUD in the top left corner of the screen
    textprintf_ex(buffer, font, 5, 5, makecol(255, 0, 0), -1, "Time: %d minutes %d seconds", (game_timer/60)/60, (game_timer/60)%60);
	textprintf_ex(buffer, font, 5, 17, makecol(255, 0, 0), -1, "Deaths: %d", player.deathcount);
    blit(buffer, screen, 0, 0, 0, 0,WinWidth, WinHeight); 
	clear_bitmap(buffer);	
}
