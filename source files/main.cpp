// Charles Zhang  ICS3U  mrs Cullum	 June 13, 2016
// "Falling Block" game, clone of Tetris. I do not own "Tetris" and all rights belong to The Tetris Company, found at Tetris.com. Game Design by Alexey Pajitnov.
// Tetris theme song and Tetriminos are trademarks of Tetris Holding
#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include "main.h"
#include "output.h"

int main(int argc, char *argv[]) {
	int level = 0;
	bool again = true;
	bool showMenu = true;
	
	// initialise allegro, print error mmessage if allegro did not initialise properly
	if (aInit() != 0) {
		allegro_message("ERROR INITIALIZING ALLEGRO");
		return -1;
	} 

	// load bmps
	initialisebmps();
	// load samples
	initialisesamples();	
		
	// play music on loop
	play_sample(sample_backgroundmusic, 100, 128, 1000, true);
	
	// program loop
	while (showMenu){
		// call menu
		showMenu = menu(level);
		
		if (!showMenu){
			again = false;
		}
		else {
			again = true;
		}
		
		clear(buffer);
		
		while (again) {
			// call game
			again = game(level); // main game
		}
		clear_keybuf();
	}
	
	stop_sample(sample_backgroundmusic);
	// cleanup before exiting
	destroybmps();
	destroysamples();
	
	return 0;
}
END_OF_MAIN()

