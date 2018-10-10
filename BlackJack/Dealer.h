#include "Card.h"
#include <vector>


class Dealer
{
private:
	std::vector<Card*> hand;
	int score = 0;
	bool hasRevealed = false;
public:

	void addToHand(Card *newCard)
	{
		hand.push_back(newCard);
		score += newCard->getScore();
		if (manageAces()) refreshScore();
		if (hand.size() == 1) newCard->switchSprite();
	}
	void update()
	{
		for (auto &c : hand) c->update();
	}

	int getHandSize() { return hand.size(); }

	void draw()
	{
		for (auto &c : hand) c->draw();
	}

	void discard(std::vector<Card*> *discard)
	{
		for (auto &c : hand) { c->resetAce(); c->getPositionComponent()->reset();  discard->push_back(c); }
		score = 0;
		hand.clear();
		hasRevealed = false;
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

	void reveal() { hand.front()->switchSprite(); hasRevealed = true; }
	bool revealed() { return hasRevealed; }
	int getScore() { return score; }

};