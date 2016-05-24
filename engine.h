#ifndef ENGINE_H_
#define ENGINE_H_

// function prototyping
struct Tetromino randTetromino(); // get random tetromino
void clearTetromino(struct Tetromino &structure); // clear tetromino
void clearMatrix(); // clears game matrix
void getTetromino(struct Tetromino &nextTetromino, struct Tetromino &tetromino); //assigns next tetromino to current, gets new buffer tetromino
void drawTetromino(struct Tetromino tetromino); // draws current tetromino to matrix
void clearSpace(struct Tetromino tetromino); // clears current tetromino in the matrix (used before moving the tetromino)
bool gravity(struct Tetromino &tetromino); // moves block down with gravity
bool gameOver(struct Tetromino tetromino); // checks if gameover
bool isComplete(int line); // checks what lines are complete
void complete(int line); //moves all spaces down above the completed line
void scoreUpdate(int &lines, int &score, int &level, int numComplete);  // score function
void speed(int &delay, int level); // changes speed based on level
bool checkCollision(struct Tetromino tetromino, int dirx, int diry); // checks for collision, returns true or false.
bool move(struct Tetromino &tetromino, int dir); // checks if the user wants to move, moves. returns if the user moved.
bool rotate(struct Tetromino &tetromino); // function to rotate tetromino
int highScore(int score); // highscore function
void drop(struct Tetromino &tetromino); // checks if the user wants to drop, drops.

bool loadbmp(BITMAP **bptr, char file[20]); // checks and loads bmp

#endif
