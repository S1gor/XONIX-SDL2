#ifndef _MAP_H_
#define _MAP_H_

#include "constants.h"

#define BLOCK_WIDTH 20
#define POINT_PER_BLOCK 5


struct Block
{
	int x;
	int y;
};

struct Map
{
	int cols;
	int rows;
	Block blocks[GAME_WIDTH / BLOCK_WIDTH][(GAME_HEIGHT- RECORDS_OFFSET) / BLOCK_WIDTH];
};

void InitMap(Map& map);


#endif