#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[]) {

	bool again = true;
	
	if (aInit() != 0) {
		allegro_message("ERROR INITIALIZING ALLEGRO");
		return -1;
	} // initialise allegro
	
	// load bmps
	initialisebmps();
	
	while (again) {
		again = game(); // main game
	}

	return 0;
}
END_OF_MAIN()

