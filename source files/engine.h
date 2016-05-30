#ifndef ENGINE_H_
#define ENGINE_H_
#include "globals.h"

// go to globals.cpp
extern volatile long speed_counter;
extern int grid[GRID_X][GRID_Y];
extern int rotateCounter;
// function prototyping
struct Tetromino randTetromino(); // get random tetromino
void clearTetromino(struct Tetromino &structure); // clear tetromino
void clearMatrix(); // clears game matrix
void getTetromino(struct Tetromino &nextTetromino, struct Tetromino &tetromino); //assigns next tetromino to current, gets new buffer tetromino
void drawTetromino(struct Tetromino tetromino); // draws current tetromino to matrix
void clearSpace(struct Tetromino tetromino); // clears current tetromino in the matrix (used before moving the tetromino
bool gameOver(struct Tetromino tetromino); // checks if gameover
bool isComplete(int line); // checks what lines are complete
void complete(int line); //moves all spaces down above the completed line
bool checkCollision(struct Tetromino tetromino, int dirx, int diry); // checks for collision, returns true or false.
int aInit(); // initialises allegro and keyboard etc


#endif
