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

extern BITMAP *jTetromino;
extern BITMAP *lineTetromino;
extern BITMAP *lTetromino;
extern BITMAP *oTetromino;
extern BITMAP *sTetromino;
extern BITMAP *tTetromino;
extern BITMAP *zTetromino;

extern BITMAP *blocks[GRID_X * GRID_Y]; 

// functions
void initialiseBlockPos(); // initialise graphics grid for game
void initialisebmps(); // load all needed bmps
bool loadbmp(BITMAP **bptr, char const file[20]); // checks and loads bmp
void outputGame(struct Tetromino next, int score, int lines, int level); // output game elements and graphics
void scoreUpdate(int &lines, int &score, int &level, int numComplete);  // score function
void speed(int &delay, int level); // changes speed based on level
int highScore(int score); // highscore function

#endif
