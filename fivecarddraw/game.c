
#include "header.h"

const Button cardOne = { 360, 496, 460, 655 };
const Button cardTwo = { 475, 496, 580, 680 };
const Button cardThree = { 590, 496, 700, 680 };
const Button cardFour = { 705, 496, 820, 680 };
const Button cardFive = { 820, 496, 940, 680 };
const Button drawButton = { 967, 587, 1206, 694 };
const Button checkButton = { 360, 697, 460, 744 };
const Button foldButton = { 820, 697, 919, 743 };
const Button decreaseBetButton = { 967, 430, 1082, 495 };
const Button increaseBetButton = { 1092, 430, 1206, 495 };
const Button allInButton = { 967, 503, 1206, 562 };
const Button resetBetButton = { 969, 238, 1206, 295 };
const Button playButton = { 730, 72, 1174, 188 };
const Button rulesButton = { 730, 213, 1174, 326 };
const Button exitButton = { 730, 354, 1174, 470 };
const Button rulesReturnButton = { 28, 412, 267, 514 };
const Button gameReturnButton = { 91, 696, 191, 743 };

void generateDeck(Card deck[4][13]) {

	for (int suitCounter = 0; suitCounter < 4; suitCounter++) {
		for (int valueCounter = 0; valueCounter < 13; valueCounter++) {
			deck[suitCounter][valueCounter].cardSprite.x = valueCounter * 50;
			deck[suitCounter][valueCounter].cardSprite.w = 50;
			deck[suitCounter][valueCounter].cardSprite.h = 80;
			deck[suitCounter][valueCounter].isHeld = false;
			deck[suitCounter][valueCounter].isQueued = false;

			switch (suitCounter) {
			case 0:
				deck[suitCounter][valueCounter].suit = 's';
				deck[suitCounter][valueCounter].value = valueCounter + 1;
				deck[suitCounter][valueCounter].cardSprite.y = 0;
				break;
			case 1:
				deck[suitCounter][valueCounter].suit = 'h';
				deck[suitCounter][valueCounter].value = valueCounter + 1;
				deck[suitCounter][valueCounter].cardSprite.y = 80;
				break;
			case 2:
				deck[suitCounter][valueCounter].suit = 'd';
				deck[suitCounter][valueCounter].value = valueCounter + 1;
				deck[suitCounter][valueCounter].cardSprite.y = 160;
				break;
			case 3:
				deck[suitCounter][valueCounter].suit = 'c';
				deck[suitCounter][valueCounter].value = valueCounter + 1;
				deck[suitCounter][valueCounter].cardSprite.y = 240;
				break;
			}

			if (deck[suitCounter][valueCounter].value == 1) {
				deck[suitCounter][valueCounter].value = 14;
			}
		}
	}
}


void generateRandomHand(Card hand[5], Card deck[4][13]) {

	int totalCardsInHand = 0;

	while (totalCardsInHand != 5) {
		int randSuit = rand() % 3;
		int randValue = rand() % 13;

		if (deck[randSuit][randValue].isHeld == false) {
			hand[totalCardsInHand] = deck[randSuit][randValue];
			totalCardsInHand++;
			deck[randSuit][randValue].isHeld = true;
		}
	}
}


void renderCards(Card myHand[5], Card dealerHand[5], SDL_Texture* deckSprites, bool handIsOver) {

	SDL_Rect cardpos[5];
	SDL_Rect dealerCardPos[5];
	SDL_Rect deckSprite = { 350, 320, 55, 80 };
	SDL_Rect deckSpritePos = { 129, 320, CARD_WIDTH + 15 , CARD_HEIGHT + 15 };
	SDL_Rect cardBack = { 0, 320, 50, 80 };
	for (int i = 0; i < 5; i++) {
		dealerCardPos[i].w = CARD_WIDTH;
		dealerCardPos[i].h = CARD_HEIGHT;

		dealerCardPos[i].x = (i * (CARD_WIDTH + 15)) + 360;
		dealerCardPos[i].y = 144;


		cardpos[i].w = CARD_WIDTH;
		cardpos[i].h = CARD_HEIGHT;

		cardpos[i].x = (i * (CARD_WIDTH + 15)) + 360;
		cardpos[i].y = 496;

		if (myHand[i].isQueued == true) {
			cardpos[i].y -= 15;
		}

		SDL_RenderCopy(renderer, deckSprites, &myHand[i].cardSprite, &cardpos[i]);
		SDL_RenderCopy(renderer, deckSprites, &cardBack, &dealerCardPos[i]);

		if (handIsOver == true) {
			SDL_RenderCopy(renderer, deckSprites, &dealerHand[i].cardSprite, &dealerCardPos[i]);
		}

	}
	SDL_RenderCopy(renderer, deckSprites, &deckSprite, &deckSpritePos);
}
void sortHandByValue(Card hand[5]) {
	int temp = 0;
	int sortCount = 0;
	while (sortCount != 5) {
		for (int i = 0; i < 5; i++) {
			for (int j = i + 1; j < 5; j++) {
				if (hand[i].value > hand[j].value) {
					temp = hand[i].value;
					hand[i].value = hand[j].value;
					hand[j].value = temp;

				}
			}
		}
		sortCount++;
	}
}
void sortHandByCard(Card hand[5]) {
	Card temp;
	int sortCount = 0;
	while (sortCount != 5) {
		for (int i = 0; i < 5; i++) {
			for (int j = i + 1; j < 5; j++) {
				if (hand[i].value > hand[j].value) {
					temp = hand[i];
					hand[i] = hand[j];
					hand[j] = temp;

				}
			}
		}
		sortCount++;
	}
}

Handtype getHandType(Card hand[5]) {
	sortHandByValue(hand);

	int valueIndex[15] = { { 0 } };
	int suitIndex[4] = { { 0 } };
	int pairCounter = 0;
	int handRank = 0;

	Handtype thisHandsType = highcard;



	for (int valueIndexCounter = 0; valueIndexCounter < 5; valueIndexCounter++) {
		valueIndex[hand[valueIndexCounter].value]++;
	}
	for (int suitIndexCounter = 0; suitIndexCounter < 5; suitIndexCounter++) {
		switch (hand[suitIndexCounter].suit) {
		case 's':
			suitIndex[SPADE_INDEX]++;
			break;
		case 'd':
			suitIndex[DIAMOND_INDEX]++;
			break;
		case 'h':
			suitIndex[HEART_INDEX]++;
			break;
		case 'c':
			suitIndex[CLUB_INDEX]++;
			break;
		}
	}

	for (int index = 2; index < 15; index++) {
		if (valueIndex[index] == 2) {
			pairCounter++;
			if (pairCounter == 1 && handRank < 1) {
				thisHandsType = pair;
				handRank = 1;
			}
			if (pairCounter == 2 && handRank < 2) {
				thisHandsType = twopair;
				handRank = 2;
			}
		}

		if (valueIndex[index] == 3 && handRank < 3) {
			thisHandsType = threeofakind;
			handRank = 3;
			for (int fullHouseCheck = 2; fullHouseCheck < 15; fullHouseCheck++) {
				if (valueIndex[fullHouseCheck] == 2 && fullHouseCheck != index && handRank < 6) {
					thisHandsType = fullhouse;
					handRank = 6;
				}
			}
		}
		if (valueIndex[index] == 4 && handRank < 7) {
			thisHandsType = fourofakind;
			handRank = 7;
		}
	}

	if (hand[0].value == hand[1].value - 1 && handRank < 4) {
		if (hand[1].value == hand[2].value - 1) {
			if (hand[2].value == hand[3].value - 1) {
				if (hand[3].value == hand[4].value - 1 || hand[4].value == hand[0].value + 12) {
					thisHandsType = straight;
					handRank = 4;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		if (suitIndex[i] == 5) {
			if (handRank < 5) {
				thisHandsType = flush;
				handRank = 5;
			}
			if (hand[0].value == hand[1].value - 1 && handRank < 8) {
				if (hand[1].value == hand[2].value - 1) {
					if (hand[2].value == hand[3].value - 1) {
						if (hand[3].value == hand[4].value - 1 || hand[4].value == hand[0].value + 12) {
							thisHandsType = straightflush;
							handRank = 8;
						}
					}
				}
			}
		}
	}

	return thisHandsType;
}

void printHandType(thisHandsType) {
	switch (thisHandsType) {
	case highcard:
		printf("\nThis hand is a high card\n");
		break;
	case pair:
		printf("\nThis hand is a pair\n");
		break;
	case twopair:
		printf("\nThis hand is a two pair\n");
		break;
	case threeofakind:
		printf("\nThis hand is a three of a kind\n");
		break;
	case straight:
		printf("\nThis hand is a straight\n");
		break;
	case flush:
		printf("\nThis hand is a flush\n");
		break;
	case fullhouse:
		printf("\nThis hand is a full house\n");
		break;
	case fourofakind:
		printf("\nThis hand is a four of a kind\n");
		break;
	case straightflush:
		printf("\nThis hand is a straight flush\n");
		break;
	}
}

int scoreHighCard(Card hand[5]) {
	sortHandByValue(hand);
	return ((hand[4].value * 14 * 14 * 14 * 14) + (hand[3].value * 14 * 14 * 14) + (hand[2].value * 14 * 14) + (hand[1].value * 14) + (hand[0].value));
}
int scoreOnePair(Card hand[5]) {
	sortHandByValue(hand);
	int returnValue = 0;
	//P P L M H
	if (hand[0].value == hand[1].value) {
		returnValue = (hand[0].value * 14 * 14 * 14) + (hand[4].value * 14 * 14) + (hand[3].value * 14) + (hand[2].value);
	}
	//L P P M H
	else if (hand[1].value == hand[2].value) {
		returnValue = (hand[1].value * 14 * 14 * 14) + (hand[4].value * 14 * 14) + (hand[3].value * 14) + (hand[0].value);
	}
	//L M P P H
	else if (hand[2].value == hand[3].value) {
		returnValue = (hand[2].value * 14 * 14 * 14) + (hand[4].value * 14 * 14) + (hand[1].value * 14) + (hand[0].value);
	}
	//L M H P P
	else if (hand[3].value == hand[4].value) {
		returnValue = (hand[3].value * 14 * 14 * 14) + (hand[2].value * 14 * 14) + (hand[1].value * 14) + (hand[0].value);
	}
	return returnValue + PAIR;
}
int scoreTwoPair(Card hand[5]) {
	sortHandByValue(hand);
	int returnValue = 0;
	//A PL PL PH PH
	if (hand[1].value == hand[2].value && hand[3].value == hand[4].value) {
		returnValue = (hand[3].value * 14 * 14) + (hand[2].value * 14) + (hand[0].value);
	}
	//PL PL A PH PH
	else if (hand[0].value == hand[1].value && hand[3].value == hand[4].value) {
		returnValue = (hand[3].value * 14 * 14) + (hand[0].value * 14) + (hand[2].value);
	}
	//PL PL PH PH A
	else if (hand[0].value == hand[1].value && hand[2].value == hand[3].value) {
		returnValue = (hand[2].value * 14 * 14) + (hand[0].value * 14) + (hand[4].value);
	}
	return returnValue + TWO_PAIR;
}
int scoreThreeOfAKind(Card hand[5]) {
	sortHandByValue(hand);

	int returnValue = 0;

	//T T T A B
	if (hand[0].value == hand[1].value && hand[1].value == hand[2].value) {
		returnValue = (hand[0].value * 14 * 14) + (hand[4].value * 14) + (hand[3].value);
	}
	//A T T T B
	else if (hand[1].value == hand[2].value && hand[2].value == hand[3].value) {
		returnValue = (hand[1].value * 14 * 14) + (hand[4].value * 14) + (hand[0].value);
	}
	//A B T T T 
	else if (hand[2].value == hand[3].value && hand[3].value == hand[4].value) {
		returnValue = (hand[2].value * 14 * 14) + (hand[1].value * 14) + (hand[0].value);
	}

	return returnValue + THREE_OF_A_KIND;
}
int scoreStraight(Card hand[5]) {
	sortHandByValue(hand);
	return hand[4].value + STRAIGHT;
}
int scoreFlush(Card hand[5]) {
	sortHandByValue(hand);
	int score = ((hand[4].value * 14 * 14 * 14 * 14) + (hand[3].value * 14 * 14 * 14) + (hand[2].value * 14 * 14) + (hand[1].value * 14) + (hand[0].value));
	return score + FLUSH;
}
int scoreFullHouse(Card hand[5]) {
	sortHandByValue(hand);
	return (hand[4].value * 14) + (hand[0].value) + FULL_HOUSE;
}
int scoreFourOfAKind(Card hand[5]) {
	sortHandByValue(hand);

	int returnValue = 0;
	//A F F F F
	if (hand[3].value == hand[4].value) {
		returnValue = (hand[1].value * 14) + (hand[0].value);
	}
	//F F F F A
	else if (hand[0].value == hand[1].value) {
		returnValue = (hand[0].value * 14) + (hand[4].value);
	}

	return returnValue + FOUR_OF_A_KIND;

}
int scoreStraightFlush(Card hand[5]) {
	sortHandByValue(hand);
	return hand[4].value + STRAIGHT;
}
int scoreHand(Card hand[5]) {
	Handtype thisHandsType = getHandType(hand);

	int score = 0;

	switch (thisHandsType) {
	case highcard:
		score = scoreHighCard(hand);
		break;
	case pair:
		score = scoreOnePair(hand);
		break;
	case twopair:
		score = scoreTwoPair(hand);
		break;
	case threeofakind:
		score = scoreThreeOfAKind(hand);
		break;
	case straight:
		score = scoreStraight(hand);
		break;
	case flush:
		score = scoreFlush(hand);
		break;
	case fullhouse:
		score = scoreFullHouse(hand);
		break;
	case fourofakind:
		score = scoreFourOfAKind(hand);
		break;
	case straightflush:
		score = scoreStraightFlush(hand);
		break;
	}
	return score;
}

void cardQueueManager(Card hand[5], Card deck[4][13]) {
	int mouseStateX, mouseStateY = 0;

	SDL_GetMouseState(&mouseStateX, &mouseStateY);

	if (mouseStateY >= 500 && mouseStateY <= 680) {
		if (mouseStateX >= cardOne.topLeftX && mouseStateX <= cardOne.bottomRightX) {
			if (hand[0].isQueued == 1) {
				hand[0].isQueued = 0;
			}
			else if (hand[0].isQueued == 0) {
				hand[0].isQueued = 1;
			}
			printf("\nCard 1 Queue: %d", hand[0].isQueued);
		}

		else if (mouseStateX >= cardTwo.topLeftX && mouseStateX <= cardTwo.bottomRightX) {
			if (hand[1].isQueued == true) {
				hand[1].isQueued = false;
			}
			else if (hand[1].isQueued == false) {
				hand[1].isQueued = true;
			}
			printf("\nCard 2 Queue: %d", hand[1].isQueued);
		}


		else if (mouseStateX >= cardThree.topLeftX && mouseStateX <= cardThree.bottomRightX) {
			if (hand[2].isQueued == 1) {
				hand[2].isQueued = 0;
			}
			else if (hand[2].isQueued == 0) {
				hand[2].isQueued = 1;
			}
			printf("\nCard 3 Queue: %d", hand[2].isQueued);
		}


		else if (mouseStateX >= cardFour.topLeftX && mouseStateX <= cardFour.bottomRightX) {
			if (hand[3].isQueued == true) {
				hand[3].isQueued = false;
			}
			else if (hand[3].isQueued == false) {
				hand[3].isQueued = true;
			}
			printf("\nCard 4 Queue: %d", hand[3].isQueued);
		}


		else if (mouseStateX >= cardFive.topLeftX && mouseStateX <= cardFive.bottomRightX) {

			if (hand[4].isQueued == true) {
				hand[4].isQueued = false;
			}
			else if (hand[4].isQueued == false) {
				hand[4].isQueued = true;
			}
			printf("\nCard 5 Queue: %d", hand[4].isQueued);
		}
	}
}




void shuffleDeck(Card deck[4][13]) {
	for (int suitCounter = 0; suitCounter < 4; suitCounter++) {
		for (int valueCounter = 0; valueCounter < 13; valueCounter++) {
			deck[suitCounter][valueCounter].isHeld = false;
		}
	}
}
void draw(Card hand[5], Card deck[4][13]) {
	int index = 0;


	while (index < 5) {
		if (hand[index].isQueued == false) {
			bool validCard = false;

			while (validCard == false) {
				int randSuit = rand() % 3;
				int randValue = rand() % 13;

				if (deck[randSuit][randValue].isHeld == false) {
					hand[index] = deck[randSuit][randValue];
					deck[randSuit][randValue].isHeld = true;
					validCard = true;
				}
			}
		}
		hand[index].isQueued = false;
		index++;
	}
}
void convertToString(int wager, char dest[6]) {
	char returnString[7];

	int tenThousandsPlace = wager / 10000;
	int thousandsPlace = (wager - (tenThousandsPlace * 10000)) / 1000;
	int oneHundredsPlace = (wager - ((tenThousandsPlace * 10000) + (thousandsPlace * 1000))) / 100;
	int tensPlace = (wager - ((tenThousandsPlace * 10000) + (thousandsPlace * 1000) + (oneHundredsPlace * 100))) / 10;
	int onesPlace = (wager - ((tenThousandsPlace * 10000) + (thousandsPlace * 1000) + (oneHundredsPlace * 100))) - (tensPlace * 10);

	dest[1] = tenThousandsPlace + 48;
	dest[2] = thousandsPlace + 48;
	dest[3] = oneHundredsPlace + 48;
	dest[4] = tensPlace + 48;
	dest[5] = onesPlace + 48;
	dest[6] = '\0';
}
void printWager(int wager, TTF_Font* font) {
	char dest[7];
	dest[0] = '$';
	convertToString(wager, dest);


	SDL_Rect rect = { 969, 306, 236, 104 };
	SDL_Color fontColor = { 0,0,0 };
	SDL_Surface* wagerTextSurface = TTF_RenderText_Solid(font, dest, fontColor);
	if (wagerTextSurface == NULL) {
		printf("ERROR: %s\n", TTF_GetError());
		return 1;
	}
	SDL_Texture* wagerTextTexture = SDL_CreateTextureFromSurface(renderer, wagerTextSurface);
	if (wagerTextTexture == NULL) {
		printf("ERROR: %s\n", TTF_GetError());
		return 1;
	}
	SDL_RenderCopy(renderer, wagerTextTexture, NULL, &rect);
	SDL_DestroyTexture(wagerTextTexture);
	SDL_FreeSurface(wagerTextSurface);
}

void printBalance(int balance, TTF_Font* font) {
	char dest[7];
	dest[0] = '$';
	convertToString(balance, dest);


	SDL_Rect rect = { 642, 699, 161, 43 };
	SDL_Color fontColor = { 0,0,0 };
	SDL_Surface* balanceTextSurface = TTF_RenderText_Solid(font, dest, fontColor);
	if (balanceTextSurface == NULL) {
		printf("ERROR: %s\n", TTF_GetError());
		return 1;
	}
	SDL_Texture* balanceTextTexture = SDL_CreateTextureFromSurface(renderer, balanceTextSurface);
	if (balanceTextTexture == NULL) {
		printf("ERROR: %s\n", TTF_GetError());
		return 1;
	}
	SDL_RenderCopy(renderer, balanceTextTexture, NULL, &rect);
	SDL_DestroyTexture(balanceTextTexture);
	SDL_FreeSurface(balanceTextSurface);
}

SDL_Window *createWindow() {
	SDL_Window *win = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
	if (win == NULL) {
		printf("ERROR: %s\n", IMG_GetError());
		return NULL;
	}
	return win;
}
SDL_Texture *loadTexture(SDL_Renderer* renderer, char filename[]) {
	SDL_Texture *loadedTexture = IMG_LoadTexture(renderer, filename);
	if (loadedTexture == NULL) {
		printf("ERROR: %s\n", IMG_GetError());
		return 1;
	}
	return loadedTexture;
}
SDL_Renderer *createRenderer(SDL_Window *window) {
	SDL_Renderer *ren = SDL_CreateRenderer(window, -1, 0);
	if (ren == NULL) {
		printf("ERROR: %s\n", IMG_GetError());
		return 1;
	}
	return ren;
}
TTF_Font* loadFont(char filename[], int fontSize) {
	TTF_Font* loadedFont = TTF_OpenFont(filename, fontSize);
	if (loadedFont == NULL) {
		printf("ERROR: %s", TTF_GetError());
	}
	return loadedFont;
}
void drawDealerHand(Card dealerHand[5], Card* deck) {
	Handtype dealerHandType = getHandType(dealerHand);

	switch (dealerHandType) {
	case highcard:
		dealerHand[4].isQueued = true;
		draw(dealerHand, deck);
		break;
	case pair:
		//P P L M H
		if (dealerHand[0].value == dealerHand[1].value) {
			dealerHand[0].isQueued = true;
			dealerHand[1].isQueued = true;
		}
		//L P P M H
		else if (dealerHand[1].value == dealerHand[2].value) {
			dealerHand[1].isQueued = true;
			dealerHand[2].isQueued = true;
		}
		//L M P P H
		else if (dealerHand[2].value == dealerHand[3].value) {
			dealerHand[2].isQueued = true;
			dealerHand[3].isQueued = true;
		}
		//L M H P P
		else if (dealerHand[3].value == dealerHand[4].value) {
			dealerHand[3].isQueued = true;
			dealerHand[4].isQueued = true;
		}
		draw(dealerHand, deck);
		break;
	case twopair:
		//A PL PL PH PH
		if (dealerHand[1].value == dealerHand[2].value && dealerHand[3].value == dealerHand[4].value) {
			dealerHand[1].isQueued = true;
			dealerHand[2].isQueued = true;
			dealerHand[3].isQueued = true;
			dealerHand[4].isQueued = true;
		}
		//PL PL A PH PH
		else if (dealerHand[0].value == dealerHand[1].value && dealerHand[3].value == dealerHand[4].value) {
			dealerHand[0].isQueued = true;
			dealerHand[1].isQueued = true;
			dealerHand[3].isQueued = true;
			dealerHand[4].isQueued = true;
		}
		//PL PL PH PH A
		else if (dealerHand[0].value == dealerHand[1].value && dealerHand[2].value == dealerHand[3].value) {
			dealerHand[0].isQueued = true;
			dealerHand[1].isQueued = true;
			dealerHand[2].isQueued = true;
			dealerHand[3].isQueued = true;
		}
		draw(dealerHand, deck);
		break;
	case threeofakind:
		//T T T A B
		if (dealerHand[0].value == dealerHand[1].value && dealerHand[1].value == dealerHand[2].value) {
			dealerHand[0].isQueued = true;
			dealerHand[1].isQueued = true;
			dealerHand[2].isQueued = true;
		}
		//A T T T B
		else if (dealerHand[1].value == dealerHand[2].value && dealerHand[2].value == dealerHand[3].value) {
			dealerHand[1].isQueued = true;
			dealerHand[2].isQueued = true;
			dealerHand[3].isQueued = true;
		}
		//A B T T T 
		else if (dealerHand[2].value == dealerHand[3].value && dealerHand[3].value == dealerHand[4].value) {
			dealerHand[2].isQueued = true;
			dealerHand[3].isQueued = true;
			dealerHand[4].isQueued = true;
		}
		draw(dealerHand, deck);
		break;
	case fourofakind:
		break;
	case straight:
		break;
	case straightflush:
		break;
	case fullhouse:
		break;
	}
}
BUTTONPRESSED getTheOneRulesButton() {
	int mousePosX, mousePosY;

	SDL_GetMouseState(&mousePosX, &mousePosY);

	if (mousePosX >= rulesReturnButton.topLeftX && mousePosX <= rulesReturnButton.bottomRightX) {
		if (mousePosY >= rulesReturnButton.topLeftY && mousePosY <= rulesReturnButton.bottomRightY) {
			return RULESRETURN;
		}
	}
}
BUTTONPRESSED getMenuButtonPressed() {
	int mousePosX, mousePosY;

	SDL_GetMouseState(&mousePosX, &mousePosY);

	if (mousePosX >= playButton.topLeftX && mousePosX <= playButton.bottomRightX) {
		if (mousePosY >= playButton.topLeftY && mousePosY <= playButton.bottomRightY) {
			return PLAYBUTTON;
		}
	}
	if (mousePosX >= rulesButton.topLeftX && mousePosX <= rulesButton.bottomRightX) {
		if (mousePosY >= rulesButton.topLeftY && mousePosY <= rulesButton.bottomRightY) {
			return RULESBUTTON;
		}
	}
	if (mousePosX >= exitButton.topLeftX && mousePosX <= exitButton.bottomRightX) {
		if (mousePosY >= exitButton.topLeftY && mousePosY <= exitButton.bottomRightY) {
			return EXITBUTTON;
		}
	}
}
BUTTONPRESSED getGameButtonPressed() {
	int mousePosX, mousePosY = 0;

	SDL_GetMouseState(&mousePosX, &mousePosY);

	//Check Button
	if (mousePosX >= checkButton.topLeftX && mousePosX <= checkButton.bottomRightX) {
		if (mousePosY >= checkButton.topLeftY && mousePosY <= checkButton.bottomRightY) {
			return CHECK;
		}
	}
	//Fold Button
	if (mousePosX >= foldButton.topLeftX && mousePosX <= foldButton.bottomRightX) {
		if (mousePosY >= foldButton.topLeftY && mousePosY <= foldButton.bottomRightY) {
			return FOLD;
		}
	}
	//Decrease Bet Button
	if (mousePosX >= decreaseBetButton.topLeftX && mousePosX <= decreaseBetButton.bottomRightX) {
		if (mousePosY >= decreaseBetButton.topLeftY && mousePosY <= decreaseBetButton.bottomRightY) {
			return LOWERBET;
		}
	}
	//Increase Bet Button
	if (mousePosX >= increaseBetButton.topLeftX && mousePosX <= increaseBetButton.bottomRightX) {
		if (mousePosY >= increaseBetButton.topLeftY && mousePosY <= increaseBetButton.bottomRightY) {
			return RAISEBET;
		}
	}
	//All in button
	if (mousePosX >= allInButton.topLeftX && mousePosX <= allInButton.bottomRightX) {
		if (mousePosY >= allInButton.topLeftY && mousePosY <= allInButton.bottomRightY) {
			return ALLIN;
		}
	}
	//Reset Bet Button
	if (mousePosX >= resetBetButton.topLeftX && mousePosX <= resetBetButton.bottomRightX) {
		if (mousePosY >= resetBetButton.topLeftY && mousePosY <= resetBetButton.bottomRightY) {
			return RESETBET;
		}
	}
	if (mousePosX >= drawButton.topLeftX && mousePosX <= drawButton.bottomRightX) {
		if (mousePosY >= drawButton.topLeftY && mousePosY <= drawButton.bottomRightY) {
			return DRAW;
		}
	}
	if (mousePosX >= gameReturnButton.topLeftX && mousePosX <= gameReturnButton.bottomRightX) {
		if (mousePosY >= gameReturnButton.topLeftY && mousePosY <= gameReturnButton.bottomRightY) {
			return GAMERETURN;
		}
	}
}


void runGame() {
	srand((unsigned int)(time(NULL)));
	SDL_Texture *deckSprites = loadTexture(renderer, "finaldeck.png");
	SDL_Texture *table = loadTexture(renderer, "finaltable.png");
	SDL_Texture *menu = loadTexture(renderer, "titlescreen.png");
	SDL_Texture *rules = loadTexture(renderer, "rules.png");
	TTF_Font* font = loadFont("font.ttf", 94);


	Card deck[4][13];
	Card hand[5];
	Card dealerHand[5];

	SDL_Event event;

	bool isRunning = true;
	bool canDraw = false;
	bool handIsOver = false;
	bool hasFolded = false;

	int balance = 1000;
	int wager = 0;
	int checkCount = 0;
	int checkWager = 0;
	int gameState = MENU;


	BUTTONPRESSED buttonPressed;


	generateDeck(deck);
	generateRandomHand(hand, deck);
	generateRandomHand(dealerHand, deck);
	sortHandByCard(dealerHand);

	while (isRunning) {


		SDL_RenderClear(renderer);

		if (gameState == MENU) {
			SDL_RenderCopy(renderer, menu, NULL, NULL);
		}
		else if (gameState == RULES) {
			SDL_RenderCopy(renderer, rules, NULL, NULL);
		}
		else if (gameState == GAME) {
			SDL_RenderCopy(renderer, table, NULL, NULL);
			printWager(wager, font);
			printBalance(balance, font);
			renderCards(hand, dealerHand, deckSprites, handIsOver);
		}

		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&event) != 0) {

			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {

				if (gameState == MENU) {
					buttonPressed = getMenuButtonPressed();
				}

				else if (gameState == RULES) {
					buttonPressed = getTheOneRulesButton();
				}

				else if (gameState == GAME) {
					if (canDraw == true) {
						cardQueueManager(hand, deck);
					}
					buttonPressed = getGameButtonPressed();
				}

				switch (buttonPressed) {
				case RULESBUTTON:
					gameState = RULES;
					break;
				case PLAYBUTTON:
					gameState = GAME;
					break;
				case EXITBUTTON:
					isRunning = false;
					break;
				case DRAW:
					if (canDraw == true) {
						draw(hand, deck);
						canDraw = false;
					}
					break;
				case RULESRETURN:
					gameState = MENU;
					break;
				case GAMERETURN:
					balance = 1000;
					gameState = MENU;
					break;
				case CHECK:
					checkCount++;
					if (checkCount == 1) {
						checkWager += 10;
						wager += 10;
						canDraw = true;
						checkWager = wager;
					}
					else if (checkCount == 2) {
						checkWager += 10;
						wager += 10;
						drawDealerHand(dealerHand, deck);
						sortHandByCard(dealerHand);
						handIsOver = true;
						int playerScore = scoreHand(hand);
						int dealerScore = scoreHand(dealerHand);

						if(wager > balance)
							wager = balance;
						if (playerScore > dealerScore) {
							balance += wager;
						}
						else if (dealerScore > playerScore) {
							balance -= wager;
						}
						checkWager = 0;
						wager = 0;
					}
					else if (checkCount == 3) {
						shuffleDeck(deck);
						generateRandomHand(hand, deck);
						generateRandomHand(dealerHand, deck);
						sortHandByCard(dealerHand);
						handIsOver = false;
						checkCount = 0;
					}

					break;
				case FOLD:
					balance -= wager;
					checkWager = 0;
					wager = 0;
					checkCount = 2;
					handIsOver = true;
					hasFolded = true;
					break;
				case LOWERBET:
					wager -= 5;
					break;
				case RAISEBET:
					wager += 5;
					break;
				case ALLIN:
					wager = balance;
					break;
				case RESETBET:
					wager = checkWager;
					break;
				}
				if (handIsOver == true) {
					canDraw = false;
					hasFolded = false;
				}
				if (wager <= checkWager) {
					wager = checkWager;
				}
				if (wager >= balance) {
					wager = balance;
				}
			}
		}
		SDL_Delay(16);
	}
	SDL_DestroyTexture(table);
	SDL_DestroyTexture(deckSprites);
	SDL_DestroyTexture(rules);
	SDL_DestroyTexture(menu);
}
