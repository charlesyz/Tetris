// input and moving/tetromino manipulation
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#include "input.h"
#include "globals.h"
#include "engine.h"

bool input(bool &canSwap, bool &pause,int delay, int &frame_counter, bool &stop, struct Tetromino &tetromino, struct Tetromino &hold, struct Tetromino &next){
	bool refresh = false;
	struct Tetromino temp; 
	
	// reset canSwap
	if (stop){
		canSwap = true;
	}
	
	// checking inputs. used this so it only triggers once.
	if (keypressed()) {
		switch(readkey()) {
			case 20992: // left arrow key
				refresh = move(tetromino, -1); // move left
				break;
			case 21248: // right arrow key
				refresh = move(tetromino, 1); // move right
				break;
			case 21504: // up arrow key
				// you can only rotate 5 times in a row, if it's not time for the tile to move by gravity, and if the tile isnt "stopped"
				if (rotateCounter < 5 && frame_counter < delay && !stop){
					refresh = rotate(tetromino); // rotates
					// if the piece was rotated, increment rotate counter
					if (refresh){
						rotateCounter++; // rotate counter resets on gravity
					}
				}
				break;
			case 19232: // spacebar drops tetromino
				drop(tetromino);
				refresh = true;
				break;
			case 21760: // down arrow key
				if (!stop) { // drops tetromino down if it isn't stopped
					stop = gravity(tetromino); // move tetromino down by 1 space
					frame_counter = 0; // reset frame counter
					// tell the game to refresh the screen
					refresh = true;
					}
				break;
			case 4208: // p key
				if (!pause){
					pause = true;
				}
				break;
			case 6778: // z key
				if (canSwap){
					// clear tetroimino from matrix
					clearSpace(tetromino);
					
					// swap hold and current if hold isn't empty
					if (hold.colour != 0){
						temp = hold;
						hold = tetromino;
						tetromino = temp;
					}
					else {
						hold = tetromino;
						getTetromino(next, tetromino);
					}
					
					// reset tetromino positions
					resetTetromino(tetromino);
					
					// draw tetromiono back to matrix
					drawTetromino(tetromino);
					canSwap = false;
				}	
				refresh = true;
				break;
		}
	}
	clear_keybuf();
	
	return refresh; // nothing happened
}

bool gravity(struct Tetromino &tetromino) {

	int i, j, k = 0;
	// reset rotateCounter
	rotateCounter = 0;
	
	// check collision
	if (checkCollision(tetromino, 1, 0)){
		drawTetromino(tetromino);
		// there was a collision
		return true;
	}
	else {
		// if there is no collision
		for(i = 0; i < 4; i++) {
			// move tetromino pieces down
			tetromino.px[i]++;
		}
		// move tetromino centre
		tetromino.cx++;
		drawTetromino(tetromino);
		
		return false;
	}
}
END_OF_FUNCTION(gravity)

bool move(struct Tetromino &tetromino, int dir) {
	int i, j, k = 0;

	// check collisions
	if (checkCollision(tetromino, 0, dir)){
		// the block did not move
		drawTetromino(tetromino);
		return false;
	}

	// if there is no collision
	for(i = 0; i < 4; i++) {
		// move tetromino pieces
		tetromino.py[i] += dir;
	}
	// move tetromino centre position
	tetromino.cy += dir;
	
	drawTetromino(tetromino); // draw tetromino to grid
	return true;
}
END_OF_FUNCTION(move)

bool rotate(struct Tetromino &tetromino) {
	struct Tetromino newTetromino = tetromino;
	int i;
	bool collide = false; // is there a collision

	clearSpace(tetromino); // clear tetromino in grid

	// rotation algorithms
	for (i = 0; i < 4; i++) {
		newTetromino.px[i] = tetromino.cx + tetromino.cy - tetromino.py[i];
		newTetromino.py[i] = tetromino.cy - tetromino.cx + tetromino.px[i];
	}
	
	// check collisions
	for (i = 0; i < 4; i++) {
		// check if there is a collision
		if (grid[newTetromino.px[i]][newTetromino.py[i]] != 0 || newTetromino.px[i] > 19
		    || newTetromino.py[i] < 0 || newTetromino.py[i] > 9){
			collide = true; // there is a collision
		}
	}
	
	//collide = checkCollision(newTetromino, 0, 0); DOESNT WORK FOR SOME REASON????
	
	// if there is a collision
	if (collide) {
		drawTetromino(tetromino); // draw tetromino back to matrix without changing
		return false; // no need to update
	}
	else if (!collide) {
		tetromino = newTetromino;
		drawTetromino(tetromino); // draw rotated tetrominoto matrix
		return true; // please update update
	}
}
END_OF_FUNCTION(rotate)

void drop(struct Tetromino &tetromino){
	// move tetromino down untill it cant move anymore
	while (!gravity(tetromino));
}
END_OF_FUNCTION(drop)
