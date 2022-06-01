#pragma once

extern SDL_Window* win;
extern SDL_Renderer* ren;

#define WIN_WIDTH 1240
#define WIN_HEIGHT 620
#define RECORDS_OFFSET 100

void DeInit(int error);

void Init();