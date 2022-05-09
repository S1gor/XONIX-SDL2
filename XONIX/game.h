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
};

struct Player
{
	/*SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect img_rect;
	SDL_Rect dst_rect;*/
	SDL_Rect rect;
	int x = win_width / 2;
	int y = win_height / 2;
	int size = 17;
	MoveStatus moveStatus;
};

struct Enemies
{
	SDL_Rect rect;
	int x = win_width / 4;
	int y = win_height / 4;
	int size = 17;
};

void InitPlayer(Player& player);

void InitEnemies(Enemies& enemies);

void GameDraw(Game& game, Player& player, Enemies& enemies);

void ProcessMove(Player& player, Enemies& enemies);

void GameUpdate(Game& game, Player& player, Enemies& enemies);

void GameLoop(Game& game, Player& player, Enemies& enemies);


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