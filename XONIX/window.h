#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#pragma once

extern SDL_Window* win;
extern SDL_Renderer* ren;

extern int win_width;
extern int win_height;
extern int records_offset;

void DeInit(int error);

void Init();