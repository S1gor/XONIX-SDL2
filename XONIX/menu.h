#ifndef _MENU_H_
#define _MENU_H_

#include "window.h"

#define BUTTON_COUNT 5
#define BUTTON_WIDTH 400
#define BUTTON_HEIGHT 60

struct Background
{
	SDL_Texture* textureBack;
	SDL_Surface* surfaceBack;
};

struct Button
{
	TTF_Font* font;
	SDL_Rect button;
	SDL_Texture* buttonBack;
	SDL_Surface* textButton;
	SDL_Surface* textRec;
};

struct MenuButton
{
	Button button[BUTTON_COUNT];
};

void InitBackground(SDL_Renderer* ren, Background& background);

void InitButtons(SDL_Renderer* ren, MenuButton& menuButton);

void RenderBackground(SDL_Renderer* ren, Background& background);

void RenderButtons(SDL_Renderer* ren, MenuButton& menuButton);

void RenderMenu(SDL_Renderer* ren, Background& background, MenuButton& menuButton);

int UpdateMenu(SDL_Event* event, MenuButton& menuButton);

void DestructMenu(Background& background, MenuButton& menuButton);

#endif