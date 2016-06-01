#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include "main.h"
#include "output.h"

int main(int argc, char *argv[]) {
	int level = 0;
	bool again = false;
	bool showMenu = true;
	SAMPLE *music = NULL; 
	
	if (aInit() != 0) {
		allegro_message("ERROR INITIALIZING ALLEGRO");
		return -1;
	} // initialise allegro
	
	// load music
	music = load_sample("sound/background.wav");
	// play music on loop
	play_sample(music, 255, 128, 1000, true);
	
	// load bmps
	initialisebmps();	

	while (showMenu){
		// call menu
		showMenu = menu(level);
		clear(buffer);
		
		// resetting again if the user wants to go play the game
		if (showMenu){
			again = true;
		}
		
		while (again) {
			// call game
			again = game(level); // main game
		}
	}
	
	destroybmps();
	destroy_sample(music);
	
	return 0;
}
END_OF_MAIN()

