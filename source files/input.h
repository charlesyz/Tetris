#ifndef INPUT_H_
#define INPUT_H_
#include "engine.h" // needed for check collision function & others

bool input(bool &canSwap, bool &pause,int delay, int &frame_counter, bool &stop, struct Tetromino &tetromino, struct Tetromino &hold, struct Tetromino &next); // check user inputs, return if there was movement
bool move(struct Tetromino &tetromino, int dir); // checks if the user wants to move, moves. returns if the user moved.
bool rotate(struct Tetromino &tetromino); // function to rotate tetromino
void drop(struct Tetromino &tetromino); // checks if the user wants to drop, drops.
bool gravity(struct Tetromino &tetromino); // moves block down with gravity
#endif
