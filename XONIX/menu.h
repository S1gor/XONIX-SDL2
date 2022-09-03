#ifndef _MENU_H_
#define _MENU_H_

#include "window.h"

#define MAX_TEXT_LENGTH 64
#define BUTTON_COUNT 5
#define BUTTON_WIDTH 400
#define BUTTON_HEIGHT 60

struct Button
{
	TTF_Font* font;
	SDL_Rect button;
	SDL_Texture* buttonBack;
	SDL_Surface* textRec;
	SDL_Surface* textButton;
};

struct MenuButton
{
	Button button[BUTTON_COUNT];
};

void InitBackground(SDL_Texture*& background, SDL_Renderer* ren);

void InitButtons(MenuButton& menuButton, SDL_Renderer* ren);

void RenderBackground(SDL_Renderer* ren, SDL_Texture* background);

void RenderButtons(SDL_Renderer* ren, MenuButton& menuButton);

void RenderMenu(SDL_Renderer* ren, SDL_Texture* background, MenuButton& menuButton);

int UpdateMenu(SDL_Event* event, MenuButton& menuButton);

void DestructMenu(SDL_Texture* background, MenuButton& menuButton);

#endif