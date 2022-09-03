#include "game.h"
#include <iostream>
#include <SDL_image.h>

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
	player.y = 0;
	player.moveStatus = playerMoveStatus_none;
}

void InitEnemies(Enemies& enemies, Difficulty dif)
{
	srand(time(NULL));
	enemies.counter = dif;
	for (int i = 0; i < dif; i++)
	{
		enemies.mas[i].x = 4 * i + 2;
		enemies.mas[i].y = 4 * i + 2;

		enemies.mas[i].move_hor = enemyMoveStatus(rand() % 2);
		enemies.mas[i].move_ver = enemyMoveStatus(rand() % 2 + 2);
	}
}

void InitRecordsBox(RecordsBox& rBox)
{
	rBox.border.x = 20;
	rBox.border.y = WIN_HEIGHT - RECORDS_OFFSET;
	rBox.border.w = WIN_WIDTH - 40;
	rBox.border.h = RECORDS_OFFSET - 7;

	rBox.box.x = rBox.border.x + 2;
	rBox.box.y = rBox.border.y + 2;
	rBox.box.w = rBox.border.w - 4;
	rBox.box.h = rBox.border.h - 4;

	rBox.score = 0;
	rBox.percent = 0;

	InitFont(rBox.font);
	SDL_Color color = { 0, 0, 0 , 255 };
	rBox.textScore = TTF_RenderUTF8_Blended(rBox.font, "Очки: 0", color);
	rBox.textPerc = TTF_RenderUTF8_Blended(rBox.font, "Захват: 0/100", color);
}

void InitWinLose(SDL_Renderer* ren, Result& result)
{
	InitFont(result.font);
	SDL_Color colorWin = { 0, 255, 0, 255 };
	char textWin[] = "ВЫ ВЫИГРАЛИ!";
	result.surf_win = TTF_RenderUTF8_Blended(result.font, textWin, colorWin);

	SDL_Color colorLose = { 255, 0, 0, 255 };
	char textLose[] = "ВЫ ПРОИГРАЛИ!";
	result.surf_lose = TTF_RenderUTF8_Blended(result.font, textLose, colorLose);
}

void InitAboutGame(SDL_Renderer* ren, AboutGame& aboutGame)
{
	InitFont(aboutGame.font);
	SDL_Color color = { 0, 255, 0, 255 };
	char text[] = "Что-то тут должно буть интересное о игре";
	aboutGame.surface = TTF_RenderUTF8_Blended(aboutGame.font, text, color);
}

void RenderMap(SDL_Renderer* ren, Map& map, Difficulty& level)
{
	SDL_Rect rect;
	rect.w = rect.h = BLOCK_WIDTH;
	for (int i = 0; i < map.rows; i++)
	{
		for (int j = 0; j < map.cols; j++)
		{
			rect.x = map.blocks[i][j].x * BLOCK_WIDTH;
			rect.y = map.blocks[i][j].y * BLOCK_WIDTH;

			if (level == difficulty_easy)
				switch (map.blocks[i][j].status)
				{
				case typeBlock_captured:	SDL_SetRenderDrawColor(ren, 68, 148, 74, 255);		break;
				case typeBlock_noncaptured:	SDL_SetRenderDrawColor(ren, 168, 228, 160, 255);	break;
				case typeBlock_processed:	SDL_SetRenderDrawColor(ren, 30, 89, 69, 255);		break;
				}
			else if (level == difficulty_medium)
				switch (map.blocks[i][j].status)
				{
				case typeBlock_captured:	SDL_SetRenderDrawColor(ren, 243, 165, 5, 255);		break;
				case typeBlock_noncaptured:	SDL_SetRenderDrawColor(ren, 255, 202, 134, 255);	break;
				case typeBlock_processed:	SDL_SetRenderDrawColor(ren, 237, 118, 14, 255);		break;
				}
			else
				switch (map.blocks[i][j].status)
				{
				case typeBlock_captured:	SDL_SetRenderDrawColor(ren, 161, 35, 18, 255);		break;
				case typeBlock_noncaptured:	SDL_SetRenderDrawColor(ren, 205, 92, 92, 255);		break;
				case typeBlock_processed:	SDL_SetRenderDrawColor(ren, 72, 6, 7, 255);			break;
				}
			SDL_RenderFillRect(ren, &rect);
		}
	}
}

void RenderPlayer(SDL_Renderer* ren, Player& player)
{
	SDL_Rect border, rect;
	border.x = player.x * BLOCK_WIDTH;
	border.y = player.y * BLOCK_WIDTH;
	border.w = border.h = BLOCK_WIDTH;
	rect.x = border.x + 1;
	rect.y = border.y + 1;
	rect.w = rect.h = BLOCK_WIDTH - 2;
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderFillRect(ren, &border);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
	SDL_RenderFillRect(ren, &rect);
}

void RenderEnemies(SDL_Renderer* ren, Enemies& enemies)
{
	for (int i = 0; i < enemies.counter; i++)
	{
		int radius = 10;
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		for (int w = 0; w < radius * 2; w++)
			for (int h = 0; h < radius * 2; h++)
			{
				int dx = radius - w;
				int dy = radius - h;
				if ((dx * dx + dy * dy) <= (radius * radius))
					SDL_RenderDrawPoint(ren, enemies.mas[i].x * BLOCK_WIDTH + BLOCK_WIDTH / 2 + dx, enemies.mas[i].y * BLOCK_WIDTH + BLOCK_WIDTH / 2 + dy);
			}
	}
}

void RenderRBox(SDL_Renderer* ren, RecordsBox& rBox, Difficulty& level)
{
	if (level == difficulty_easy)
	{
		SDL_SetRenderDrawColor(ren, 168, 228, 160, 255);
		SDL_RenderFillRect(ren, &rBox.border);
		SDL_SetRenderDrawColor(ren, 68, 148, 74, 255);
	}
	else if (level == difficulty_medium)
	{
		SDL_SetRenderDrawColor(ren, 255, 202, 134, 255);
		SDL_RenderFillRect(ren, &rBox.border);
		SDL_SetRenderDrawColor(ren, 243, 165, 5, 255);
	}
	else
	{
		SDL_SetRenderDrawColor(ren, 205, 92, 92, 255);
		SDL_RenderFillRect(ren, &rBox.border);
		SDL_SetRenderDrawColor(ren, 161, 35, 18, 255);
	}
	SDL_RenderFillRect(ren, &rBox.box);

	SDL_Texture* tScore = SDL_CreateTextureFromSurface(ren, rBox.textScore);
	SDL_Rect rScore = { 50, WIN_HEIGHT - RECORDS_OFFSET + 25, 175, 50 };
	SDL_RenderCopy(ren, tScore, NULL, &rScore);
	SDL_DestroyTexture(tScore);

	SDL_Texture* tPerc = SDL_CreateTextureFromSurface(ren, rBox.textPerc);
	SDL_Rect rPerc = { WIN_WIDTH / 2, WIN_HEIGHT - RECORDS_OFFSET + 25, 300, 50 };
	SDL_RenderCopy(ren, tPerc, NULL, &rPerc);
	SDL_DestroyTexture(tPerc);
}

void RenderGame(SDL_Renderer* ren, Map& map, Player& player, Enemies& enemies, RecordsBox& rBox, Difficulty& level)
{
	RenderMap(ren, map, level);
	RenderPlayer(ren, player);
	RenderEnemies(ren, enemies);
	RenderRBox(ren, rBox, level);
}

void RenderWinLose(SDL_Renderer* ren, Result& result, const char* win_lose)
{
	SDL_Rect rect = { WIN_WIDTH / 2 - 250, WIN_HEIGHT / 2 - 100, 500, 125 };
	if (win_lose == "win")
	{
		result.tex_win = SDL_CreateTextureFromSurface(ren, result.surf_win);
		SDL_RenderCopy(ren, result.tex_win, NULL, &rect);
		SDL_DestroyTexture(result.tex_win);
	}
	else
	{
		result.tex_lose = SDL_CreateTextureFromSurface(ren, result.surf_lose);
		SDL_RenderCopy(ren, result.tex_lose, NULL, &rect);
		SDL_DestroyTexture(result.tex_lose);
	}
	SDL_RenderPresent(ren);
	SDL_Delay(2000);
}

void RenderAboutGame(SDL_Renderer* ren, AboutGame& aboutGame)
{
	SDL_Rect rect = { WIN_WIDTH / 2 - 250, WIN_HEIGHT / 2 - 100, 100, 20 };
	aboutGame.texture = SDL_CreateTextureFromSurface(ren, aboutGame.surface);
	SDL_RenderCopy(ren, aboutGame.texture, NULL, &rect);
	SDL_DestroyTexture(aboutGame.texture);
}

bool UpdatePlayer(Player& player, Enemies& enemies, Map& map, RecordsBox& rBox)
{
	SDL_Rect nextPos = { 0,0,0,0 };
	switch (player.moveStatus)
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

	/*if (player.moveStatus.playerMoveStatus_none)
		return false;
	else if (player.moveStatus.playerMoveStatus_up)
	{
		nextPos.x = player.x;
		nextPos.y = player.y - 1;
	}
	else if (player.moveStatus.playerMoveStatus_down)
	{
		nextPos.x = player.x;
		nextPos.y = player.y + 1;
	}
	else if (player.moveStatus.playerMoveStatus_left)
	{
		nextPos.y = player.y;
		nextPos.x = player.x - 1;
	}
	else if (player.moveStatus.playerMoveStatus_right)
	{
		nextPos.y = player.y;
		nextPos.x = player.x + 1;
	}*/

	if ((nextPos.x >= 0 && nextPos.x < WIN_WIDTH / BLOCK_WIDTH) && (nextPos.y >= 0 && nextPos.y < (WIN_HEIGHT - RECORDS_OFFSET) / BLOCK_WIDTH))
	{
		player.x = nextPos.x;
		player.y = nextPos.y;

		if (map.blocks[player.x][player.y].status == typeBlock_captured && player.moveStatus !=	playerMoveStatus_none)
		{
			int counter = UpdateMap(map, enemies);
			UpdateText(rBox, counter);
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
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.scancode)
		{
		case SDL_SCANCODE_UP:		player.moveStatus = playerMoveStatus_up;		break;
		case SDL_SCANCODE_DOWN:		player.moveStatus = playerMoveStatus_down;		break;
		case SDL_SCANCODE_LEFT:		player.moveStatus = playerMoveStatus_left;		break;
		case SDL_SCANCODE_RIGHT:	player.moveStatus = playerMoveStatus_right;		break;

		/*case SDL_SCANCODE_UP:		player.moveStatus.playerMoveStatus_up = true;		break;
		case SDL_SCANCODE_DOWN:		player.moveStatus.playerMoveStatus_down = true;		break;
		case SDL_SCANCODE_LEFT:		player.moveStatus.playerMoveStatus_left = true;		break;
		case SDL_SCANCODE_RIGHT:	player.moveStatus.playerMoveStatus_right = true;	break;*/
		}
		break;
	/*case SDL_KEYUP:
		switch (event->key.keysym.scancode)
		{
		case SDL_SCANCODE_UP:		player.moveStatus.playerMoveStatus_up = false;			break;
		case SDL_SCANCODE_DOWN:		player.moveStatus.playerMoveStatus_down = false;		break;
		case SDL_SCANCODE_RIGHT:	player.moveStatus.playerMoveStatus_right= false;		break;
		case SDL_SCANCODE_LEFT:		player.moveStatus.playerMoveStatus_left = false;		break;
		}
		break;*/
	}
}

bool UpdateEnemies(Enemies& enemies, Map& map, Player& player)
{
	bool isCollision = false;
	for (int i = 0; i < enemies.counter; i++)
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

		if (map.blocks[nextPos.x][nextPos.y].status == typeBlock_noncaptured)
		{
			enemies.mas[i].x = nextPos.x;
			enemies.mas[i].y = nextPos.y;
		}
		else if (map.blocks[nextPos.x][nextPos.y].status == typeBlock_captured)
		{
			bool corner = true;
			switch (enemies.mas[i].move_hor)
			{
			case enemyMoveStatus_left:
				if (map.blocks[enemies.mas[i].x - 1][enemies.mas[i].y].status == typeBlock_captured)
				{
					enemies.mas[i].move_hor = enemyMoveStatus_right;
					corner = false;
				}
				break;
			case enemyMoveStatus_right:
				if (map.blocks[enemies.mas[i].x + 1][enemies.mas[i].y].status == typeBlock_captured)
				{
					enemies.mas[i].move_hor = enemyMoveStatus_left;
					corner = false;
				}
				break;
			}

			switch (enemies.mas[i].move_ver)
			{
			case enemyMoveStatus_up:
				if (map.blocks[enemies.mas[i].x][enemies.mas[i].y - 1].status == typeBlock_captured)
				{
					enemies.mas[i].move_ver = enemyMoveStatus_down;
					corner = false;
				}
				break;
			case enemyMoveStatus_down:
				if (map.blocks[enemies.mas[i].x][enemies.mas[i].y + 1].status == typeBlock_captured)
				{
					enemies.mas[i].move_ver = enemyMoveStatus_up;
					corner = false;
				}
				break;
			}

			if (corner)
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
		else if (map.blocks[nextPos.x][nextPos.y].status == typeBlock_processed)
			isCollision = true;
	}
	return isCollision;
}

void Draw(Map& map, int x, int y)
{
	if (map.blocks[x][y].status == typeBlock_noncaptured) map.blocks[x][y].status = typeBlock_nondraw;
	if (map.blocks[x][y - 1].status == typeBlock_noncaptured) Draw(map, x, y - 1);
	if (map.blocks[x][y + 1].status == typeBlock_noncaptured) Draw(map, x, y + 1);
	if (map.blocks[x - 1][y].status == typeBlock_noncaptured) Draw(map, x - 1, y);
	if (map.blocks[x + 1][y].status == typeBlock_noncaptured) Draw(map, x + 1, y);
}

int UpdateMap(Map& map, Enemies& enemies)
{
	int counter = 0;

	for (int i = 0; i < enemies.counter; i++)
	{
		Draw(map, enemies.mas[i].x, enemies.mas[i].y);
	}

	for (int i = 0; i < map.rows; i++)
		for (int j = 0; j < map.cols; j++)
		{
			if (map.blocks[i][j].status == typeBlock_nondraw)
				map.blocks[i][j].status = typeBlock_noncaptured;
			else
			{
				if (map.blocks[i][j].status == typeBlock_noncaptured || map.blocks[i][j].status == typeBlock_processed)
					counter++;
				map.blocks[i][j].status = typeBlock_captured;
			}
		}
	return counter;
}

void UpdateText(RecordsBox& rBox, int counterNew)
{
	SDL_Color color = { 0, 0, 0 };

	rBox.score += POINT_PER_BLOCK * counterNew;
	int blocks = rBox.score / POINT_PER_BLOCK;
	rBox.percent = (blocks * 100) / ((WIN_WIDTH / BLOCK_WIDTH - 2) * ((WIN_HEIGHT - RECORDS_OFFSET) / BLOCK_WIDTH - 2));

	char* score = (char*)calloc(20, sizeof(char));
	strcat_s(score, 20, "Очки: ");
	char* tmp = (char*)calloc(20, sizeof(char));
	_itoa_s(rBox.score, tmp, 20, 10);
	strcat_s(score, 20, tmp);

	SDL_FreeSurface(rBox.textScore);
	rBox.textScore = TTF_RenderUTF8_Blended(rBox.font, score, color);

	char* percent = (char*)calloc(30, sizeof(char));
	_itoa_s(rBox.percent, tmp, 20, 10);
	strcat_s(percent, 30, "Захват: ");
	strcat_s(percent, 30, tmp);
	strcat_s(percent, 30, "/100");

	SDL_FreeSurface(rBox.textPerc);
	rBox.textPerc = TTF_RenderUTF8_Blended(rBox.font, percent, color);

	free(score);
	free(tmp);
	free(percent);
}

bool CheckWin(RecordsBox& rBox)
{
	if (rBox.percent >= 80)
		return true;
	return false;
}

void DestructGame(Difficulty& level, RecordsBox& rBox, Result& result)
{
	TTF_CloseFont(rBox.font);
	TTF_CloseFont(result.font);
	SDL_FreeSurface(rBox.textPerc);
	SDL_FreeSurface(rBox.textScore);

	int rec_easy;
	int rec_medium;
	int rec_hard;

	FILE* file;
	char rec_file[] = "resources/records.txt";
	fopen_s(&file, rec_file, "r");
	if (file == NULL)		printf("Не удалось открыть файл %s", rec_file);

	fscanf_s(file, "%d", &rec_easy);
	fscanf_s(file, "%d", &rec_medium);
	fscanf_s(file, "%d", &rec_hard);
	
	fclose(file);

	switch (level)
	{
	case difficulty_easy:
		rec_easy = (rBox.score > rec_easy ? rBox.score : rec_easy);
		break;
	case difficulty_medium:
		rec_medium = (rBox.score > rec_medium ? rBox.score : rec_medium);
		break;
	case difficulty_hard:
		rec_hard = (rBox.score > rec_hard ? rBox.score : rec_hard);
		break;
	}

	fopen_s(&file, rec_file, "w");

	fprintf(file, "%d\n%d\n%d", rec_easy, rec_medium, rec_hard);

	fclose(file);
}