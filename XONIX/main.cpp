#include "game.h"

int main(int argc, char* argv[])
{
	Init();

	Game game;
	Player player;
	Enemies enemies;

	GameLoop(game, player, enemies);

	DeInit(0);
	return 0;
}