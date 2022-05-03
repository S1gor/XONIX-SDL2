#include "constants.h"

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int main(int argc, char* argv[])
{
	Init();
	win = SDL_CreateWindow("XONIX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);


	SDL_Event ev;
	
	int mouse_x = GAME_WIDTH / 2;
	int mouse_y = GAME_HEIGHT / 2;

	bool isUp = false; bool isDown = false; bool isLeft = false; bool isRight = false;

	bool quit = true;
	while (quit)
	{
		while (SDL_PollEvent(&ev))
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				quit = false;
				break;
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:	quit = false;		break;
				case SDL_SCANCODE_UP:		isUp = true;		break;
				case SDL_SCANCODE_DOWN:		isDown = true;		break;
				case SDL_SCANCODE_RIGHT:	isRight = true;		break;
				case SDL_SCANCODE_LEFT:		isLeft = true;		break;
				}
				break;
			case SDL_KEYUP:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:		isUp = false;		break;
				case SDL_SCANCODE_DOWN:		isDown = false;		break;
				case SDL_SCANCODE_RIGHT:	isRight = false;	break;
				case SDL_SCANCODE_LEFT:		isLeft = false;		break;
				}
				break;
			}
		}

		if (isUp && !isDown)		mouse_y--;
		if (!isUp && isDown)		mouse_y++;
		if (isRight && !isLeft)		mouse_x++;
		if (!isRight && isLeft)		mouse_x--;

		

		SDL_SetRenderDrawColor(ren, 0, 225, 225, 225);
		SDL_RenderClear(ren);
	
		SDL_Rect r = { mouse_x,mouse_y,15,15 };
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderDrawRect(ren, &r);

		
		SDL_RenderPresent(ren);
	}


	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	DeInit(0);
	return 0;
}