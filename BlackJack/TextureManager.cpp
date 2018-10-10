#include "TextureManager.h"
#include "Game.h"
#include <iostream>

SDL_Texture * TextureManager::LoadTexture(const char * path)
{
	SDL_Surface *temp = IMG_Load(path);
	if (temp) {
		SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, temp);
		if (tex) {
			return tex;
		}
	}
	std::cout << IMG_GetError() << std::endl;
}

void TextureManager::Draw(SDL_Rect sourceRect, SDL_Rect destRect, SDL_Texture * tex)
{
	SDL_RenderCopy(Game::renderer, tex, &sourceRect, &destRect);
}
