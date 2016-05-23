#ifndef TETRIS_H_
#define TETRIS_H_

#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>

#define GRID_X 20
#define GRID_Y 10

// initializing structure
struct Tetromino {
	char shape; // shape of the tetromino
	int colour; // colour of tetromino
	int px[4]; // position of 4 blocks
	int py[4]; // position of 4 blocks
	float cx; // position of centre
	float cy; // position of centre
};

// function prototyping
void increment_speed_counter();
struct Tetromino randTetromino(); // get random tetromino
void clearTetromino(struct Tetromino &structure); // clear tetromino
void clearMatrix(); // clears game matrix
bool game(); // main game
int aInit(); // initialises allegro and keyboard etc
void getTetromino(struct Tetromino &nextTetromino, struct Tetromino &tetromino); //assigns next tetromino to current, gets new buffer tetromino
void drawTetromino(struct Tetromino tetromino); // draws current tetromino to matrix
void clearSpace(struct Tetromino tetromino); // clears current tetromino in the matrix (used before moving the tetromino)
bool gravity(struct Tetromino &tetromino); // moves block down with gravity
bool gameOver(struct Tetromino tetromino); // checks if gameover
bool move(struct Tetromino &tetromino, int dir); // checks if the user wants to move, moves. returns if the user moved.
bool drop(struct Tetromino &tetromino); // checks if the user wants to drop, drops.
bool rotate(struct Tetromino &tetromino); // function to rotate tetromino
bool isComplete(int line); // checks what lines are complete
void complete(int line); //moves all spaces down above the completed line
void scoreUpdate(int &lines, int &score, int &level, int numComplete);  // score function
void speed(int &delay, int level); // changes speed based on level
bool checkCollision(struct Tetromino tetromino, int dirx, int diry); // checks for collision, returns true or false.

bool loadbmp(BITMAP **bptr, char file[20]); // checks and loads bmp
void highScore(int &high, int score); // highscore function

#endif
