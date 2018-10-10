#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Card.h"
#include "Button.h"
#include "Table.h"
#include "Player.h"
#include "Deck.h"
#include "Timer.h"
#include "Dealer.h"
#include "NumberPrinter.h"

typedef enum GameState
{
	DEALING, STAY, BETUP, DOUBLEDOWN, BETDOWN, HIT, IDLE, END
};

class Game
{
private:

	SDL_Window *window;
	bool isRunning = true;

	int turnCount = 0;
	int numDecks = 6;

	ButtonManager buttonManager;
	Table *table;
	Player player;
	Dealer dealer;
	Deck deck;
	std::string buttonTag;
	Timer t;

	NumberPrinter numberPrinter;

	bool resetHand = false;
	bool blackjack = false;
	bool dealerBlackJack = false;
	bool hasWon;
	
	void manageLogic();
	void playerDraw();
	void dealerDraw(); 

	GameState state = IDLE;

public:
	static SDL_Renderer *renderer;
	static SDL_Event event;

	void init(char *title, int width, int height, int x, int y, bool fullscreen);
	bool running() { return isRunning; }
	void update();
	void render();
	void manageEvents();



	void clean();
	Game();
	~Game();
};

