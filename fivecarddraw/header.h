
//JACKSON SCHUUR
//Scoring method inspired by resources found at http://www.mathcs.emory.edu/~cheung/Courses/170/Syllabus/10/pokerValue.html
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> 
#include <stdio.h>
#include <SDL_ttf.h>

#define SPADE_INDEX 0
#define DIAMOND_INDEX 1
#define HEART_INDEX 2
#define CLUB_INDEX 3

#define WIDTH 1280
#define HEIGHT 800
#define TITLE "5 CARD DRAW"

#define CARD_WIDTH 100
#define CARD_HEIGHT 160

#define STRAIGHT_FLUSH 8000000
#define FOUR_OF_A_KIND 7000000
#define FULL_HOUSE 6000000
#define FLUSH 5000000
#define STRAIGHT 4000000
#define THREE_OF_A_KIND 3000000
#define TWO_PAIR 2000000
#define PAIR 1000000

#define MENU 0
#define RULES 1
#define GAME 2


typedef struct Button {
	int topLeftX;
	int topLeftY;
	int bottomRightX;
	int bottomRightY;
}Button;

typedef struct Card {
	bool isHeld;
	bool isQueued;
	int value;
	char suit;
	SDL_Rect cardSprite;
}Card;

typedef enum Handtype {
	highcard, pair, twopair, threeofakind, straight, flush, fullhouse, fourofakind, straightflush
}Handtype;

typedef enum BUTTONPRESSED {
	FOLD, CHECK, RAISEBET, LOWERBET, ALLIN, RESETBET, DRAW, PLAYBUTTON, RULESBUTTON, EXITBUTTON, RULESRETURN, GAMERETURN
}BUTTONPRESSED;




SDL_Renderer *renderer;
SDL_Window *window;
void runGame();