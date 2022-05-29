#include "window.h"

#pragma once

#define BLOCK_WIDTH 20
#define POINT_PER_BLOCK 5
#define MAX_ENEMY 5

struct Game
{
	bool run = true;
	SDL_Event ev;
};

enum playerMoveStatus
{
	playerMoveStatus_left,
	playerMoveStatus_right,
	playerMoveStatus_up,
	playerMoveStatus_down,
	playerMoveStatus_none
};

//struct PlayerMoveStatus
//{
//	bool up = false;
//	bool down = false;
//	bool left = false;
//	bool right = false;
//};

struct Player
{
	int x;
	int y;
	playerMoveStatus moveStatus;
};

enum difficulty
{
	difficulty_easy = 1,
	difficulty_medium = 3,
	difficulty_hard = 5
};

enum enemyMoveStatus
{
	enemyMoveStatus_left,
	enemyMoveStatus_right,
	enemyMoveStatus_up,
	enemyMoveStatus_down
};

struct Enemy
{
	int x;
	int y;
	enemyMoveStatus move_hor;
	enemyMoveStatus move_ver;
};

struct Enemies
{
	Enemy mas[MAX_ENEMY];
	difficulty counter;
};

enum typeBlock
{
	typeBlock_captured,
	typeBlock_processed,
	typeBlock_noncaptured,
	typeBlock_nondraw
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

void InitMap(Map& map);

void InitPlayer(Player& player);

void InitEnemies(Enemies& enemies, difficulty dif);

void RenderMap(SDL_Renderer* ren, Map& map);

void RenderPlayer(SDL_Renderer* ren, Player& player);

void RenderEnemies(SDL_Renderer* ren, Enemies& enemies);

void RenderGame(SDL_Renderer* ren, Map& map, Player& player, Enemies& enemies);

void RenderWinLose(SDL_Renderer* ren, SDL_Texture* texture);

bool UpdatePlayer(Player& player, Enemies& enemies, Map& map);

void UpdatePlayerInput(Player& player, SDL_Event* event);

bool UpdateEnemies(Enemies& enemies, Map& map, Player& player);

int UpdateMap(Map& map, Enemies& enemies);

void Draw(Map& map, int x, int y);




void GameDraw(Game& game, Player& player, Enemies& enemies, Map& map, difficulty dif);

void ProcessMove(Player& player, Enemies& enemies);

void GameUpdate(Game& game, Player& player, Enemies& enemies);

void GameLoop(Game& game, Player& player, Enemies& enemies, Map& map, difficulty dif);


