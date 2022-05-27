#include<iostream>
#include "game.h"

void InitPlayer(Player& player)
{
	player.x = 0;
	player.y = 1;
	//player.moveStatus = moveStatus_none;

	/*player.surface = IMG_Load("player.jpg");
	player.texture = SDL_CreateTextureFromSurface(ren, player.surface);
	player.img_rect = { 0,0,player.surface->w,player.surface->h };
	SDL_FreeSurface(player.surface);
	player.dst_rect = { player.rect.x,player.rect.y,player.img_rect.w / 19,player.img_rect.h / 19 };

	SDL_RenderCopy(ren, player.texture, NULL, &player.dst_rect);*/
}

void InitEnemies(Enemies& enemies, difficulty dif)
{
	srand(time(NULL));


}

void RenderPlayer(SDL_Renderer* ren, Player& player)
{
	SDL_Rect border, inside;
	border.x = player.x * BLOCK_WIDTH;
	border.y = player.y * BLOCK_WIDTH;
	border.w = border.h = BLOCK_WIDTH;
	inside.x = border.x + 1;
	inside.y = border.y + 1;
	inside.w = inside.h = BLOCK_WIDTH - 2;
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderFillRect(ren, &border);
	SDL_SetRenderDrawColor(ren, 170, 0, 170, 255);
	SDL_RenderFillRect(ren, &inside);
}

void InitEnemies(Enemies& enemies)
{
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderDrawRect(ren, &enemies.rect);
}

//void GameDraw(Game& game, Player& player, Enemies& enemies)
//{
//	SDL_SetRenderDrawColor(ren, 0, 225, 225, 255);
//	SDL_RenderClear(ren);
//
//	InitPlayer(player);
//	InitEnemies(enemies);
//
//	SDL_RenderPresent(ren);
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


void InitMap(Map& map)
{
	map.cols = (WIN_HEIGHT- RECORDS_OFFSET) / BLOCK_WIDTH;
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
			case typeBlock_noncaptured:
				SDL_SetRenderDrawColor(ren, 0, 100, 100, 255);
			case typeBlock_processed:
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
			}
			SDL_RenderFillRect(ren, &rect);
		}
	}
}

int UpdateMap(Map& map, Enemies& enemies)
{
	int counter = 0; return 0;
}

void GameDraw(Game& game, Player& player, Enemies& enemies, Map& map)
{
	SDL_SetRenderDrawColor(ren, 0, 225, 225, 255);
	SDL_RenderClear(ren);

	InitPlayer(player);
	InitEnemies(enemies);
	InitMap(map);
	RenderPlayer(ren, player);

	SDL_RenderPresent(ren);
}

void GameLoop(Game& game, Player& player, Enemies& enemies, Map& map)
{
	while (game.run)
	{
		GameUpdate(game, player, enemies);
		GameDraw(game, player, enemies, map);
	}
}