#include "game.h"

int block_width = 20;
int point_per_block = 5;

void InitPlayer(Player& player)
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderDrawRect(ren, &player.rect);

	/*player.surface = IMG_Load("player.jpg");
	player.texture = SDL_CreateTextureFromSurface(ren, player.surface);
	player.img_rect = { 0,0,player.surface->w,player.surface->h };
	SDL_FreeSurface(player.surface);
	player.dst_rect = { player.x,player.y,player.img_rect.w / 19,player.img_rect.h / 19 };

	SDL_RenderCopy(ren, player.texture, NULL, &player.dst_rect);*/
}

void InitEnemies(Enemies& enemies)
{
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderDrawRect(ren, &enemies.rect);
}

void GameDraw(Game& game, Player& player, Enemies& enemies)
{
	SDL_SetRenderDrawColor(ren, 0, 225, 225, 255);
	SDL_RenderClear(ren);

	InitPlayer(player);
	InitEnemies(enemies);

	SDL_RenderPresent(ren);
}

void ProcessMove(Player& player, Enemies& enemies)
{
	if (player.moveStatus.up && !player.moveStatus.down && !player.moveStatus.left && !player.moveStatus.right && player.rect.y != 0)								player.rect.y--;
	if (!player.moveStatus.up && player.moveStatus.down && !player.moveStatus.left && !player.moveStatus.right && player.rect.y != win_height - player.rect.w)		player.rect.y++;
	if (player.moveStatus.right && !player.moveStatus.left && !player.moveStatus.up && !player.moveStatus.down && player.rect.x != win_width - player.rect.w)		player.rect.x++;
	if (!player.moveStatus.right && player.moveStatus.left && !player.moveStatus.up && !player.moveStatus.down && player.rect.x != 0)								player.rect.x--;
}

void ProcessMove2(Enemies& enemies)
{
	enemies.rect.x += enemies.xSpeed;
	enemies.rect.y += enemies.ySpeed;

	if (enemies.rect.x + enemies.rect.w > win_width)
	{
		enemies.rect.x = win_width - enemies.rect.w;
		enemies.xSpeed = -1 * (rand() % (enemies.maxSpeed - enemies.minSpeed) + enemies.minSpeed);
	}
	if (enemies.rect.x < 0)
	{
		enemies.rect.x = 0;
		enemies.xSpeed = rand() % (enemies.maxSpeed - enemies.minSpeed) + enemies.minSpeed;
	}
	if (enemies.rect.y + enemies.rect.h > win_height)
	{
		enemies.rect.y = win_width - enemies.rect.h;
		enemies.ySpeed = -1 * (rand() % (enemies.maxSpeed - enemies.minSpeed) + enemies.minSpeed);
	}
	if (enemies.rect.y < 0)
	{
		enemies.rect.y = 0;
		enemies.ySpeed = rand() % (enemies.maxSpeed - enemies.minSpeed) + enemies.minSpeed;
	}
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
	ProcessMove2(enemies);
}

void GameLoop(Game& game, Player& player, Enemies& enemies)
{
	while (game.run)
	{
		GameUpdate(game, player, enemies);
		GameDraw(game, player, enemies);
	}
}






/*void InitMap(Map& map)
{
	map.cols = (win_height - records_offset) / block_width;
	map.rows = win_width / block_width;
	for (int i = 0; i < map.rows; i++)
	{
		for (int j = 0; j < map.cols; j++)
		{
			map.blocks[i][j].x = i;
			map.blocks[i][j].y = j;
			if (i == 0 || j == 0 || i == map.rows - 1 || j == map.cols - 1)
				map.blocks[i][j].status.captured = true;
			else
				map.blocks[i][j].status.noncaptured = true;
		}
	}
}

void RenderMap(SDL_Renderer* ren, Map& map)
{
	SDL_Rect rect;
	rect.w = rect.h = block_width;
	for (int i = 0; i < map.rows; i++)
	{
		for (int j = 0; j < map.cols; j++)
		{
			rect.x = map.blocks[i][j].x * block_width;
			rect.y = map.blocks[i][j].y * block_width;

			if (map.blocks[i][j].status.captured == true)
				SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
			else if (map.blocks[i][j].status.noncaptured == true)
				SDL_SetRenderDrawColor(ren, 0, 100, 100, 255);
			else if (map.blocks[i][j].status.processed == true)
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		}
		SDL_RenderFillRect(ren, &rect);
	}
}*/