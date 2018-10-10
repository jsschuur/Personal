#include "Game.h"
#include <iostream>
#include <string>

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

using namespace std;

void Game::init(char *title, int width, int height, int x, int y, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
	window = SDL_CreateWindow(title, x, y, width, height, flags);
	if (window)
	{
		renderer = SDL_CreateRenderer(window, -1, 0);
	}

	

	table = new Table();
	buttonManager.addButton(620, 871, 200, 104, "resources/dealbutton.png", "deal"); //deal = 0
	buttonManager.addButton(380, 871, 200, 104, "resources/staybutton.png", "stay"); //stay = 1
	buttonManager.addButton(380, 756, 200, 104, "resources/betupbutton.png", "betup"); //betup = 2
	buttonManager.addButton(620, 756, 200, 104, "resources/doubledown.png", "doubledown"); //doubledown = 3
	buttonManager.addButton(140, 756, 200, 104, "resources/betdownbutton.png", "betdown"); //betdown = 4
	buttonManager.addButton(140, 871, 200, 104, "resources/hitbutton.png", "hit"); //hit = 5

	buttonManager.newHand();

	deck.loadDeck(numDecks);
	deck.shuffle();
	numberPrinter.init();
}

void Game::update()
{
	buttonManager.update();
	manageLogic();
	player.update();
	dealer.update();
	numberPrinter.update(player.getBet(), player.getBalance());
}

void Game::render()
{
	SDL_RenderClear(renderer);
	table->draw();
	buttonManager.draw();
	player.draw();
	dealer.draw();
	numberPrinter.draw();
	SDL_RenderPresent(renderer);
}

void Game::manageEvents()
{
	while (SDL_PollEvent(&event)) 
	{
		if (event.type == SDL_QUIT) isRunning = false;
		buttonManager.updateState();
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{	
			buttonTag = buttonManager.getTag();
		}
	}

	if (!buttonTag.empty())
	{
		if (buttonTag == "deal")
		{
			if (state == IDLE) {
				state = DEALING; buttonManager.hasDealt();
				if (!player.canDoubleDown()) buttonManager.setPressable(DOUBLEDOWN, false);
			}
			else {
				resetHand = true;
				buttonManager.newHand();
			}
		}
		else if (buttonTag == "hit")
		{
			state = HIT;
			buttonManager.hasHit();
		}
		else if (buttonTag == "doubledown")
		{
			state = DOUBLEDOWN;
			buttonManager.hasDoubledDown();
		}
		else if (buttonTag == "betup")
		{
			state = BETUP;
		}
		else if (buttonTag == "betdown")
		{
			state = BETDOWN;
		}
		else if (buttonTag == "stay")
		{
			state = STAY;
			buttonManager.disable();
		}
	}
	buttonTag.clear();
}

void Game::manageLogic()
{
	switch (state)
	{
	case DEALING:
		if (dealer.getHandSize() == 0)
		{
			dealerDraw();
		}

		if (t.wait(500))
		{
			if (player.getHandSize() == dealer.getHandSize())
			{
				dealerDraw();
			}
			else
			{
				playerDraw();
			}
			if (player.getHandSize() == 2 && dealer.getHandSize() == 2)
			{
				if (player.getScore() == 21)
				{
					state = STAY;
					blackjack = true;
					break;
				}
				else if (dealer.getScore() == 21)
				{
					state = STAY;
					dealerBlackJack = true;
					break;
				}
				state = IDLE;
			}
		}
		break;
	case BETUP:
		player.increaseBet();
		state = IDLE;
		break;
	case DOUBLEDOWN:
		player.doubleDown();
		playerDraw();
		state = STAY;
		break;
	case BETDOWN:
		player.decreaseBet();
		state = IDLE;
		break;
	case HIT:
		playerDraw();
		if (player.getScore() > 21)
		{
			buttonManager.end();
			state = STAY;
		}
		else state = IDLE;
		break;
	case STAY:



		if (blackjack)
		{
			player.blackJack();
			state = END;
			buttonManager.end();
			blackjack = false;
			break;
		}
		else if (dealerBlackJack)
		{
			dealer.reveal();
			player.closeHand(false);
			state = END;
			buttonManager.end();
			dealerBlackJack = false;
			break;
		}



		else if (player.getScore() > 21)
		{
			player.closeHand(false);
			state = END;
			buttonManager.end();
		}

		if (!dealer.revealed() && !blackjack && player.getScore() <= 21) dealer.reveal();

		else if (dealer.getScore() >= 17 && dealer.getScore() <= 21 && player.getScore() <= 21)
		{
			if (dealer.getScore() > player.getScore())
			{
				player.closeHand(false);
			}
			else if (dealer.getScore() == player.getScore())
			{
				player.closeHand(false);
				player.tie();
			}
			else
			{
				player.closeHand(true);
			}

			state = END;
			buttonManager.end();
		}
		else if (dealer.getScore() < 17)
		{
			if(t.wait(600)) dealerDraw();
		}
		else if (dealer.getScore() > 21)
		{
			player.closeHand(true);
			state = END;
			buttonManager.end();
		}
		break;
	case END:

		if (resetHand)
		{
			player.discard(deck.getDiscardPtr());
			dealer.discard(deck.getDiscardPtr());
			state = IDLE;
			resetHand = false;

			if (player.didDoubleDown()) player.undoDoubleDown();

			if (deck.numCard() < (52 * numDecks) / 15) deck.reshuffle(numDecks);
		}
		break;
	}
}

void Game::playerDraw()
{
	Card *draw = deck.draw();
	draw->getAnimatableComponent()->setEntity(1);
	draw->getAnimatableComponent()->setIndex(player.getHandSize());
	player.addToHand(draw);
}

void Game::dealerDraw()
{
	Card *draw = deck.draw();
	draw->getAnimatableComponent()->setEntity(0);
	draw->getAnimatableComponent()->setIndex(dealer.getHandSize());
	dealer.addToHand(draw);
}

void Game::clean()
{
	deck.clean();
	table->clean();
	numberPrinter.clean();
	buttonManager.clean();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

Game::Game()
{
}


Game::~Game()
{
}