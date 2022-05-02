#include<iostream>
#include<SDL.h>
#include<SDL_image.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int win_width = 1300, win_height = 750;

void DeInit(int error)
{
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
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
	
	win = SDL_CreateWindow("XONIX", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL)	DeInit(1);
	
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)	DeInit(1);
}

int main(int argc, char* argv[])
{
	Init();
	SDL_Event ev;

	
	int mouse_x = win_width / 2;
	int mouse_y = win_height / 2;

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
			case SDL_WINDOWEVENT:
				if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					win_width = ev.window.data1;
					win_height = ev.window.data2;
				}
				break;
			case SDL_KEYDOWN:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					quit = false;
					break;
				case SDL_SCANCODE_UP:
					isUp = true;
					break;
				case SDL_SCANCODE_DOWN:
					isDown = true;
					break;
				case SDL_SCANCODE_RIGHT:
					isRight = true;
					break;
				case SDL_SCANCODE_LEFT:
					isLeft = true;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (ev.key.keysym.scancode)
				{
				case SDL_SCANCODE_UP:
					isUp = false;
					break;
				case SDL_SCANCODE_DOWN:
					isDown = false;
					break;
				case SDL_SCANCODE_RIGHT:
					isRight = false;
					break;
				case SDL_SCANCODE_LEFT:
					isLeft = false;
					break;
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



	DeInit(0);
	return 0;
}