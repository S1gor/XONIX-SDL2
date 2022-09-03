#include "levels.h"
#include "window.h"

int main(int argc, char** argv)
{
	InitSDL();
	
	bool quit = false;
	Difficulty level;

	while (!quit)
	{
		quit = menu(window, ren, level);
		if (!quit)
			game(window, ren, level);
	}

	DeInitSDL(0);
	return 0;
}