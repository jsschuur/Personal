#pragma once
#include "TextureManager.h"
#include <vector>
#include <string>

#define HIGHLIGHTED 1
#define	NORMAL 0
#define PRESSED 2
#define UNPRESSABLE 3

#define BUTTONDEAL 0
#define BUTTONSTAY 1
#define BUTTONBETUP 2
#define BUTTONDOUBLEDOWN 3
#define BUTTONBETDOWN 4
#define BUTTONHIT 5


class Button
{
private:
	unsigned state;
	SDL_Texture *spriteTex;
	int x;
	int y;
	int width;
	int height;
	bool isPressable = true;
	std::string tag;
	SDL_Rect srcRect;
	SDL_Rect destRect;

public:

	Button(int x, int y, int width, int height, char *path, std::string tag)
	{
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.h = 104;
		srcRect.w = 200;
		this->tag = tag;
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		destRect.x = x;
		destRect.y = y;
		destRect.w = width;
		destRect.h = height;
		spriteTex = TextureManager::LoadTexture(path);
	}

	~Button() = default;

	void updateState();

	void update()
	{
		srcRect.y = state * 104;
	}

	void setPressable(bool pressable) { this->isPressable = pressable; }

	void draw()
	{
		TextureManager::Draw(srcRect, destRect, spriteTex);
	}
	unsigned getState() { return state; }
	std::string getTag() { return tag; }

	void clean()
	{
		SDL_DestroyTexture(spriteTex);
	}
};

class ButtonManager
{
private:
	std::vector<Button*> buttons;
	std::string lastButtonPressed;
public:
	void addButton(int x, int y, int width, int height, char *path, std::string tag)
	{
		Button *added = new Button(x, y, width, height, path, tag);
		buttons.push_back(added);
	}

	void setPressable(int index, bool pressable) //not pretty, could use hash table
	{
		buttons[index]->setPressable(pressable);
	}

	void updateState()
	{
		for (auto &b : buttons) b->updateState();
	}

	void update()
	{
		for (auto &b : buttons)	b->update();
		for (auto &b : buttons) b->updateState();
	}
	void draw()
	{
		for (auto &b : buttons) b->draw();
	}
	void reset()
	{
		for (auto &b : buttons) b->setPressable(true);
	}
	void disable()
	{
		for (auto &b : buttons) b->setPressable(false);
	}
	std::string getTag()
	{
		for (auto &b : buttons)	if (b->getState() == PRESSED) return b->getTag();
		return "";
	}

	void end()
	{
		disable();
		setPressable(BUTTONDEAL, true);
	}
	void newHand()
	{
		disable();
		setPressable(BUTTONBETUP,true);
		setPressable(BUTTONDEAL, true);
		setPressable(BUTTONBETDOWN, true);
	}
	void hasHit()
	{
		setPressable(BUTTONDOUBLEDOWN, false);
	}
	void hasDoubledDown()
	{
		disable();
		setPressable(BUTTONDEAL, true);
	}
	void hasDealt()
	{
		disable();
		setPressable(BUTTONHIT, true);
		setPressable(BUTTONSTAY, true);
		setPressable(BUTTONDOUBLEDOWN, true);
	}
	void clean()
	{
		for (auto &b : buttons) b->clean();
	}
};
