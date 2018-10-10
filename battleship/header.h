#include <SDL_image.h>
#include<SDL_main.h>
#include<SDL.h>
#include <time.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_main.h>
#include <SDL.h>

#define _CRT_SECURE_NO_WARNINGS


typedef enum {
	WATER, HIT, MISS, HIGHLIGHTED, SHIP, POTENTIALSHIP, POTENTIALHIGHLIGHTED
}Tile;

typedef struct {
	int hits;
	int misses;
	int totalShots;
	int hitMissRatio;
} Scorekeeper;

int run();
