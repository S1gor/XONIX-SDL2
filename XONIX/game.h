#include "window.h"

#pragma once

extern int block_width;
extern int point_per_block;

//struct Block
//{
//	int x;
//	int y;
//};
//
//struct Map
//{
//	int cols;
//	int rows;
//	Block blocks[win_width / block_width][(win_height - records_offset) / block_width];
//};

//void InitMap(Map& map);

struct MoveStatus
{
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
};

struct Game
{
	bool run = true;
	SDL_Event ev;
	MoveStatus moveStatus;
};

void GameDraw(Game& game);

void GameUpdate(Game& game);

void GameLoop(Game& game);
