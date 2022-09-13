#include "levels.h"

bool menu(SDL_Window* window, SDL_Renderer* ren, Difficulty& level, AboutGame& aboutGame)
{
	bool quit = false;

	Background background;
	MenuButton menuButton;
	InitBackground(ren, background);
	InitButtons(ren, menuButton);

	SDL_Event event;

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
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

		if (aboutGame.flag)
		{
			quit = true;
			RenderAboutGame(ren, aboutGame);
			aboutGame.flag = false;
			SDL_Delay(4000);
		}
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
		SDL_Delay(90);
	}
	DestructGame(level, rBox, result, aboutGame);
}