// main game function
#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include "engine.h"
#include "input.h"
#include "globals.h"
#include "output.h"

// go to globals.cpp
extern volatile long speed_counter;
extern int grid[GRID_X][GRID_Y];

bool game() {
	struct Tetromino current; // current moving tetromino,
	struct Tetromino next; // curent buffer tetromino
	bool stop = false; //did the tetromino collide
	bool refresh = false; // should the game refresh the screen
	bool lose = false; // is the game over
	bool check = false; // should the game recheck
	bool getnew = false;
	int level = 0;
	int score = 0;
	int lines = 0;
	int delay = 50;
	int frame_counter = 0;
	int completed[4]; // completed lines
	int linesComplete; // # of lines completed at a time
	int i, j;
	
	// initialise blockPos
	initialiseBlockPos();
	
	// create blitmap, blit game backgroudn to buffer
	buffer = create_bitmap(400,600);
	blit(gameBackground, buffer, 0, 0, 0, 0, 400, 600);

	// clear tetrominos and game grid
	clearTetromino(current);
	clearTetromino(next);
	clearMatrix();

	current = randTetromino(); // getting a new tetromino
	next = randTetromino(); // getting a new buffer tetromino

	// print tetromino to grid
	clearSpace(current);
	drawTetromino(current);

	//TEMPORARY PRINTING
	system("cls");
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 10; j++) {
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}

	while(!key[KEY_ESC]) { //If the user hits escape, quit the program{

		// reset check boolean
		check = true;
		// reset completed array
		for (i = 0; i < 4; i++) {
			completed[i] = -1;
		}

		//logic loop
		while(speed_counter > 0) {
			// checking inputs
			if (input(frame_counter, stop, current)){
				check = false;
				refresh = true;
			}
			
			// if the game should refresh the screen
			if (refresh) {
				// reset refresh
				refresh = false;
				
				// reset bgrid
				loadbmp(&bGrid, "game_grid.bmp");
				
				// check elements of grid for colours
				for (int i = 0; i < 20; i++) {
					for (int j = 0; j < 10; j++) {
						switch (grid[i][j]){
							// blit that colour block to the corresponding block in the grid
							case 1:
								blit(bCyan, bGrid, 0, 0, blockPos[i][j].py, blockPos[i][j].px, 16, 16);
								break;
							case 2:
								blit(bYellow, bGrid, 0, 0, blockPos[i][j].py, blockPos[i][j].px, 16, 16);
								break;
							case 3:
								blit(bPurple, bGrid, 0, 0, blockPos[i][j].py, blockPos[i][j].px, 16, 16);
								break;
							case 4:
								blit(bGreen, bGrid, 0, 0, blockPos[i][j].py, blockPos[i][j].px, 16, 16);
								break;
							case 5:
								blit(bRed, bGrid, 0, 0, blockPos[i][j].py, blockPos[i][j].px, 16, 16);
								break;
							case 6:
								blit(bBlue, bGrid, 0, 0, blockPos[i][j].py, blockPos[i][j].px, 16, 16);
								break;
							case 7:
								blit(bOrange, bGrid, 0, 0, blockPos[i][j].py, blockPos[i][j].px, 16, 16);
								break;
						}
					}
				}
				
				// blit the grid to the buffer then the buffer to the screen
				blit(bGrid, buffer, 0, 0, 35, 140, bGrid -> w, bGrid -> h);	
				blit(buffer, screen, 0, 0, 0, 0, 400, 600);	
				
				//TEMPORARY PRINTING
				system("cls");
				for (int i = 0; i < 20; i++) {
					for (int j = 0; j < 10; j++) {
						printf("%d", grid[i][j]);
					}
					printf("\n");
				}
				printf("score = %d\nlevel = %d\nlines = %d\nhighscore = %d\n", score, level, lines, highScore(score));
				
				
			}
			
			// increment frame counter, decrement speed counter
			frame_counter++;
			speed_counter--;
		}

		// double check collisions
		if (stop && !getnew) {
			stop = checkCollision(current, 1, 0);
		}
		
		// every "delay", run gravity function
		if (frame_counter > delay && !stop) {
			stop = gravity(current); // move tetromino down by 1 space
			frame_counter = 0; // reset frame counter

			// tell the game to refresh the screen
			refresh = true;
		}

		// if there is a collision, check if lines are complete
		if (frame_counter > delay && stop && check) {
			j = 0; // set j to 0
			linesComplete = 0; // reset lines complete
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
					getnew = true; // get a new tetormino
				}
			}
			// increase score
			if (linesComplete > 0){		
				scoreUpdate(lines, score, level, linesComplete);
			}
		}

		// if there is a collision, get a new tetromino and check for game over
		if (frame_counter > delay && stop) {  
			// check if it's game over
			if (check) {
				getTetromino(next, current); // get a new tetromino
				if (!gameOver(current)) {
					drawTetromino(current); // draw tetromino to grid
					// reset stop
					stop = false;
					// tell the game to refresh the screen
					refresh = true;
					getnew = false; 
				}
				// game is over
				else {
					lose = true;
				}
			}
			frame_counter = 0; // reset frame counter
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
