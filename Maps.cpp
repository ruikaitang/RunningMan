#include <allegro.h>
#include <stdio.h>
#include <string.h>

#include "RunningMan.h"

//draws the background
void drawbg(BITMAP *buffer, Tile map[40][22], Tile tileset[numoftiles], Character player, int level)
{   
    //initializing some counter variables and variables for the coordinates of the tile on the grid
    int i = 0, j = 0, x = 0, y = 0;
    
    //blits an instructional background on the first level that lacks the sweeping laser
    if (level == 1)
    {
        BITMAP *info;
        //char txt[5] = ".bmp";                 //code to add a different background for each level
        //char filename[10] = "";               //just uncomment these 5 lines and remove the if (level == 1) statment
        //itoa(level, filename, 10);
        //strcat(filename, txt);
        //info = load_bitmap(filename, NULL);       
        info = load_bitmap("INSTRUCTIONS.bmp", NULL);   //comment this line out if you wish to load different background for different levels
        
        blit(info, buffer, 0, 0, 0, 0, WinWidth, WinHeight);    //blits and destroys the background
        destroy_bitmap(info);
    }
    
    //checks if lasers are disabled, and if they are changes all laser tiles to empty tiles
    if (player.laser == 0)
    {
        for (i = 0; i < 40 ; i++)
        {
            for ( j = 0 ; j < 22 ; j++)
            {
                if (map[i][j].id == 60 || map[i][j].id == 25) map[i][j].id = 48;
            }
        }
    }
    
    //checks the id of each tile in the 2D map array and blits the appropriate visual
    for (i = 0; i < 40 ; i++)
    {
        for ( j = 0 ; j < 22 ; j++)
        {
            //only blits if the tile is not empty
            if (map[i][j].id != 48) masked_blit(tileset[map[i][j].id].sprite, buffer, 0, 0, x, y, 32, 32);
            map[i][j].xpos = x;                 //marks where the map tile is to be used for collision detection
            map[i][j].ypos = y;
            if (x == 1248 && y == 672) break;   //breaks the loop if it reaches the last tile
            else if (x == 1248)                 //goes to the next line if the last tile on a line is reached
            {
                x = 0;
                y += 32;
            }
            else x += 32;                       //goes to blit the next tile
        }
    }
}
//loads the map from the text file
void loadmap(Tile map[40][22], int &ifnewlevel, int level)
{
    //The map files are stored as text files in the form of "n.txt"
    //where n is the level number. This block of code loads the appropriate level data
    FILE *info;
    char txt[5] = ".txt";
    char filename[10] = "";
    itoa(level, filename, 10);
    strcat(filename, txt);
    info = fopen(filename, "r");
    
    
    //transfers the level data from the text document to the map array
    int i = 0, j = 0, tileid = 0;
    for (i = 0; i < 40 ; i++)
    {
        for (j = 0; j < 22 ; j++)
        {
            fscanf(info, "%d,", &tileid);
            map[i][j].id = tileid - 1;      //tiling program is a bit weird and increments the tile ID by 1
        }                                   //when saving, so this accounts for that
    }
    
    ifnewlevel = 0;                         //after loading, flags the level as loaded so it is not constantly reloaded
}

//loads the tiles in from a spritesheet
void loadtiles(Tile tileset[numoftiles])
{
    //opens the spritesheet
    BITMAP *temp = load_bitmap("TEMPTILESET.bmp", NULL);
    int i = 0, x = 1, y = 1;
    
    //transfers the individual tiles to the tileset array
    for (i = 0 ; i < 100 ; i++)
    {
        tileset[i].sprite = create_bitmap(32, 32);
        masked_blit(temp, tileset[i].sprite, x, y, 0, 0, 32, 32);   //uses a different part of the spritesheet for each individual tile
        if (x == 232 && y == 232) break;    //stops the loop if the end of the spritesheet is reached
        else if (x == 232)                  //goes to the next row if the end of a row is reached
        {
            x = 1;
            y += 33;
        }
        else x += 33;                       //goes to the next tile
    }
    destroy_bitmap(temp);                   //destroys the spritesheet after the bitmaps are loaded into the tileset array
}

//initializes the map array (blank bitmaps created for their sprite)
void initializemap(Tile map[40][22])
{
    int i = 0, j = 0;
    
    //creates an empty bitmap for all the tiles on the map so that an actual image can be blitted later
    for (i = 0; i < 40 ; i++)
    {
        for (j = 0; j < 22 ; j++)
        {
            map[i][j].sprite = create_bitmap(32, 32);
            map[i][j].xpos = 0;
            map[i][j].ypos = 0;
        }
    }
}
