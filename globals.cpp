#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

// globals
volatile long speed_counter = 0;
int grid[GRID_X][GRID_Y];

BITMAP *buffer;
