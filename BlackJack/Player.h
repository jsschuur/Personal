#include "Card.h"
#include <vector>

class Player
{
private:
	int balance = 1000;
	int bet = 1;
	std::vector<Card*> hand;
	int score = 0;
	bool hasDoubledDown;
	int doubledownBet;
public:
	
	void addToHand(Card *newCard) 
	{ 
		hand.push_back(newCard);
		score += newCard->getScore();
		if (manageAces()) refreshScore();
	}
	void update() { for (auto &c : hand) c->update(); }

	int getHandSize() { return hand.size(); }

	void draw()
	{
		for (auto &c : hand) c->draw();
	}

	bool manageAces()
	{
		if (score > 21)
		{
			for (auto &c : hand)
			{
				if (c->isAce() && c->getScore() != 1)
				{
					c->switchAce();
					return true;
				}
			}
			return false;
		}
	}

	void refreshScore()
	{
		score = 0;
		for (auto &c : hand) score += c->getScore();
	}

	int getScore() { return score; }

	void closeHand(bool didWin)
	{
		if (didWin)	balance += bet;
		else balance -= bet;

		if (balance <= 0) balance = 0;
		if (balance >= 99999) balance = 99999;
	}
	void discard(std::vector<Card*> *discard)
	{
		for (auto &c : hand) { c->resetAce(); c->getPositionComponent()->reset(); discard->push_back(c); }
		score = 0;
		hand.clear();
	}
	void increaseBet()
	{
		if (bet < 10)
		{
			bet++;
		}
		else if (bet < 40)
		{
			bet += 5;
		}
		else if (bet < 100)
		{
			bet += 10;
		}
		else if (bet < 200)
		{
			bet += 25;
		}
		if (bet > balance) bet = balance;
	}
	void decreaseBet()
	{
		if (bet > 1 && bet <= 10)
		{
			bet--;
		}
		else if (bet >= 10 && bet <= 40)
		{
			bet -= 5;
		}
		else if (bet >= 40 && bet <= 100)
		{
			bet -= 10;
		}
		else if (bet >= 100)
		{
			bet -= 25;
		}
	}
	void resetBet() { bet = 0; }
	void blackJack()
	{
		balance += (bet * 2);
	}


	void doubleDown() { bet += bet; hasDoubledDown = true; }

	bool didDoubleDown() { return hasDoubledDown; }
	void undoDoubleDown() { bet -= bet / 2; hasDoubledDown = false; }

	int getBet() { return bet; }
	int getBalance() { return balance; }
	void tie()
	{
		balance += bet;
	}
	bool canDoubleDown() { return balance >= (bet * 2); }
};