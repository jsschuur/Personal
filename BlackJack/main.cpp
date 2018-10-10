#include <SDL.h>
#include <iostream>
#include <time.h>
#include "Game.h"

int main(int argc, char *argv[])
{
	srand((unsigned)time(0));
	
	int gameWidth = 1920;
	int gameHeight = 1080;
	
	bool isFullscreen = true;
	Game *game = new Game();
	game->init("Blackjack", gameWidth, gameHeight, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, false);
	

	int fps = 60;
	int frameDelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;

	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->manageEvents(); 
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
	
}
