// Charles Zhang  ICS3U  mrs Cullum	 June 13, 2016
// header file for outpu.h
#ifndef OUTPUT_H_
#define OUTPUT_H_
#include "globals.h"
// external varaibles in globals.cpp
extern int grid[GRID_X][GRID_Y];	// hold grid info
extern struct Block blockPos[GRID_X][GRID_Y];

extern BITMAP *buffer;
extern BITMAP *bGrid;
extern BITMAP *gameBackground;
extern BITMAP *mainMenu;
extern BITMAP *helpMenu;
extern BITMAP *creditsMenu;
extern BITMAP *pauseMenu;
extern BITMAP *lost;

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

// sound samples
extern SAMPLE *sample_complete;
extern SAMPLE *sample_backgroundmusic;
extern SAMPLE *sample_drop;
extern SAMPLE *sample_fall;
extern SAMPLE *sample_rotate;

// functions
void initialiseBlockPos(); // initialise graphics grid for game
void destroybmps(); // destroy all bmps
void destroysamples(); // destroys all samples
void initialisebmps(); // load all needed bmps
void initialisesamples(); // loads all needed samples
bool loadbmp(BITMAP **bptr, char const file[20]); // checks and loads bmp
bool loadsample(SAMPLE **fptr, char const fileName[20]); // checks and loads samples
void outputGame(struct Tetromino hold, struct Tetromino next, int score, int lines, int level); // output game elements and graphics
void scoreUpdate(int &lines, int &score, int &level, int numComplete);  // score function
void speed(int &delay, int level); // changes speed based on level
int highScore(int score); // highscore function

#endif
