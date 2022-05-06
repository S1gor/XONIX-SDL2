#include "window.h"

#pragma once

extern int block_width;
extern int point_per_block;

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


struct TypeBlock
{
	bool captured = true;
	bool processed = true;
	bool noncaptured = true;
};

struct Block
{
	int x;
	int y;
	TypeBlock status;
};

struct Map
{
	int cols;
	int rows;
	Block blocks[65][33];//32
};

void InitMap(Map& map);

void RenderMap(SDL_Renderer* ren, Map& map);