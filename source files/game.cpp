// main game function
#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include "engine.h"
#include "input.h"
#include "globals.h"
#include "output.h"

bool game() {
	struct Tetromino current; // current moving tetromino,
	struct Tetromino next; // curent buffer tetromino
	bool stop = false; //did the tetromino collide
	bool refresh = true; // should the game refresh the screen
	bool lose = false; // is the game over
	bool check = false; // should the game recheck
	bool pause = false;
	int level = 0;
	int score = 0;
	int lines = 0;
	int delay = 80;
	int frame_counter = 0;
	int input_counter = 0;
	int reset_counter = 0; // timer for a delay to get a new tetromino
	int completed[4]; // completed lines
	int linesComplete; // # of lines completed at a time
	int i, j;

	srand(time(NULL)); //random number seed

	// initialise blockPos
	initialiseBlockPos();

	// create blitmap, blit game backgroudn to buffer
	buffer = create_bitmap(400,600);

	// clear tetrominos and game grid
	clearTetromino(current);
	clearTetromino(next);
	clearMatrix();

	current = randTetromino(); // getting a new tetromino
	next = randTetromino(); // getting a new buffer tetromino

	// print tetromino to grid
	clearSpace(current);
	drawTetromino(current);

	while(!key[KEY_ESC]) { //If the user hits escape, quit the program{

		// reset check boolean
		check = true;
		// reset completed array
		for (i = 0; i < 4; i++) {
			completed[i] = -1;
		}

		//logic loop
		while(speed_counter > 0) {
			
			if (input_counter > 10){
				// checking inputs
				if (input(pause, delay, frame_counter, stop, current)) {
					check = false;
					refresh = true;
				}
				// reset input_counter
				input_counter = 0;
				clear_keybuf();
			}
			
			// if the game should refresh the screen
			if (refresh) {
				// reset refresh
				refresh = false;
				
				outputGame(next, score, lines, level);
				
				system("cls");
				printf("%d", delay);

			}
			
			// if there is a collision, check if lines are complete
			if (stop && check) {
				j = 0; // set j to 0
				linesComplete = 0; // reset lines complete
				
				if (reset_counter > 25){
					// check if line is complete
					for (i = 0; i < 20; i++) {
						if (isComplete(i)) {
							completed[j] = i;
							j++;
							linesComplete++; // increment number of lines complete
						}
					}
					// move down completed lines
					for (i = 0; i < 4; i++) {
						if (completed[i] != -1) {
							complete(completed[i]);
							refresh = true;
							frame_counter = 0; // reset frame counter
						}
					}
					// increase score
					if (linesComplete > 0) {
						scoreUpdate(lines, score, level, linesComplete);
					}
					 // get a new tetromino
					getTetromino(next, current);
					
					if (!gameOver(current)) {
						// draw tetromino to grid
						drawTetromino(current);
						// reset stop
						stop = false;
						// tell the game to refresh the screen
						refresh = true;
					}
					// game is over
					else {
						lose = true;
					}
					
					reset_counter = 0;
				}
				
				else{
					reset_counter++;
				}
			}

			// increment frame counter, decrement speed counter
			frame_counter++;
			speed_counter--;
			input_counter++;
		}
		
		// if the user wants to pause
		if (pause){
			allegro_message("You are paused. Press OK to unpause");
			pause = false;
		}

		// double check collisions
		if (stop) {
			stop = checkCollision(current, 1, 0);
			drawTetromino(current);
		}

		// every "delay", run gravity function
		if (frame_counter > delay && !stop) {
			stop = gravity(current); // move tetromino down by 1 space
			frame_counter = 0; // reset frame counter

			// tell the game to refresh the screen
			refresh = true;
		}

		// update delay
		speed(delay, level);

		// if game over
		if (lose) {
			allegro_message("GAME OVER! press okay to play again");
			return true;
		}
	}
	return false;
}
END_OF_FUNCTION(game)
