#include "game.h"

int main(int argc, char* argv[])
{
	Init();

	Game game;

	GameLoop(game);

	DeInit(0);
	return 0;
}