#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#pragma once

extern SDL_Window* win;
extern SDL_Renderer* ren;

#define WIN_WIDTH 1240
#define WIN_HEIGHT 620
#define RECORDS_OFFSET 100
//extern int win_width;
//extern int win_height;
//extern int records_offset;

void DeInit(int error);

void Init();