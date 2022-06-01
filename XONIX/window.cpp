#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include "window.h"

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

void DeInit(int error)
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	IMG_Quit();
	SDL_Quit();
	exit(error);
}

void Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)	DeInit(1);

	win = SDL_CreateWindow("XONIX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL) DeInit(1);
	
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL) DeInit(1);

	TTF_Font* font = TTF_OpenFont("resources/font.ttf", 50);

	int res;
	if ((res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) == 0)	DeInit(1);
	if (res & IMG_INIT_PNG) printf("Initialized PNG library\n"); else printf("Couldn't init PNG library\n");
	if (res & IMG_INIT_JPG) printf("Initialized JPG library\n"); else printf("Couldn't init JPG library\n");
}