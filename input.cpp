#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#include "input.h"
#include "globals.h"
#include "engine.h"

bool move(struct Tetromino &tetromino, int dir) {
	int i, j, k = 0;
	bool move = true;

	// check collisions
	if (checkCollision(tetromino, 0, dir)){
		// the block moved
		return false;
	}

	clearSpace(tetromino); // clear tetromino in matrix
	
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
	int xnew[4];// new x positions
	int ynew[4];// new y positions
	int i;
	bool noCollide = true; // is there a collision

	clearSpace(tetromino); // clear tetromino in grid

	// rotation algorithms
	for (i = 0; i < 4; i++) {
		xnew[i] = tetromino.cx + tetromino.cy - tetromino.py[i];
		ynew[i] = tetromino.cy - tetromino.cx + tetromino.px[i];
	}

	//checking collisions
	for (i = 0; i < 4; i++) {
		if (grid[xnew[i]][ynew[i]] != 0 || xnew[i] < 0 || xnew[i] > 19 || ynew[i] < 0 || ynew[i] > 9) {
			noCollide = false;
		}
	}

	if (!noCollide) {
		drawTetromino(tetromino); // draw tetromino back to matrix
		return false; // no need to update
	}
	if (noCollide) {
		for (i = 0; i < 4; i++) {
			tetromino.px[i] = xnew[i];
			tetromino.py[i] = ynew[i];
		}
		drawTetromino(tetromino); // draw tetromino back to matrix
		return true; // no need to update
	}

}
END_OF_FUNCTION(rotate)

