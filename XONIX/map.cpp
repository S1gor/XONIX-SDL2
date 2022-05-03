#include "map.h"

void InitMap(Map& map)
{
	map.cols = (GAME_HEIGHT - RECORDS_OFFSET) / BLOCK_WIDTH;
	map.rows = GAME_WIDTH / BLOCK_WIDTH;

	for (int i = 0; i < map.rows; i++)
		for (int j = 0; j < map.cols; j++)
		{
			map.blocks[i][j].x = i;
			map.blocks[i][j].y = j;
		}
}
