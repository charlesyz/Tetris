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
	srand(time(0)); //random number seed

	while (again) {
		again = game(); // main game
	}

	return 0;
}
END_OF_MAIN()

