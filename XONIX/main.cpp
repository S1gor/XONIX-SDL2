#include "game.h"

int main(int argc, char* argv[])
{
	Init();

	Game game;
	Player player;
	Enemies enemies;
	Map map;
	difficulty level = { difficulty_easy };

	GameLoop(game, player, enemies, map, level);

	DeInit(0);
	return 0;
}