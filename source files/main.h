#ifndef MAIN_H_
#define MAIN_H_

// in game.cpp
bool game(); // main game
// in engine.cpp
void increment_speed_counter(); // speed counter logic
int aInit(); // initialises allegro and keyboard etc
// in output.cpp
void initialisebmps(); // load all needed bmps
#endif
