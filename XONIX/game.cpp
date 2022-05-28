#include<iostream>
#include "game.h"

void InitMap(Map& map)
{
	map.cols = (WIN_HEIGHT - RECORDS_OFFSET) / BLOCK_WIDTH;
	map.rows = WIN_WIDTH / BLOCK_WIDTH;
	for (int i = 0; i < map.rows; i++)
	{
		for (int j = 0; j < map.cols; j++)
		{
			map.blocks[i][j].x = i;
			map.blocks[i][j].y = j;
			if (i == 0 || j == 0 || i == map.rows - 1 || j == map.cols - 1)
				map.blocks[i][j].status = typeBlock_captured;
			else
				map.blocks[i][j].status = typeBlock_noncaptured;
		}
	}
}

void InitPlayer(Player& player)
{
	player.x = 0;
	player.y = 1;
	//player.moveStatus = moveStatus_none;
}

void InitEnemies(Enemies& enemies, difficulty dif)
{
	srand(time(NULL));
	enemies.counter = dif;
	for (int i = 0; i<int(dif); i++)
	{
		enemies.mas[i].x = 4 * i + 2;
		enemies.mas[i].y = 4 * i + 2;

		enemies.mas[i].move_hor = enemyMoveStatus(rand() % 2);
		enemies.mas[i].move_ver = enemyMoveStatus(rand() % 2 + 2);
	}
}

//void InitRecordsBox()
//void InitWinLose()

void RenderMap(SDL_Renderer* ren, Map& map)
{
	SDL_Rect rect;
	rect.w = rect.h = BLOCK_WIDTH;
	for (int i = 0; i < map.rows; i++)
	{
		for (int j = 0; j < map.cols; j++)
		{
			rect.x = map.blocks[i][j].x * BLOCK_WIDTH;
			rect.y = map.blocks[i][j].y * BLOCK_WIDTH;

			switch (map.blocks[i][j].status)
			{
			case typeBlock_captured:
				SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
				break;
			case typeBlock_noncaptured:
				SDL_SetRenderDrawColor(ren, 0, 100, 100, 255);
				break;
			case typeBlock_processed:
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
				break;
			}
			SDL_RenderFillRect(ren, &rect);
		}
	}
}

void RenderPlayer(SDL_Renderer* ren, Player& player)
{
	SDL_Rect border, p;
	border.x = player.x * BLOCK_WIDTH;
	border.y = player.y * BLOCK_WIDTH;
	border.w = border.h = BLOCK_WIDTH;
	p.x = border.x + 1;
	p.y = border.y + 1;
	p.w = p.h = BLOCK_WIDTH - 2;
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderFillRect(ren, &border);
	SDL_SetRenderDrawColor(ren, 170, 0, 170, 255);
	SDL_RenderFillRect(ren, &p);
}

void RenderEnemies(SDL_Renderer* ren, Enemies& enemies)
{
	for (int i = 0; i< int(enemies.counter); i++)
	{
		int circle_radius = 10;
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
		for (int j = 0; j < circle_radius * 2; j++)
		{
			for (int x = 0; x < circle_radius * 2; x++)
			{
				int dx = circle_radius - j;
				int dy = circle_radius - x;
				if ((dx * dx + dy * dy) <= (circle_radius * circle_radius))
				{
					SDL_RenderDrawPoint(ren,
						enemies.mas[i].x * BLOCK_WIDTH + BLOCK_WIDTH / 2 + dx,
						enemies.mas[i].y * BLOCK_WIDTH + BLOCK_WIDTH / 2 + dy);
				}
			}
		}
	}
}

//void RenderRecordsBox();

void RenderGame(SDL_Renderer* ren, Map& map, Player& player, Enemies& enemies)
{
	RenderMap(ren, map);
	RenderPlayer(ren, player);
	RenderEnemies(ren, enemies);
	//RenderRecordsBox();
}

//void RenderWinLose(SDL_Renderer* ren, SDL_Texture* texture)
//{
//
//}





void ProcessMove(Player& player, Enemies& enemies)
{
	//if (player.moveStatus.up && !player.moveStatus.down && !player.moveStatus.left && !player.moveStatus.right && player.rect.y != 0)								player.rect.y--;
	//if (!player.moveStatus.up && player.moveStatus.down && !player.moveStatus.left && !player.moveStatus.right && player.rect.y != WIN_HEIGHT- player.rect.w)		player.rect.y++;
	//if (player.moveStatus.right && !player.moveStatus.left && !player.moveStatus.up && !player.moveStatus.down && player.rect.x != WIN_WIDTH - player.rect.w)		player.rect.x++;
	//if (!player.moveStatus.right && player.moveStatus.left && !player.moveStatus.up && !player.moveStatus.down && player.rect.x != 0)								player.rect.x--;
}

void GameUpdate(Game& game, Player& player, Enemies& enemies)
{
	while (SDL_PollEvent(&game.ev))
	{
		switch (game.ev.type)
		{
		case SDL_QUIT:
			game.run = false;
			break;
		case SDL_KEYDOWN:
			switch (game.ev.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:	game.run = false;					break;
			case SDL_SCANCODE_UP:		player.moveStatus.up = true;		break;
			case SDL_SCANCODE_DOWN:		player.moveStatus.down = true;		break;
			case SDL_SCANCODE_RIGHT:	player.moveStatus.right = true;		break;
			case SDL_SCANCODE_LEFT:		player.moveStatus.left = true;		break;
			}
			break;
		case SDL_KEYUP:
			switch (game.ev.key.keysym.scancode)
			{
			case SDL_SCANCODE_UP:		player.moveStatus.up = false;		break;
			case SDL_SCANCODE_DOWN:		player.moveStatus.down = false;		break;
			case SDL_SCANCODE_RIGHT:	player.moveStatus.right = false;	break;
			case SDL_SCANCODE_LEFT:		player.moveStatus.left = false;		break;
			}
			break;
		}
	}
	ProcessMove(player, enemies);
}

int UpdateMap(Map& map, Enemies& enemies)
{
	int counter = 0; return 0;
}

void GameDraw(Game& game, Player& player, Enemies& enemies, Map& map, difficulty dif)
{
	SDL_SetRenderDrawColor(ren, 0, 225, 225, 255);
	SDL_RenderClear(ren);

	InitPlayer(player);
	InitEnemies(enemies, dif);
	InitMap(map);
	RenderPlayer(ren, player);

	SDL_RenderPresent(ren);
}

void GameLoop(Game& game, Player& player, Enemies& enemies, Map& map,difficulty dif)
{
	while (game.run)
	{
		GameUpdate(game, player, enemies);
		GameDraw(game, player, enemies, map, dif);
	}
}