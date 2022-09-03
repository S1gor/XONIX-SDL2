#include "window.h"
#include <iostream>
#include <SDL_image.h>

SDL_Window* window = NULL;
SDL_Renderer* ren = NULL;

void DeInitSDL(int error)
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(window);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	exit(error);
}

void InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Не удалось инициализировать SDL!");
		DeInitSDL(1);
	}

	window = SDL_CreateWindow("XONIX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Не удалось создать окно!");
		DeInitSDL(1);
	}
	
	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("Не удалось создать рисовальщик!");
		DeInitSDL(1);
	}

	int res;
	if ((res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) == 0)
	{
		printf("Не удалось инициализировать SDL_Image!");
		DeInitSDL(1);
	}
	if (!IMG_INIT_PNG)	printf("Не удалось инициализировать библиотеку PNG.\n");
	if (!IMG_INIT_JPG)	printf("Не удалось инициализировать библиотеку JPG.\n");
}

void InitFont(TTF_Font*& font)
{
	if (TTF_Init())
	{
		printf("Не удалось инициализировать шрифт!");
		DeInitSDL(1);
	}
	font = TTF_OpenFont("resources/mrd_aachen_bold.ttf", 50);
}