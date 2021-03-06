// Charles Zhang  ICS3U  mrs Cullum	 June 13, 2016
// all globals used in the project
#include <allegro.h>
#include "globals.h"

// globals
volatile long speed_counter = 0; // for game logic
int grid[GRID_X][GRID_Y];	// hold grid info
int rotateCounter = 0; // counter for number of rotates
// x and y values of all blocks (for grpahics output)
struct Block blockPos[GRID_X][GRID_Y];

// bitmaps
BITMAP *buffer = NULL;
BITMAP *bGrid = NULL;
BITMAP *gameBackground = NULL;
BITMAP *mainMenu = NULL;
BITMAP *helpMenu = NULL;
BITMAP *creditsMenu = NULL;
BITMAP *pauseMenu = NULL;
BITMAP *lost = NULL;

BITMAP *bRed = NULL;
BITMAP *bYellow = NULL;
BITMAP *bCyan = NULL;
BITMAP *bBlue = NULL;
BITMAP *bPurple = NULL;
BITMAP *bGreen = NULL;
BITMAP *bOrange = NULL; 

BITMAP *jTetromino = NULL;
BITMAP *lineTetromino = NULL;
BITMAP *lTetromino = NULL;
BITMAP *oTetromino = NULL;
BITMAP *sTetromino = NULL;
BITMAP *tTetromino = NULL;
BITMAP *zTetromino = NULL;

BITMAP *blocks[GRID_X * GRID_Y]; 

// sound samples;
SAMPLE *sample_complete = NULL;
SAMPLE *sample_backgroundmusic = NULL;
SAMPLE *sample_drop = NULL;
SAMPLE *sample_fall = NULL;
SAMPLE *sample_rotate = NULL;
