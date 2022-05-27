#include "game.h"

int main(int argc, char* argv[])
{
	Init();

	Game game;
	Player player;
	Enemies enemies;
	Map map;

	GameLoop(game, player, enemies, map);

	DeInit(0);
	return 0;
}