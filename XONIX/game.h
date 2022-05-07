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

struct Player
{
	int x = win_width / 2;
	int y = win_height / 2;
};

void GameDraw(Game& game, Player& player);

void GameUpdate(Game& game, Player& player);

void GameLoop(Game& game, Player& player);


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