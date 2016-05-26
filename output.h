#ifndef OUTPUT_H_
#define OUTPUT_H_
#include "globals.h"
// external varaibles in globals.cpp
extern int grid[GRID_X][GRID_Y];	// hold grid info
extern struct Block blockPos[GRID_X][GRID_Y];

extern BITMAP *buffer;
extern BITMAP *bGrid;
extern BITMAP *gameBackground;
extern BITMAP *bRed;
extern BITMAP *bYellow;
extern BITMAP *bCyan;
extern BITMAP *bBlue;
extern BITMAP *bPurple;
extern BITMAP *bGreen;
extern BITMAP *bOrange;

extern BITMAP *blocks[GRID_X * GRID_Y]; 

void initialiseBlockPos(); // initialise graphics grid for game
void initialisebmps(); // load all needed bmps
bool loadbmp(BITMAP **bptr, char file[20]); // checks and loads bmp

#endif
