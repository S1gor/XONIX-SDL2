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

bool UpdatePlayer(Player& player, Enemies& enemies, Map& map)
{
	SDL_Rect nextPos{ 0,0,0,0 };
	switch(player.moveStatus)
	{
	case playerMoveStatus_none:
		return false;
	case playerMoveStatus_up:
		nextPos.x = player.x;
		nextPos.y = player.y - 1;
		break;
	case playerMoveStatus_down:
		nextPos.x = player.x;
		nextPos.y = player.y + 1;
		break;
	case playerMoveStatus_left:
		nextPos.y = player.y;
		nextPos.x = player.x - 1;
		break;
	case playerMoveStatus_right:
		nextPos.y = player.y;
		nextPos.x = player.x + 1;
		break;
	}
	if ((nextPos.x >= 0 && nextPos.x < WIN_WIDTH / BLOCK_WIDTH)
		&& (nextPos.y >= 0 && nextPos.y < (WIN_HEIGHT - RECORDS_OFFSET) / BLOCK_WIDTH))
	{
		player.x = nextPos.x;
		player.y = nextPos.y;

		if (map.blocks[player.x][player.y].status == typeBlock_captured
			&& player.moveStatus != playerMoveStatus_none)
		{
			//int count = updateMap(map, enemies);
			//updateText(count, rBox);
			player.moveStatus = playerMoveStatus_none;
			return false;
		}
		else if (map.blocks[player.x][player.y].status == typeBlock_noncaptured)
		{
			map.blocks[player.x][player.y].status = typeBlock_processed;
			return false;
		}
		else if (map.blocks[player.x][player.y].status == typeBlock_processed)
		{
			return true;
		}
	}
	return false;
}

void UpdatePlayerInput(Player& player, SDL_Event* event)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_UP)
		{
			player.moveStatus = playerMoveStatus_up;
		}
		if (event->key.keysym.sym == SDLK_DOWN)
		{
			player.moveStatus = playerMoveStatus_down;
		}
		if (event->key.keysym.sym == SDLK_LEFT)
		{
			player.moveStatus = playerMoveStatus_left;
		}
		if (event->key.keysym.sym == SDLK_RIGHT)
		{
			player.moveStatus = playerMoveStatus_right;
		}
	}
}

bool UpdateEnemies(Enemies& enemies, Map& map, Player& player)
{
	bool isCollision = false;
	for (int i = 0; i < int(enemies.counter); i++)
	{
		SDL_Rect nextPos = { 0,0,0,0 };
		switch (enemies.mas[i].move_hor)
		{
		case enemyMoveStatus_left:
			nextPos.x = enemies.mas[i].x - 1;
			break;
		case enemyMoveStatus_right:
			nextPos.x = enemies.mas[i].x + 1;
			break;
		}

		switch (enemies.mas[i].move_ver)
		{
		case enemyMoveStatus_up:
			nextPos.y = enemies.mas[i].y - 1;
			break;
		case enemyMoveStatus_down:
			nextPos.y = enemies.mas[i].y + 1;
			break;
		}

		if (enemies.mas[i].x == player.x && enemies.mas[i].y == player.y)
			isCollision = true;

		/*без столкновения*/
		if (map.blocks[nextPos.x][nextPos.y].status == typeBlock_noncaptured)
		{
			enemies.mas[i].x = nextPos.x;
			enemies.mas[i].y = nextPos.y;
		}
		/*столкновение с уже захваченной территорией*/
		else if (map.blocks[nextPos.x][nextPos.y].status == typeBlock_captured)
		{
			bool flag = false;
			switch (enemies.mas[i].move_hor)
			{
			case enemyMoveStatus_left:
				if (map.blocks[enemies.mas[i].x - 1][enemies.mas[i].y].status == typeBlock_captured)
				{
					enemies.mas[i].move_hor = enemyMoveStatus_right;
					flag = true;
				}
				break;
			case enemyMoveStatus_right:
				if (map.blocks[enemies.mas[i].x + 1][enemies.mas[i].y].status == typeBlock_captured)
				{
					enemies.mas[i].move_hor = enemyMoveStatus_left;
					flag = true;
				}
				break;
			}

			switch (enemies.mas[i].move_ver)
			{
			case enemyMoveStatus_up:
				if (map.blocks[enemies.mas[i].x][enemies.mas[i].y - 1].status == typeBlock_captured)
				{
					enemies.mas[i].move_ver = enemyMoveStatus_down;
					flag = true;
				}
				break;
			case enemyMoveStatus_down:
				if (map.blocks[enemies.mas[i].x][enemies.mas[i].y + 1].status == typeBlock_captured)
				{
					enemies.mas[i].move_ver = enemyMoveStatus_up;
					flag = true;
				}
				break;
			}

			if (!flag) /*если угол*/
			{
				if (enemies.mas[i].move_hor == enemyMoveStatus_left)
					enemies.mas[i].move_hor = enemyMoveStatus_right;
				else
					enemies.mas[i].move_hor = enemyMoveStatus_left;

				if (enemies.mas[i].move_ver == enemyMoveStatus_up)
					enemies.mas[i].move_ver = enemyMoveStatus_down;
				else
					enemies.mas[i].move_ver = enemyMoveStatus_up;
			}
		}
		/*столкновение с территорией в процессе захвата*/
		else if (map.blocks[nextPos.x][nextPos.y].status == typeBlock_processed)
		{
			isCollision = true;
		}
	}
	return isCollision;
}

int UpdateMap(Map& map, Enemies& enemies)
{
	int counter = 0;

	for (int i = 0; i < int(enemies.counter); i++)
	{
		Draw(map, enemies.mas[i].x, enemies.mas[i].y);
	}

	for (int i = 0; i < map.rows; i++)
	{
		for (int j = 0; j < map.cols; j++)
		{
			if (map.blocks[i][j].status == typeBlock_nondraw)
			{
				map.blocks[i][j].status = typeBlock_noncaptured;
			}
			else
			{
				if (map.blocks[i][j].status == typeBlock_noncaptured
					|| map.blocks[i][j].status == typeBlock_processed)
					counter++;
				map.blocks[i][j].status = typeBlock_captured;
			}
		}
	}
	return counter;
}

void Draw(Map& map, int x, int y)
{
	if (map.blocks[x][y].status == typeBlock_noncaptured) map.blocks[x][y].status = typeBlock_nondraw;
	if (map.blocks[x][y - 1].status == typeBlock_noncaptured) Draw(map, x, y - 1);
	if (map.blocks[x][y + 1].status == typeBlock_noncaptured) Draw(map, x, y + 1);
	if (map.blocks[x - 1][y].status == typeBlock_noncaptured) Draw(map, x - 1, y);
	if (map.blocks[x + 1][y].status == typeBlock_noncaptured) Draw(map, x + 1, y);
}















void ProcessMove(Player& player, Enemies& enemies)
{
	/*if (player.moveStatus.up && !player.moveStatus.down && !player.moveStatus.left && !player.moveStatus.right && player.rect.y != 0)								player.rect.y--;
	if (!player.moveStatus.up && player.moveStatus.down && !player.moveStatus.left && !player.moveStatus.right && player.rect.y != WIN_HEIGHT- player.rect.w)		player.rect.y++;
	if (player.moveStatus.right && !player.moveStatus.left && !player.moveStatus.up && !player.moveStatus.down && player.rect.x != WIN_WIDTH - player.rect.w)		player.rect.x++;
	if (!player.moveStatus.right && player.moveStatus.left && !player.moveStatus.up && !player.moveStatus.down && player.rect.x != 0)								player.rect.x--;*/
}

//void GameUpdate(Game& game, Player& player, Enemies& enemies)
//{
//	while (SDL_PollEvent(&game.ev))
//	{
//		switch (game.ev.type)
//		{
//		case SDL_QUIT:
//			game.run = false;
//			break;
//		case SDL_KEYDOWN:
//			switch (game.ev.key.keysym.scancode)
//			{
//			case SDL_SCANCODE_ESCAPE:	game.run = false;					break;
//			case SDL_SCANCODE_UP:		player.moveStatus.up = true;		break;
//			case SDL_SCANCODE_DOWN:		player.moveStatus.down = true;		break;
//			case SDL_SCANCODE_RIGHT:	player.moveStatus.right = true;		break;
//			case SDL_SCANCODE_LEFT:		player.moveStatus.left = true;		break;
//			}
//			break;
//		case SDL_KEYUP:
//			switch (game.ev.key.keysym.scancode)
//			{
//			case SDL_SCANCODE_UP:		player.moveStatus.up = false;		break;
//			case SDL_SCANCODE_DOWN:		player.moveStatus.down = false;		break;
//			case SDL_SCANCODE_RIGHT:	player.moveStatus.right = false;	break;
//			case SDL_SCANCODE_LEFT:		player.moveStatus.left = false;		break;
//			}
//			break;
//		}
//	}
//	ProcessMove(player, enemies);
//}



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
		//GameUpdate(game, player, enemies);
		GameDraw(game, player, enemies, map, dif);
	}
}