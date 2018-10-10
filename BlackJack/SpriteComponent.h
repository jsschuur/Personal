#pragma once
#include <SDL.h>
#include "AnimatableComponent.h"
#include "PositionComponent.h"
#include "TextureManager.h"

class SpriteComponent
{
private:
	SDL_Texture *tex;
	SDL_Texture *back;
	SDL_Texture *cardTex;
	SDL_Rect sourceRect;
	SDL_Rect destRect;

	PositionComponent *position = nullptr;
	AnimatableComponent *animatable;

public:
	SpriteComponent(SDL_Texture *cardTex)
	{
		this->cardTex = cardTex;
		tex = cardTex;
	}
	~SpriteComponent()
	{
		SDL_DestroyTexture(tex);
	}

	void init(PositionComponent *position, AnimatableComponent *animatable, SDL_Texture *back)
	{
		this->position = position;
		this->animatable = animatable;
		this->back = back;
		sourceRect.x = 0;
		sourceRect.y = 0;
		sourceRect.w = 413; //card width
		sourceRect.h = 600; //card height
		destRect.x = 0;
		destRect.y = 0;
		destRect.w = 220; //render width
		destRect.h = 320; //render height
	}

	void switchSprite()
	{
		if (tex == back) tex = cardTex;
		else tex = back;
	}

	void update(bool isBack)
	{
		destRect.x = position->getX();
		destRect.y = position->getY();
	}

	void draw()
	{
		TextureManager::Draw(sourceRect, destRect, tex);
	}
	void clean() { SDL_DestroyTexture(cardTex); SDL_DestroyTexture(back); SDL_DestroyTexture(tex); }
};
