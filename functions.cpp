#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

void increment_speed_counter() {
	speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter)

void clearTetromino(struct Tetromino &structure) {
	int i;

	// clearing structure
	structure.shape = ' ';
	for (i = 0; i < 4; i++) {
		structure.px[i] = 0;
		structure.py[i] = 0;
	}
	structure.colour = 0;
	structure.cx = 0;
	structure.cy = 0;
}
END_OF_FUNCTION(clearTetromino)

void clearMatrix() {
	int i;
	int j;
	//resetting the matrix
	for (i = 0; i < GRID_X; i++) {
		for (j = 0; j < GRID_Y; j++) {
			grid[i][j] = 0;
		}
	}
}
END_OF_FUNCTION(clearMatrix)

struct Tetromino randTetromino() {
	struct Tetromino newTetromino;
	int i;

	// getting a random number between 1 and 7
	newTetromino.colour = rand() % 7 + 1;

	switch(newTetromino.colour) {

			// if the tetromino is a l shaped tetromino (cyan)
		case 1:
			newTetromino.shape = 'l';
			for (i = 0; i < 4; i++) {
				newTetromino.px[i] = 1; // setting each block's x coordinate to 0
				newTetromino.py[i] = 3 + i; // setting each block's y coordinate
			}
			// setting centre of tetromino
			newTetromino.cx = 0.5;
			newTetromino.cy = 4.5;
			break;

			// O shaped tetromino (yellow)
		case 2:
			newTetromino.shape = 'O';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 0;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 4;
			newTetromino.py[1] = 5;
			newTetromino.py[2] = 4;
			newTetromino.py[3] = 5;
			// setting centre of tetromino
			newTetromino.cx = 0.5;
			newTetromino.cy = 4.5;
			break;

			// T shaped tetromino (purple)
		case 3:
			newTetromino.shape = 'T';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 1;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 4;
			newTetromino.py[1] = 3;
			newTetromino.py[2] = 4;
			newTetromino.py[3] = 5;
			// setting centre of tetromino
			newTetromino.cx = 1;
			newTetromino.cy = 4;
			break;

			// S shaped tetromino(green)
		case 4:
			newTetromino.shape = 'S';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 0;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 4;
			newTetromino.py[1] = 5;
			newTetromino.py[2] = 3;
			newTetromino.py[3] = 4;
			// setting centre of tetromino
			newTetromino.cx = 1;
			newTetromino.cy = 4;
			break;

			// Z shaped tetromino(red)
		case 5:
			newTetromino.shape = 'Z';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 0;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 3;
			newTetromino.py[1] = 4;
			newTetromino.py[2] = 4;
			newTetromino.py[3] = 5;
			// setting centre of tetromino
			newTetromino.cx = 1;
			newTetromino.cy = 4;
			break;

			// J shaped tetromino(blue)
		case 6:
			newTetromino.shape = 'J';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 1;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 3;
			newTetromino.py[1] = 3;
			newTetromino.py[2] = 4;
			newTetromino.py[3] = 5;
			// setting centre of tetromino
			newTetromino.cx = 1;
			newTetromino.cy = 4;
			break;
			// L shaped tetromino(blue)
		case 7:
			newTetromino.shape = 'J';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 1;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 5;
			newTetromino.py[1] = 3;
			newTetromino.py[2] = 4;
			newTetromino.py[3] = 5;
			// setting centre of tetromino
			newTetromino.cx = 1;
			newTetromino.cy = 4;
			break;
	}

	return newTetromino;
}
END_OF_FUNCTION(randTetromino)

int aInit() {
	allegro_init(); // Initialize Allegro
	install_keyboard(); // Initialize keyboard routines
	install_mouse(); // Initialize mouse

	//Tell allegro to install the timer routines
	install_timer();
	LOCK_VARIABLE(speed_counter); //Used to set the timer - which regulates the game's speed
	LOCK_FUNCTION(increment_speed_counter);	// lock the function which increments the speed counter.

	install_int_ex(increment_speed_counter, BPS_TO_TIMER(100)); //Set BPS
	set_color_depth(desktop_color_depth()); // Set the color depth

	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 400,600,0,0); //Change  graphics mode to 400 x 600
	show_mouse(screen);

	return 0;
}
END_OF_FUNCTION(aInit)

void getTetromino(struct Tetromino &nextTetromino, struct Tetromino &tetromino) {
	tetromino = nextTetromino;
	nextTetromino = randTetromino(); // getting a new buffer tetromino
}
END_OF_FUNCTION(getTetromino)

void drawTetromino(struct Tetromino tetromino) {
	int i;

	for (i = 0; i < 4; i++) {
		grid[tetromino.px[i]][tetromino.py[i]] = tetromino.colour; // assign the grid spaces a colour
	}
}
END_OF_FUNCTION(drawTetromino)

void clearSpace(struct Tetromino tetromino) {
	int i;

	for (i = 0; i < 4; i++) {
		grid[tetromino.px[i]][tetromino.py[i]] = 0; // clear x and y pos of the tetromino
	}
}
END_OF_FUNCTION(clearSpace)

bool gravity(struct Tetromino &tetromino) {

	int i, j, k = 0;

	// check collision
	if (checkCollision(tetromino[i], 1, 0)){
		// there was a collision
		return true;
	}
	
	clearSpace(tetromino);
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
END_OF_FUNCTION(gravity)

bool gameOver(struct Tetromino tetromino) {
	int i;
	// check if game over
	for (i = 0; i < 4; i++) {
		if (grid[tetromino.px[i]][tetromino.py[i]] != 0) {
			return true;
		}
	}
	return false;
}
END_OF_FUNCTION(gameOver)

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

bool isComplete(int line) {
	int i;

	// check if line has any 0s in it
	for (i = 0; i < 10; i++) {
		if (grid[line][i] == 0) {
			return false; // line is not complete
		}
	}
	// no 0s? return the line is complete;
	return true;
}
END_OF_FUNCTION(isComplete)

void complete(int line) {
	int i;

	// move lines above line down by 1
	while (line > 0) {
		for (i = 0; i < 10; i++) {
			grid[line][i] = grid[line - 1][i];
		}
		line--;
	}
	// empty last line
	for (i = 0; i < 10; i++) {
		grid[0][i] = 0;
	}
}
END_OF_FUNCTION(complete)

void scoreUpdate(int &lines, int &score, int &level, int numComplete){
	int i = 0;
	
	printf("TEST\n");
	
	lines += numComplete;
	if (lines % 10 == 0 && lines != 0){
		level++;
	}
	
	switch(numComplete){
		case 1:
			score += 50*(level + 1);
			break;
		case 2:
			score += 150*(level + 1);
			break;
		case 3:
			score += 350*(level + 1);
			break;
		case 4:
			score += 1000*(level + 1);
			break; 
	}
}
END_OF_FUNCTION(score)

void speed(int &delay, int level){
	if (level < 20){
		delay = 50 - (level + 1) * 5;
	}
}
END_OF_FUNCTION(speed)

bool checkCollision(struct Tetromino tetromino, int dirx, int diry){
	int i;
	bool collision = false;
	
	clearSpace(tetromino);
	for (i = 0; i < 4; i++) {
		// check if there is a collision
		if (grid[tetromino.px[i] + dirx][tetromino.py[i] + diry] != 0 && tetromino.px[i] + dirx > 20 && tetromino.py[i] + diry >= 0 && tetromino.py[i] + diry < 10){
			collision = true; // there is a collision
		}
	}
	drawTetromino(tetromino);
	return collision;
}
