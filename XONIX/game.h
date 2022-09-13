#ifndef _GAME_H_
#define _GAME_H_

#include "window.h"

#define BLOCK_WIDTH 20
#define POINT_PER_BLOCK 5
#define MAX_ENEMY 5

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

enum playerMoveStatus
{
	playerMoveStatus_left,
	playerMoveStatus_right,
	playerMoveStatus_up,
	playerMoveStatus_down,
	playerMoveStatus_none
};

struct Player
{
	int x;
	int y;
	playerMoveStatus moveStatus;
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

enum Difficulty
{
	difficulty_easy = 1,
	difficulty_medium = 3,
	difficulty_hard = 5
};

struct Enemies
{
	Enemy mas[MAX_ENEMY];
	Difficulty counter;
};

struct RecordsBox
{
	TTF_Font* font;
	SDL_Rect box;
	int score;
	int percent;
	SDL_Surface* textPerc;
	SDL_Surface* textScore;
};

struct Result
{
	TTF_Font* font;
	SDL_Surface* surf_win;
	SDL_Texture* tex_win;
	SDL_Surface* surf_lose;
	SDL_Texture* tex_lose;
};

struct AboutGame
{
	TTF_Font* font;
	bool flag = false;
	SDL_Surface* surface;
	SDL_Texture* texture;
};

void InitMap(Map& map);

void InitPlayer(Player& player);

void InitEnemies(Enemies& enemies, Difficulty diff);

void InitRecordsBox(RecordsBox& rBox);

void InitWinLose(SDL_Renderer* ren, Result& result);

void InitAboutGame(SDL_Renderer* ren, AboutGame& aboutGame);

void RenderMap(SDL_Renderer* ren, Map& map, Difficulty& level);

void RenderPlayer(SDL_Renderer* ren, Player& player);

void RenderEnemies(SDL_Renderer* ren, Enemies& enemies);

void RenderRBox(SDL_Renderer* ren, RecordsBox& rBox, Difficulty& level);

void RenderGame(SDL_Renderer* ren, Map& map, Player& player, Enemies& enemies, RecordsBox& rBox, Difficulty& level);

void RenderWinLose(SDL_Renderer* ren, Result& result, const char* win_lose);

void RenderAboutGame(SDL_Renderer* ren, AboutGame& aboutGame);

bool UpdatePlayer(Player& player, Enemies& enemies, Map& map, RecordsBox& rBox);

void UpdatePlayerInput(Player& player, SDL_Event* event);

bool UpdateEnemies(Enemies& enemies, Map& map, Player& player);

void Draw(Map& map, int x, int y);

int UpdateMap(Map& map, Enemies& enemies);

void UpdateText(RecordsBox& rBox, int counterNew);

bool CheckWin(RecordsBox& rBox);

void DestructGame(Difficulty& level, RecordsBox& rBox, Result& result, AboutGame& aboutGame);

#endif