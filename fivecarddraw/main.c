#include "header.h"

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("ERROR: %s\n\n", SDL_GetError());
	}
	if (TTF_Init() != 0) {
		printf("ERROR: %s\n\n", TTF_GetError());
	}
	
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);

	runGame();

	SDL_Quit();
	return 0;
}
