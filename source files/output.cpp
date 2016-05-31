// all files to do with output, score, graphics, and sound
#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include "output.h"
#include "globals.h"

void outputGame(struct Tetromino next, int score, int lines, int level){
	
	// reset bgrid
	loadbmp(&bGrid, "bitmaps/game_grid.bmp");
	
	// clear buffer
	clear(buffer);
	// blit background to buffer
	blit(gameBackground, buffer, 0, 0, 0, 0, 400, 600);
	
	// check elements of grid for colours
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			switch (grid[i][j]) {
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
	// print next tetromino
	switch (next.shape) {
		// blit that colour block to the corresponding block in the grid
		case 'l':
			blit(lineTetromino, buffer, 0, 0, 240, 160, 64, 32);
			break;
		case 'L':
			blit(lTetromino, buffer, 0, 0, 240, 160, 64, 32);
			break;
		case 'J':
			blit(jTetromino, buffer, 0, 0, 240, 160, 64, 32);
			break;
		case 'O':
			blit(oTetromino, buffer, 0, 0, 240, 160, 64, 32);
			break;
		case 'T':
			blit(tTetromino, buffer, 0, 0, 240, 160, 64, 32);
			break;
		case 'S':
			blit(sTetromino, buffer, 0, 0, 240, 160, 64, 32);
			break;
		case 'Z':
			blit(zTetromino, buffer, 0, 0, 240, 160, 64, 32);
		break;
	}
	// printing scores
	textprintf_ex(buffer, font, 210, 240, makecol(0,0,0), -1, "%d", score);
	textprintf_ex(buffer, font, 210, 310, makecol(0,0,0), -1, "%d", lines);
	textprintf_ex(buffer, font, 210, 370, makecol(0,0,0), -1, "%d", level + 1);
	textprintf_ex(buffer, font, 210, 440, makecol(0,0,0), -1, "%d", highScore(score));

	// blit the grid to the buffer then the buffer to the screen
	blit(bGrid, buffer, 0, 0, 35, 140, bGrid -> w, bGrid -> h);
	blit(buffer, screen, 0, 0, 0, 0, 400, 600);
}


void initialiseBlockPos(){
	int i;
	int j;
	// initialise matrix blocks
	for (i = 0; i < 20; i++){
		for (j = 0; j < 10; j++){
			blockPos[i][j].px = i * 16;
			blockPos[i][j].py = j * 16;
		}
	}
}
END_OF_FUNCTION(initialiseBlockPos)

void initialisebmps(){
	
	// loading bmps	
	loadbmp(&bGrid, "bitmaps/game_grid.bmp");
	loadbmp(&gameBackground, "bitmaps/game_interface.bmp");
	loadbmp(&mainMenu, "bitmaps/main_menu.bmp");
	loadbmp(&helpMenu, "bitmaps/help_menu.bmp");
	loadbmp(&creditsMenu, "bitmaps/credits_menu.bmp");
	
	loadbmp(&bRed, "bitmaps/red_block.bmp");
	loadbmp(&bYellow, "bitmaps/yellow_block.bmp");
	loadbmp(&bCyan, "bitmaps/cyan_block.bmp");
	loadbmp(&bBlue, "bitmaps/blue_block.bmp");
	loadbmp(&bPurple, "bitmaps/purple_block.bmp");
	loadbmp(&bGreen, "bitmaps/green_block.bmp");
	loadbmp(&bOrange, "bitmaps/orange_block.bmp");
	
	loadbmp(&oTetromino, "bitmaps/o_tetromino.bmp");
	loadbmp(&sTetromino, "bitmaps/s_tetromino.bmp");
	loadbmp(&lineTetromino, "bitmaps/line_tetromino.bmp");
	loadbmp(&tTetromino, "bitmaps/t_tetromino.bmp");
	loadbmp(&zTetromino, "bitmaps/z_tetromino.bmp");
	loadbmp(&jTetromino, "bitmaps/j_tetromino.bmp");
	loadbmp(&lTetromino, "bitmaps/l_tetromino.bmp");
	
}
END_OF_FUNCTION(initialisebmps)

bool loadbmp(BITMAP **fptr, char const fileName[20]) {	
	*fptr = load_bitmap(fileName, NULL);
	if (!*fptr) {
    	printf("Could not find %s\n", fileName);
    	allegro_message("Could not open file.");
    	return false;
	}
	return true;
}
END_OF_FUNCTION(checkAndLoad)



void scoreUpdate(int &lines, int &score, int &level, int numComplete){
	int i = 0;
	
	lines += numComplete;
	if (lines % 5 == 0 && lines != 0 && level < 19){
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
	
	delay = 80 - (4 * level);
	
}
END_OF_FUNCTION(speed)

int highScore(int score){
	FILE *fptr;
	int high;
	
	
	fptr = fopen("highscore.txt", "r");
	fscanf(fptr, "%d", &high);
	
	// is the high score lower than the current score?
	if (score > high){
		high = score;
		// close and reopen file
		fclose(fptr);
		fopen("highscore.txt", "w");
		// write to file
		fprintf(fptr, "%d", high);
	}
	
	if (high == 1){ // for some reason if the high score is 0 it sets it to 1.
		high = 0;
	}
	
	// close file
	fclose(fptr);
	
	return high;
}
END_OF_FUNCTION(highScore)

