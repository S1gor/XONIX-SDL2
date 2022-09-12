#include "levels.h"
#include "window.h"

int main(int argc, char** argv)
{
	InitSDL();
	
	bool quit = false;
	Difficulty level;
	AboutGame aboutGame;
	while (!quit)
	{
		quit = menu(window, ren, level,aboutGame);
		if (!quit)
			game(window, ren, level, aboutGame);
	}

	DeInitSDL(0);
	return 0;
}