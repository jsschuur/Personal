#pragma once
#include "TextureManager.h"

class Table
{
private:
	SDL_Rect sourceRect = { 0, 0, 1920, 1080 };
	SDL_Rect destinationRect = { 0, 0, 1920, 1080 };
	SDL_Texture *tableTex;
	SDL_Texture *deckText;
	SDL_Rect sourceRectDeck = { 0, 0, 463, 600 };
	SDL_Rect destinationRectDeck = { 50, 50, 220, 320 };
public:
	Table() {
		tableTex = TextureManager::LoadTexture("resources/table.png"); deckText = TextureManager::LoadTexture("resources/deck1.png");
	}
	void draw()
	{
		TextureManager::Draw(sourceRect, destinationRect, tableTex);
		TextureManager::Draw(sourceRectDeck, destinationRectDeck, deckText);
	}

	void clean()
	{
		SDL_DestroyTexture(deckText);
		SDL_DestroyTexture(tableTex);
	}
};