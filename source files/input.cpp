// input and moving/tetromino manipulation
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#include "input.h"
#include "globals.h"
#include "engine.h"

bool input(int delay, int &frame_counter, bool &stop, struct Tetromino &tetromino){
	bool refresh = false;
	// checking inputs. used this so it only triggers once.
	if (keypressed()) {
		switch(readkey()) {
			case 20992: // left arrow key 20992
				refresh = move(tetromino, -1); // move left
				break;
			case 21248: // right arrow key
				refresh = move(tetromino, 1); // move right
				break;
			case 21504: // up arrow key
				if (rotateCounter < 5){
					if (frame_counter < delay - 1 && !stop){
					refresh = rotate(tetromino); // rotates
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
		}
		clear_keybuf();
	}
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

	
	collide = checkCollision(newTetromino, 0, 0);
	
	// if there is a collision
	if (collide) {
		drawTetromino(tetromino); // draw tetromino back to matrix
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
