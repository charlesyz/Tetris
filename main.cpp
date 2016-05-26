#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include "main.h"
#include "output.h"

int main(int argc, char *argv[]) {

	bool again = true;
	
	if (aInit() != 0) {
		allegro_message("ERROR INITIALIZING ALLEGRO");
		return -1;
	} // initialise allegro
	
	// load bmps
	initialisebmps();
	
	
	srand(time(0)); //random number seed
	
	while (again) {
		again = game(); // main game
	}

	return 0;
}
END_OF_MAIN()

int aInit() {
	allegro_init(); // Initialize Allegro
	install_keyboard(); // Initialize keyboard routines
	install_mouse(); // Initialize mouse

	//Tell allegro to install the timer routines
	install_timer();
	LOCK_VARIABLE(speed_counter); //Used to set the timer - which regulates the game's speed
	LOCK_FUNCTION(increment_speed_counter);	// lock the function which increments the speed counter.

	install_int_ex(increment_speed_counter, BPS_TO_TIMER(100)); //Set BPS
	set_color_depth(desktop_color_depth()); // Set the color depth

	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 400,600,0,0); //Change  graphics mode to 400 x 600
	show_mouse(screen);

	return 0;
}
END_OF_FUNCTION(aInit)
