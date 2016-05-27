// all files to do with output, graphics, and sound
#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include "output.h"
#include "globals.h"

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
	loadbmp(&bGrid, "game_grid.bmp");
	loadbmp(&gameBackground, "game_interface.bmp");
	loadbmp(&bRed, "red_block.bmp");
	loadbmp(&bYellow, "yellow_block.bmp");
	loadbmp(&bCyan, "cyan_block.bmp");
	loadbmp(&bBlue, "blue_block.bmp");
	loadbmp(&bPurple, "purple_block.bmp");
	loadbmp(&bGreen, "green_block.bmp");
	loadbmp(&bOrange, "orange_block.bmp");
	

}
END_OF_FUNCTION(initialisebmps)

bool loadbmp(BITMAP **ptr, char fileName[20]) {	
	*ptr = load_bitmap(fileName, NULL);
	if (!*ptr) {
    	allegro_message("Could not open file.");
    	printf("Could not find %s\n", fileName);
    	return false;
	}
	return true;
}
END_OF_FUNCTION(checkAndLoad)
