#ifndef GLOBALS_H_
#define GLOBALS_H_

#define GRID_X 20
#define GRID_Y 10

// initializing structure
struct Tetromino{
	char shape; // shape of the tetromino
	int colour; // colour of tetromino
	int px[4]; // position of 4 blocks
	int py[4]; // position of 4 blocks
	float cx; // position of centre
	float cy; // position of centre
};

// position of blocks for graphics
struct Block{
	int px;
	int py;
};
#endif

