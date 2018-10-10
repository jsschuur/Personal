#pragma once
#include <SDL_image.h>
#include <SDL.h>
class TextureManager
{
public:
	static SDL_Texture *LoadTexture(const char *path);
	static void Draw(SDL_Rect sourceRect, SDL_Rect destRect, SDL_Texture *tex);
};

