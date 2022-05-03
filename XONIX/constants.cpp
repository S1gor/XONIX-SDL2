#include "constants.h"

void DeInit(int error)
{
	IMG_Quit();
	SDL_Quit();
	exit(error);
}

void Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)	DeInit(1);

	int res;
	if ((res = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)) == 0)	DeInit(1);
	if (res & IMG_INIT_PNG) printf("Initialized PNG library\n"); else printf("Couldn't init PNG library\n");
	if (res & IMG_INIT_JPG) printf("Initialized JPG library\n"); else printf("Couldn't init JPG library\n");
}