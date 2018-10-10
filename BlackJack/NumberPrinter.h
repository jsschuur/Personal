#pragma once
#include "TextureManager.h"
#include <stack>

//26 xdistance
//26 * 59 size bloc
//

class NumberPrinter
{
private:
	SDL_Texture *tex;
	std::stack<int> betStack;
	std::stack<int> balanceStack;

public:
	NumberPrinter()
	{
		
	}

	void init()
	{
		tex = TextureManager::LoadTexture("resources/numbers.png");
	}
	~NumberPrinter() = default;
	void update(int bet, int balance)
	{
		while (bet > 0)
		{
			int digit = bet % 10;
			betStack.push(digit);
			bet /= 10;
		}
		while (balance > 0)
		{
			int digit = balance % 10;
			balanceStack.push(digit);
			balance /= 10;
		}
	}

	void draw()
	{
		int betIndex = 0;
		while (!betStack.empty())
		{
			SDL_Rect betSrc = { 26 * betStack.top(), 0, 26, 59 };
			SDL_Rect betDest = { 346 + (26 * betIndex), 648, 26, 59 };
			betStack.pop();
			TextureManager::Draw(betSrc, betDest, tex);
			betIndex++;
		}
		int balanceIndex = 0;
		while (!balanceStack.empty())
		{
			SDL_Rect betSrc = { 26 * balanceStack.top(), 0, 26, 59 };
			SDL_Rect betDest = { 604 + (26 * balanceIndex), 648, 26, 59 };
			balanceStack.pop();
			TextureManager::Draw(betSrc, betDest, tex);
			balanceIndex++;
		}
	}
	void clean() { SDL_DestroyTexture(tex); }
};