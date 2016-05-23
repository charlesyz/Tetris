#ifndef INPUT_H_
#define INPUT_H_

bool move(struct Tetromino &tetromino, int dir); // checks if the user wants to move, moves. returns if the user moved.
bool drop(struct Tetromino &tetromino); // checks if the user wants to drop, drops.
bool rotate(struct Tetromino &tetromino); // function to rotate tetromino

#endif
