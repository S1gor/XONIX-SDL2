#include"menu.h"
#include<iostream>
#include<SDL_ttf.h>
#include<SDL_image.h>

void InitBackground(SDL_Texture* background, SDL_Renderer* ren)
{
	SDL_Surface* surface = IMG_Load("resources / background.jpg");
	if (surface == NULL)	printf("Нет картинки background.jpg");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
}

void InitButtons(MenuButton& menuButton, SDL_Renderer* ren, TTF_Font* font)
{
	char name[4][20] = {
		"resources/btn1.bmp",
		"resources/btn2.bmp",
		"resources/btn3.bmp",
		"resources/btn4.bmp", };



}