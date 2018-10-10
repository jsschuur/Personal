

#include "header.h"
#define _CRT_SECURE_NO_WARNINGS
/*********************************************************************************************************
*Welcome to Jackson Schuur's Awesome game of battleship. This game is graphical (thats right) and heavily*
*Uses the SDL libraries. I learned SDL primarily by using lazyfoo's tutorial found on the internet (just *
*google the name). To run this without SDL installed and implemented, I have tested on two different     *
*computers that the program runs properly if the .exe is ran from the "Debug" folder. If you are         *
*interested in implementing SDL lazyfoo also has great tutorials on that, along with a few other sites   *
*for more recent versions of Visual Studio. SDL, SDL_Image, and SDL_ttf must all be implemented          *
*P.S Yes I know the game does not tell you when you have sunk a battleship. Don't think of it as         *
*"missing something," think of at is....increased difficulty.                                            *
*********************************************************************************************************/
int main(int argc, char ** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	run();

	SDL_Quit();
	return 0;
}