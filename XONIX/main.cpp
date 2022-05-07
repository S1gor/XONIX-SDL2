#include "game.h"

int main(int argc, char* argv[])
{
	Init();

	Game game;
	Player player;

	GameLoop(game, player);

	DeInit(0);
	return 0;
}