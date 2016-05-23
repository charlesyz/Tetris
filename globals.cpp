#include <allegro.h>
#include "globals.h"

// globals
volatile long speed_counter = 0; // for game logic
int grid[GRID_X][GRID_Y];	// hold grid info
BITMAP *buffer;
 
