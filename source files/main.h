// Charles Zhang  ICS3U  mrs Cullum	 June 13, 2016
// header file for main.cpp
#ifndef MAIN_H_
#define MAIN_H_

// in game.cpp
bool game(int level); // main game
bool menu(int &level); // main menu function

// in engine.cpp
void increment_speed_counter(); // speed counter logic
int aInit(); // initialises allegro and keyboard etc
// in output.cpp
void initialisebmps(); // load all needed bmps

//in globals.cpp
extern BITMAP *buffer;
#endif
