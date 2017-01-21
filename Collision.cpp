#include <allegro.h>
#include <stdio.h>

#include "RunningMan.h"

//function that chaecks the player's collision with map elements
void pcollision(Character &player, int &collision, Tile map[40][22])
{
    int i = 0, j = 0;
    
    //checks the collision of the player character with every other tile on the map
    for (i = 0 ; i < 40 ; i++)
    {
        for (j = 0 ; j < 22 ; j++)
        {
		    //ignores the collision check if the tile is not an interactive tile/is an empty tile
        	if (map[i][j].id != 48)
            {        	
                //checks for upward collision (e.g. if the player hits a tile above them)	
                if (player.ypos>map[i][j].ypos && player.yspeed < 0)
                {
                    //if the collision is detected...
        			if ((map[i][j].ypos + 32 - player.ypos) > player.yspeed 
        			&& (map[i][j].xpos - player.xpos) > -32 && (map[i][j].xpos - player.xpos) < 32)
        			{
                        //if the tile is a switch tile the laser on the level is turned off
                        if (map[i][j].id == 37) player.laser = 0;
                        //if the tile is a spike or a laser the player is killed
                        if (map[i][j].id == 33 || map[i][j].id == 42 || map[i][j].id == 43 || map[i][j].id == 62 || map[i][j].id == 25 || map[i][j].id == 60) player.death = 1;
        				//makes sure that the switch does not physically impede the player
                        else if (map[i][j].id != 37)
                        {
                            player.ypos = map[i][j].ypos + 32;  //sets the player location to under the tile	
        				    player.yspeed = gravity;        //makes the player fall immediately for a smoother experience
                        }
                    }
        		}
        		
        		//checks for downward collision (e.g. if the player is standing on a platform)
        		if (player.ypos<map[i][j].ypos && player.yspeed >=0)
                {
                    //see comments for above
        			if (((map[i][j].ypos)-(player.ypos + 32)) < player.yspeed 
        			&& (map[i][j].xpos - player.xpos) > -32 && (map[i][j].xpos - player.xpos) < 32)
        			{
                        if (map[i][j].id == 37) player.laser = 0;
                        if (map[i][j].id == 33 || map[i][j].id == 42 || map[i][j].id == 43 || map[i][j].id == 62 || map[i][j].id == 25 || map[i][j].id == 60) player.death = 1;
        				else if (map[i][j].id != 37)
                        {   player.ypos = map[i][j].ypos - 32 ;
        				    collision = 1;          //flags the player as standing on a platform
        				    player.jumptime = 0;    //allows the player to jump
                        }
                    }
        		}   
                
                //checks for right collision 
                if (player.xpos<map[i][j].xpos && player.xspeed > 0)
                {
                    //see comments above
        			if (((map[i][j].xpos)-(player.xpos + 32)) < player.xspeed
        			&& (map[i][j].ypos - player.ypos) > -32 && (map[i][j].ypos - player.ypos) < 32)
        			{
                        if (map[i][j].id == 37) player.laser = 0;
        				if (map[i][j].id == 33 || map[i][j].id == 42 || map[i][j].id == 43 || map[i][j].id == 62 || map[i][j].id == 25 || map[i][j].id == 60) player.death = 1;
                        else if (map[i][j].id != 37) player.xpos = map[i][j].xpos - 32 ;
                    }
        		}
                
                //checks for left collision
                if (player.xpos>map[i][j].xpos && player.xspeed < 0)
                {
                    //see comments above
        			if ((map[i][j].xpos + 32 - player.xpos) > player.xspeed 
        			&& (map[i][j].ypos - player.ypos) > -32 && (map[i][j].ypos - player.ypos) < 32 || map[i][j].id == 25 || map[i][j].id == 60)
        			{
        				if (map[i][j].id == 37) player.laser = 0;
        				if (map[i][j].id == 33 || map[i][j].id == 42 || map[i][j].id == 43 || map[i][j].id == 62) player.death = 1;
                        else if (map[i][j].id != 37) player.xpos = map[i][j].xpos + 32;
                    }
        		}          		
        	}
        }
	}
}
