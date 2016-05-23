// input and moving
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#include "input.h"
#include "globals.h"
#include "engine.h"

void input(){
	int left = 20992; // left arrow
	int right = 21248; // right arrow
	int up = 21503; // up arrow
	int down = 21760; // down arrow
	// checking inputs. used this so it only triggers once.
	if (keypressed()) {
		switch(readkey()) {
			case left: // left arrow key
				refresh = move(current, -1); // move left
				check = false; // tell not to get anew tetromino YET
				break;
			case right: // right arrow key
				refresh = move(current, 1); // move right
				check = false;
				break;
			case up: // up arrow key
				refresh = rotate(current); // rotates
				check = false;
				break;
			case down: // down arrow key
				if (!stop) { // drops tetromino down
					stop = gravity(current); // move tetromino down by 1 space
					drawTetromino(current); // draw tetromino to grid
					frame_counter = 0; // reset frame counter
					// tell the game to refresh the screen
					refresh = true;
					}
				break;
		}
	}
}
