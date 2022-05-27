#include "window.h"

#pragma once

#define BLOCK_WIDTH 20
#define POINT_PER_BLOCK 5

struct Game
{
	bool run = true;
	SDL_Event ev;
};

//enum moveStatus
//{
//	moveStatus_left,
//	moveStatus_right,
//	moveStatus_up,
//	moveStatus_down,
//	moveStatus_none
//};

struct MoveStatus
{
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
};

struct Player
{
	/*SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect img_rect;
	SDL_Rect dst_rect;*/
	/*SDL_Rect rect = { WIN_WIDTH / 2,WIN_HEIGHT/ 2, 17 , 17 };
	MoveStatus moveStatus;*/
	int x;
	int y;
	MoveStatus moveStatus;
};

enum difficulty
{
	difficulty_easy = 1,
	difficulty_medium = 3,
	difficulty_hard = 5,
};

struct Enemies
{
	SDL_Rect rect = { WIN_WIDTH / 2 , WIN_HEIGHT/ 2, 17 , 17 };

	Uint32 lastTick;
	bool active = false;
	int minSpeed = 1;
	int maxSpeed = 4;
	int xSpeed = 2;
	int ySpeed = 2;
};

enum typeBlock
{
	typeBlock_captured,
	typeBlock_processed,
	typeBlock_noncaptured,
	typeBlock_nondraw,
};

struct Block
{
	int x;
	int y;
	typeBlock status;
};

struct Map
{
	int cols;
	int rows;
	Block blocks[WIN_WIDTH / BLOCK_WIDTH][(WIN_HEIGHT - RECORDS_OFFSET) / BLOCK_WIDTH];
};

void InitPlayer(Player& player);

void InitEnemies(Enemies& enemies);

void GameDraw(Game& game, Player& player, Enemies& enemies, Map& map);

void ProcessMove(Player& player, Enemies& enemies);

void GameUpdate(Game& game, Player& player, Enemies& enemies);

void GameLoop(Game& game, Player& player, Enemies& enemies, Map& map);



void InitMap(Map& map);

void RenderMap(SDL_Renderer* ren, Map& map);

int UpdateMap(Map& map, Enemies& enemies);