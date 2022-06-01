#include"window.h"
#include<SDL.h>

#pragma once

#define MAX_TEXT_LENGH 64
#define BUTTON_COUNT 4
#define BUTTON_WIDTH 400
#define BUTTON_HEIGHT 60

struct Button
{
	SDL_Rect button;
	SDL_Texture* buttonBack;
	SDL_Surface* text;
};

struct MenuButton
{
	Button buttons[BUTTON_COUNT];
};

void InitBackground(SDL_Texture* background, SDL_Renderer* ren);

void InitButtons(MenuButton& menuButton, SDL_Renderer* ren, TTF_Font* font);
