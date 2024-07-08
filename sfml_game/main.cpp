#include <iostream>
#include <ctime>
#include "Game.h"


int main()
{
	srand(time(NULL));

	//init game class
	Game game;


	//Game loop
	while (game.running())
	{
		game.update();
		game.render();
	}

	return 0;
}