#include "Button.h"
#include "Game.h"

void Button::updateState()
{
	if (isPressable) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x >= this->x && y >= this->y)
		{
			if (x <= this->x + width && y <= this->y + height)
			{
				if (Game::event.type == SDL_MOUSEBUTTONDOWN)
				{
					state = PRESSED;
					return;
				}
				state = HIGHLIGHTED;
				return;
			}
		}
		state = NORMAL;
	}
	else state = UNPRESSABLE;
}