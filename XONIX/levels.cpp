#include "levels.h"

bool menu(SDL_Window* window, SDL_Renderer* ren, Difficulty& level, AboutGame& aboutGame)
{
	bool quit = false;

	Background background;
	MenuButton menuButton;
	//AboutGame aboutGame;
	InitBackground(ren, background);
	InitButtons(ren, menuButton);

	SDL_Event event;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				DestructMenu(background, menuButton);
				return true;
			}

			switch (UpdateMenu(&event, menuButton))
			{
			case 1:
				level = difficulty_easy;
				quit = true;
				break;
			case 2:
				level = difficulty_medium;
				quit = true;
				break;
			case 3:
				level = difficulty_hard;
				quit = true;
				break;
			case 4:
				aboutGame.flag = true;
				quit = true;
				break;
			case 0:
				DestructMenu(background, menuButton);
				return true;
			}
		}
		SDL_RenderClear(ren);
		RenderMenu(ren, background, menuButton);
		SDL_RenderPresent(ren);	
	}
	DestructMenu(background, menuButton);
	return false;
}

void game(SDL_Window* window, SDL_Renderer* ren, Difficulty& level, AboutGame& aboutGame)
{
	bool quit = false;

	SDL_Event event;

	Map map;
	Player player;
	Enemies enemies;
	RecordsBox rBox;
	Result result;
	//AboutGame aboutGame;

	InitMap(map);
	InitPlayer(player);
	InitEnemies(enemies, level);
	InitRecordsBox(rBox);
	InitWinLose(ren, result);
	InitAboutGame(ren, aboutGame);
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;
			UpdatePlayerInput(player, &event);
		}

		/*if (aboutGame.flag)
		{
			quit = true;
			RenderAboutGame(ren, aboutGame);
		}*/

		if (UpdatePlayer(player, enemies, map, rBox))
		{
			quit = true;
			RenderWinLose(ren, result, "lose");
		}
		if (UpdateEnemies(enemies, map, player))
		{
			quit = true;
			RenderWinLose(ren, result, "lose");
		}

		if (!quit)
		{
			SDL_RenderClear(ren);

			RenderGame(ren, map, player, enemies, rBox, level);

			SDL_RenderPresent(ren);
		}

		if (CheckWin(rBox) && !quit)
		{
			quit = true;
			RenderWinLose(ren, result, "win");
		}
		SDL_Delay(85);
	}
	DestructGame(level, rBox, result);
}