// input and moving
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>

#include "input.h"
#include "globals.h"
#include "engine.h"

bool input(int &frame_counter, bool &stop, struct Tetromino &tetromino){
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
				refresh = rotate(tetromino); // rotates
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
	}
	return refresh; // nothing happened
}
