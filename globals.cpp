#include <allegro.h>
#include "globals.h"

// globals
volatile long speed_counter = 0; // for game logic
int grid[GRID_X][GRID_Y];	// hold grid info
// x and y values of all blocks (for grpahics output)
struct Block blockPos[GRID_X][GRID_Y];

BITMAP *buffer = NULL;
BITMAP *bGrid = NULL;
BITMAP *gameBackground = NULL;
BITMAP *bRed = NULL;
BITMAP *bYellow = NULL;
BITMAP *bCyan = NULL;
BITMAP *bBlue = NULL;
BITMAP *bPurple = NULL;
BITMAP *bGreen = NULL;
BITMAP *bOrange = NULL; 

BITMAP *blocks[GRID_X * GRID_Y]; 
