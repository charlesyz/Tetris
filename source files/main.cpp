#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[]) {
	int level = 0;
	bool again = true;
	bool showMenu = true;
	
	if (aInit() != 0) {
		allegro_message("ERROR INITIALIZING ALLEGRO");
		return -1;
	} // initialise allegro
	
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
	

	return 0;
}
END_OF_MAIN()

