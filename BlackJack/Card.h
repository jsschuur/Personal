#pragma once
#include "PositionComponent.h"
#include "SpriteComponent.h"

class Card
{
private:
	
	PositionComponent *position;
	AnimatableComponent *animate;
	SpriteComponent *sprite;
	
	int score;
	bool isBack;
	bool ace;

public:

	Card(SDL_Texture *cardTex, int score, SDL_Texture *back)
	{
		position = new PositionComponent();
		position->init();
		animate = new AnimatableComponent(position);
		sprite = new SpriteComponent(cardTex);
		sprite->init(position, animate, back);
		this->score = score;
		ace = false;
		isBack = false;
	}

	Card(SDL_Texture *cardTex, int score, SDL_Texture *back, bool isAce)
	{
		position = new PositionComponent();
		position->init();
		animate = new AnimatableComponent(position);
		sprite = new SpriteComponent(cardTex);
		sprite->init(position, animate, back);
		this->score = score;
		isBack = false;
		this->ace = isAce;
	}

	bool isAce() { return ace; }


	void switchAce() { score = 1; }
	void resetAce() { score = 11; }
	void switchSprite() { sprite->switchSprite(); }

	void update()
	{
		animate->update();
		position->update();
		sprite->update(isBack);
	}

	int getScore() { return score; }

	void draw()
	{
		sprite->draw();
	}
	PositionComponent *getPositionComponent() { return position; }
	AnimatableComponent *getAnimatableComponent() { return animate; }

	void clean() { sprite->clean(); }
};