// Charles Zhang  ICS3U  mrs Cullum	 June 13, 2016
// main menu and game
#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include "engine.h"
#include "input.h"
#include "globals.h"
#include "output.h"

bool menu(int &level){
	bool lock = false;
	int counter = 0;
	int wait_counter = 0;
	
	// create blitmap, blit main menu to buffer
	buffer = create_bitmap(400,600);
	blit(mainMenu, buffer, 0, 0, 0, 0, 400, 600);
	
	while (!key[KEY_Q]){
		while(speed_counter > 0) {
			
			// reset lock every 200 ms	
			if (counter > 20){
				lock = false;
				counter = 0;
			}
			
			// checking for the player clicking on buttons
			if (mouse_b & 1 && !lock){
				// if play game button
				if (mouse_x > 100 && mouse_x < 320 && mouse_y > 210 && mouse_y < 259){
					return true;
				}
				// if left arrow button, decrement level
				else if (mouse_x > 111 && mouse_x < 129 && mouse_y > 291 && mouse_y < 314 && level > 0){
					level--;
				}
				// if right arrow button, increment level
				else if (mouse_x > 291 && mouse_x < 398 && mouse_y > 291 && mouse_y < 314 && level < 19){
					level++;
				}
				// if help button
				else if (mouse_x > 100 && mouse_x < 320 && mouse_y > 345 && mouse_y < 398){
					while (!key[KEY_BACKSPACE]){
						blit(helpMenu, buffer, 0, 0, 0, 0, 400, 600);
						blit(buffer, screen, 0, 0, 0, 0, 400, 600);
					}
				}
				// if credits button
				else if (mouse_x > 100 && mouse_x < 320 && mouse_y > 415 && mouse_y < 466){
					while (!key[KEY_BACKSPACE]){
						blit(creditsMenu, buffer, 0, 0, 0, 0, 400, 600);
						blit(buffer, screen, 0, 0, 0, 0, 400, 600);
					}
				}
				
				lock = true;
			}
			speed_counter--;
			counter++;
			
			// print to screen
			blit(mainMenu, buffer, 0, 0, 0, 0, 400, 600);
			textprintf_ex(buffer, font, 260, 300, makecol(0,0,0), -1, "%d", level + 1);
			blit(buffer, screen, 0, 0, 0, 0, 400, 600);
		}
	
	clear_keybuf();
	}
	
	return false;
}

bool game(int level) {
	struct Tetromino current; // current moving tetromino,
	struct Tetromino next; // curent buffer tetromino
	struct Tetromino hold; // hold tetromino
	bool stop = false; //did the tetromino collide
	bool refresh = true; // should the game refresh the screen
	bool lose = false; // is the game over
	bool check = false; // should the game recheck
	bool pause = false;
	bool canSwap = true;
	bool playsound = true;
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

	// clear tetrominos and game grid
	clearTetromino(current);
	clearTetromino(next);
	clearTetromino(hold);
	clearMatrix();

	current = randTetromino(); // getting a new tetromino
	next = randTetromino(); // getting a new buffer tetromino

	// print tetromino to grid
	clearSpace(current);
	drawTetromino(current);

	while(!key[KEY_ESC]) { //If the user hits escape, quit the program

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
				if (input(canSwap, pause, delay, frame_counter, stop, current, hold, next)) {
					check = false;
					refresh = true;
				}
				
				// reset input_counter
				input_counter = 0;
				clear_keybuf();
			}
			
			// if the game should refresh the screen, reprint the screen
			if (refresh) {
				// reset refresh
				refresh = false;
				
				outputGame(hold, next, score, lines, level);

			}
			
			// if there is a collision, check if lines are complete and do all score / compelte line related functions
			if (stop && check) {
				j = 0; // set j to 0
				linesComplete = 0; // reset lines complete
				
				// play sound only once
				if (playsound){
					// play  the fall sound
					play_sample(sample_fall, 255, 128, 1000, false);
					playsound = false;
				}
				
				if (reset_counter > 25){
					// check if line is complete
					for (i = 0; i < 20; i++) {
						if (isComplete(i)) {
							// play the complete sound
							play_sample(sample_complete, 255, 128, 1000, false);
							
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
					playsound = true;
					frame_counter = 0; // reset frame counter
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
		while (pause){
			// stop and resume background music with a pause between to prevent stuttering of the music
			stop_sample(sample_backgroundmusic);
			rest(170);
			allegro_message("You are paused. Press OK to unpause");
			rest(170);
			pause = false;
			play_sample(sample_backgroundmusic, 255, 128, 1000, true);
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
