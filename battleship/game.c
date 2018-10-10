#include "header.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Scorekeeper scorekeeper[2];

/***********************************************************************************
*Function Name: IsOverlap                                                          *
*Function Author: Yours Truly                                                      *                                                              *
*Function Purpose: This function is exclusively used to check valid placements for *
*the cpu's ships only.                                                             *
*Function Summary: This function takes in all the relevant data values for a ship  *
*checks whether or not said ship will collide with another ship via checking the   *
*values of the underboard                                                          *
***********************************************************************************/
int isOverlap(int underboard[10][10], int orient, int length, int x, int y) {
	int returnValue = 1;
	for (int i = 0; i < length; i++) {
		switch (orient) {
		case 0:
			if (underboard[x + i][y] == 1) {
				returnValue = 0;
			}
			break;
		case 1:
			if (underboard[x][y + i] == 1) {
				returnValue = 0;
			}
			break;
		}
	}
	return returnValue;
}


/***********************************************************************************
*Function Name: isOutOfBounds                                                      *
*Function Author: Yours Truly                                                      *
*Function Purpose: This function is exclusively used to check valid placements for *
*the cpu's ships only.                                                             *
*Function Summary: This function takes in all the relevant data values for a ship  *
*checks whether or not said ship will exceed the boundaries of the array           *
***********************************************************************************/
int isOutOfBounds(int x, int y, int length, int orient) {
	int threshold = 9 - length;

	switch (orient) {
	case 0:
		if (x > threshold) {
			return 0;
		}
		else {
			return 1;
		}
		break;
	case 1:
		if (y > threshold) {
			return 0;
		}
		else {
			return 1;
		}
		break;
	}

}

/***********************************************************************************
*Function Name: placeShip                                                          *
*Function Author: Yours Truly                                                      *
*Function Purpose: This function is exclusively used to place the cpu's ships only *
*after checking for validity                                                       *
*Function Summary: This function takes in all the relavent data values for a given *
*ships and switches the values of the underboard properly                          *
***********************************************************************************/
void placeShip(int underboard[10][10], int x, int y, int orient, int length) {
	for (int i = 0; i < length; i++) {
		switch (orient) {
		case 0:
			underboard[x + i][y] = 1;
			break;
		case 1:
			underboard[x][y + i] = 1;
			break;
		}
	}
}

/***********************************************************************************
*Function Name: randomizeShip                                                      *
*Function Author: Yours Truly                                                      *
*Function Purpose: This function randomizes the cpu's board for the sake of variety*
*Function Summary: This functoin generates a random coordinate and orientation,    *
*checks to see if a ship at those coordinates and orientation will fit, and        *
*and places the ship if it does                                                    *
***********************************************************************************/
void randomizeShip(int underboard[10][10]) {

	int ships = 0;
	int length = 5;

	while(ships < 5){
		int validPlace = 0;
		while (validPlace == 0) {

			int xPos = rand() % 10;
			int yPos = rand() % 10;
			int orient = rand() % 2;


			int outofbounds = isOutOfBounds(xPos, yPos, length, orient);
			int overlap = isOverlap(underboard, orient, length, xPos, yPos);

			if (outofbounds == 1 && overlap == 1) {
				placeShip(underboard, xPos, yPos, orient, length);
				validPlace = 1;

			}
			else {
			}


		}
		ships++;
		length--;
		if (length == 1) {
			length += 2;
		}
	}
}
	
//drawbBoard: it draws the board...entirely unnecessary but cleans up the run function
void drawBoard(SDL_Texture* board) {
	SDL_RenderCopy(renderer, board, NULL, NULL);
}

/***********************************************************************************
*Function Name: setTilesToWater                                                    *
*Function Author: Yours Truly                                                      *
*Function Purpose: Sets the two tilesets to an initial state of "water"            *
*Function Summary: This function takes in both tilesets, and cycles through every  *
*Element, setting them to water. This function is only called once                 *
***********************************************************************************/
void setTilesToWater(Tile playerTileset[10][10], Tile cpuTileset[10][10]) {
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			playerTileset[x][y] = WATER;
			cpuTileset[x][y] = WATER;
		}
	}
}

//See setTilesToWater and apply same reasoning except with the underboards
void setUnderboardToZero(int underBoard[10][10]) {
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			underBoard[x][y] = 0;
		}
	}
}

/***********************************************************************************
*Function Name: checkMove                                                          *
*Function Author: Yours Truly                                                      *
*Function Purpose: This function checks the coordinates of a player's or cpu's move*
*to see whether or not it is a hit or a miss and changes the cooresponding tile    *
*accordingly                                                                       *
*Function Summary: This function checks to see if the coordinate given holds a ship*
*by checking the value of the underboard                                           *
***********************************************************************************/
int checkMove(int underBoard[10][10], Tile tileset[10][10], int x, int y, int playerIndex) {
	if (underBoard[x][y] == 0) {
		tileset[x][y] = MISS;
		scorekeeper[playerIndex].misses++;
		if (playerIndex == 1) {
			scorekeeper[1].hits++;
			scorekeeper[1].totalShots++;
			return 5;
		}
		else {
			scorekeeper[0].hits++;
			scorekeeper[0].totalShots++;
			return 3;
		}
	}
	if (underBoard[x][y] == 1) {
		tileset[x][y] = HIT;
		
		if (playerIndex == 1) {
			scorekeeper[1].hits++;
			scorekeeper[1].totalShots++;
			return 6;
		}
		else {
			scorekeeper[0].hits++;
			scorekeeper[0].totalShots++;
			return 2;
		}
	}
}

/***********************************************************************************
*Function Name: drawTiles                                                          *
*Function Author: Yours Truly                                                      *
*Function Purpose: This function draws the tiles to the screen                     *
*Function Summary: This is by far the coolest function in the program. It takes in *
*both tileset arrays and uses the SDL_RenderCopy function to draw the proper tile  *
*to the proper location on the screen. Observe and admire how gracefully the for   *
*loop calculates the pixel coordinates of the screen                               *
***********************************************************************************/
void drawTiles(Tile playerTileset[10][10], Tile cpuTileset[10][10], SDL_Texture* tiles) {
	SDL_Rect playerTilePos = { 0, 0, 64, 64 };
	SDL_Rect cpuTilePos = { 0, 0, 64, 64 };

	SDL_Rect waterTile = { 64, 64, 64, 64 };
	SDL_Rect hitTile = { 128, 64, 64, 64 };
	SDL_Rect missTile = { 64, 128, 64, 64 };
	SDL_Rect highlightedTile = { 128, 128, 64, 64 };
	SDL_Rect potentialTile = { 64, 0, 64, 64 };
	SDL_Rect shipTile = { 0, 0, 64, 64 };
	SDL_Rect potentialHighlighted = { 128, 0, 64, 64 };

	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			playerTilePos.x = (x + 1) * 64;
			playerTilePos.y = (y + 1) * 64;
			
			cpuTilePos.x = ((x + 1) * 64) + 704;
			cpuTilePos.y = (y + 1) * 64;

			Tile playerTileIndex = playerTileset[x][y];
			Tile cpuTileIndex = cpuTileset[x][y];

			switch (playerTileIndex) {
			case WATER:
				SDL_RenderCopy(renderer, tiles, &waterTile, &playerTilePos);
				break;
			case HIT: 
				SDL_RenderCopy(renderer, tiles, &hitTile, &playerTilePos);
				break;
			case MISS:
				SDL_RenderCopy(renderer, tiles, &missTile, &playerTilePos);
				break;
			case HIGHLIGHTED:
				SDL_RenderCopy(renderer, tiles, &highlightedTile, &playerTilePos);
				break;
			case POTENTIALSHIP:
				SDL_RenderCopy(renderer, tiles, &potentialTile, &playerTilePos);
				break;
			case SHIP:
				SDL_RenderCopy(renderer, tiles, &shipTile, &playerTilePos);
				break;
			case POTENTIALHIGHLIGHTED:
				SDL_RenderCopy(renderer, tiles, &potentialHighlighted, &playerTilePos);
			}
			switch (cpuTileIndex) {
			case WATER:
				SDL_RenderCopy(renderer, tiles, &waterTile, &cpuTilePos);
				break;
			case HIT:
				SDL_RenderCopy(renderer, tiles, &hitTile, &cpuTilePos);
				break;
			case MISS:
				SDL_RenderCopy(renderer, tiles, &missTile, &cpuTilePos);
				break;
			case HIGHLIGHTED:
				SDL_RenderCopy(renderer, tiles, &highlightedTile, &cpuTilePos);
				break;
			}
		}
	}
}


//Simple function, used when the player wants to change his or her mind when initiallyy placing ships
//just resets tiles with no ships underneath to water
resetPlayerTileset(Tile tileset[10][10], int underboard[10][10]) {
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (underboard[x][y] != 1) {
				tileset[x][y] = WATER;
			}
		}
	}
}


/***********************************************************************************
*Function Name: cpuMove                                                            *
*Function Author: Yours Truly                                                      *
*Function Purpose: Used to manage cpu moves                                        *
*Function Summary: Generates a random coordinate and checks whether or not there   *
*is a ship underneath                                                              *
***********************************************************************************/
void cpuMove(Tile playerTileset[10][10], int underboard[10][10], int *textIndex) {

	int validMove = 0;

	while (validMove == 0) {
		int randX = rand() % 10;
		int randY = rand() % 10;

		if (playerTileset[randX][randY] == WATER || playerTileset[randX][randY] == SHIP) {
			*textIndex = checkMove(underboard, playerTileset, randX, randY, 1);
			validMove = 1;
		}
	}
}

//cycles through the tilesets and checks if every ship has been hit
int checkIsOver(Tile playerTileset[10][10], Tile cpuTileset[10][10]) {
	int returnValue = 0;
	int playerHits = 0;
	int cpuHits = 0;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (playerTileset[x][y] == HIT) {
				cpuHits++;
			}
			if (cpuTileset[x][y] == HIT) {
				playerHits++;
			}
		}
	}
	if (playerHits == 17) {
		returnValue = 1;
	}
	if (cpuHits == 17) {
		returnValue = 2;
	}
	return returnValue;
}

/***********************************************************************************
*Function Name: manageTextBoxes                                                    *
*Function Author: Yours Truly                                                      *
*Function Purpoes: To manage the text boxes drawn on the bottom left corer of the  *
*screen                                                                            *
*Function Summary: This is another awesome function. it takes in an index and      *
*properly chooses the correct box from texts.png                                   *
***********************************************************************************/
void manageTextBoxes(int textIndex, SDL_Texture *textboxes) {
	SDL_Rect texts[15];
	SDL_Rect textPos = { 70 + 4, 718 + 6, 600, 50 };
	for (int i = 0; i < 15; i++) {
		texts[i].x = 1;
		texts[i].y = (i * 40) + 1;
		texts[i].w = 200;
		texts[i].h =14;
	}

	SDL_RenderCopy(renderer, textboxes, &texts[textIndex], &textPos);
}

void generateValidPlacements(int x, int y, int length, int underboard[10][10], int tileset[10][10]) {
	resetPlayerTileset(tileset, underboard);


	if (x > -1 && x < 10 && y > -1 && y < 10) {
		int isValidUp = 1;
		int isValidDown = 1;
		int isValidLeft = 1;
		int isValidRight = 1;

		for (int i = 0; i < length; i++) {
			for (int i = 0; i < length; i++) {
				if (underboard[x][y + i] == 1) {
					isValidUp = 0;
				}
				if (underboard[x][y - i] == 1) {
					isValidDown = 0;
				}
				if (underboard[x + i][y] == 1) {
					isValidRight = 0;
				}
				if (underboard[x - i][y] == 1) {
					isValidLeft = 0;
				}
			}
		}

		length--;
		if (x + length < 10 && isValidRight == 1) {
			tileset[x + length][y] = POTENTIALSHIP;
		}
		if (y + length < 10 && isValidUp == 1) {
			tileset[x][y + length] = POTENTIALSHIP;
		}
		if (x - length > -1 && isValidLeft == 1) {
			tileset[x - length][y] = POTENTIALSHIP;
		}
		if (y - length > -1 && isValidDown == 1) {
			tileset[x][y - length] = POTENTIALSHIP;
		}
	}
}
void playerPlaceShip(int x, int y, int underboard[10][10], Tile tileset[10][10], int length) {

	length--;
	int originalTileX = 0;
	int originalTileY = 0;
	int sumShips = 0;
	if (tileset[x][y] == POTENTIALHIGHLIGHTED) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (tileset[i][j] == SHIP && underboard[i][j] == 0) {
					originalTileX = i;
					originalTileY = j;
				}
			}
		}
		for (int i = 0; i < length + 1; i++) {
			if (originalTileX == x && originalTileY > y) {
				underboard[x][y + i] = 1;
				tileset[x][y + i] = SHIP;
			}
			else if (originalTileX == x && originalTileY < y) {
				underboard[x][y - i] = 1;
				tileset[x][y - i] = SHIP;
			}
			else if (originalTileX > x && originalTileY == y) {
				underboard[x + i][y] = 1;
				tileset[x + i][y] = SHIP;
			}
			else if (originalTileX < x && originalTileY == y) {
				underboard[x - i][y] = 1;
				tileset[x - i][y] = SHIP;
			}
		}
	}
	resetPlayerTileset(tileset, underboard);
}
int setup(SDL_Event event, Tile playerTileset[10][10], int playerUnderboard[10][10], int length, int *textIndex) {
	if (event.type == SDL_MOUSEMOTION) {
		int mouseX, mouseY = 0;

		SDL_GetMouseState(&mouseX, &mouseY);

		int mouseTileX = (mouseX / 64) - 1;
		int mouseTileY = (mouseY / 64) - 1;
		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				if (mouseTileX == x && mouseTileY == y) {
					if (mouseTileX > -1 && mouseTileX < 11 && mouseTileY > -1 && mouseTileY < 11) {
						if (playerTileset[mouseTileX][mouseTileY] == WATER) {
							playerTileset[x][y] = HIGHLIGHTED;
						}
						if (playerTileset[mouseTileX][mouseTileY] == POTENTIALSHIP) {
							playerTileset[x][y] = POTENTIALHIGHLIGHTED;
						}
					}
				}
				if (x != mouseTileX || y != mouseTileY) {
					if (playerTileset[x][y] == HIGHLIGHTED) {
						playerTileset[x][y] = WATER;
					}
					if (playerTileset[x][y] == POTENTIALHIGHLIGHTED) {
						playerTileset[x][y] = POTENTIALSHIP;
					}
				}
			}
		}
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int mouseX, mouseY = 0;

		SDL_GetMouseState(&mouseX, &mouseY);

		int x = (mouseX / 64) - 1;
		int y = (mouseY / 64) - 1;



		if (playerTileset[x][y] == HIGHLIGHTED) {
			generateValidPlacements(x, y, length, playerUnderboard, playerTileset);
			playerTileset[x][y] = SHIP;
			*textIndex = 1;
		}
		else if (playerTileset[x][y] == POTENTIALHIGHLIGHTED) {
			playerPlaceShip(x, y, playerUnderboard, playerTileset, length);
			*textIndex = 0;
			return 1;
		}
	}
}

void manageBattleship(SDL_Event event, Tile playerTileset[10][10], Tile cpuTileset[10][10], int playerUnderboard[10][10], int cpuUnderboard[10][10], int *turnSwitch, int *textIndex) {
	if (event.type == SDL_MOUSEMOTION) {
		int mouseX, mouseY = 0;

		SDL_GetMouseState(&mouseX, &mouseY);

		int mouseTileX = (mouseX / 64) - 1;
		int mouseTileY = (mouseY / 64) - 1;

		int mouseCpuTileX = ((mouseX - 704) / 64) - 1;
		int mouseCpuTileY = (mouseY / 64) - 1;


		for (int x = 0; x < 10; x++) {
			for (int y = 0; y < 10; y++) {
				if (mouseCpuTileX == x && mouseCpuTileY == y) {
					if (mouseCpuTileX > -1 && mouseCpuTileX < 11 && mouseCpuTileY > -1 && mouseCpuTileY < 11) {
						if (cpuTileset[mouseCpuTileX][mouseCpuTileY] == WATER) {
							cpuTileset[x][y] = HIGHLIGHTED;
						}
					}
				}
				if (x != mouseCpuTileX || y != mouseCpuTileY) {
					if (cpuTileset[x][y] == HIGHLIGHTED) {
						cpuTileset[x][y] = WATER;
					}
				}
			}
		}
	}
	
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		int mouseX, mouseY = 0;



		SDL_GetMouseState(&mouseX, &mouseY);

		int mouseCpuTileX = (((mouseX - 704) / 64) - 1);
		int mouseCpuTileY = (mouseY / 64) - 1;
		if (cpuTileset[mouseCpuTileX][mouseCpuTileY] == HIGHLIGHTED) {
			*textIndex = checkMove(cpuUnderboard, cpuTileset, mouseCpuTileX, mouseCpuTileY, 0);
			*turnSwitch = 1;
		}
	}
}

//managePauseAmbience pauses for the cpu's turn. Entirely unnecessary, but it adds.
/*
void managePauseAmbience(int* textIndex) {
	if (*textIndex == 2 || *textIndex == 3) {
		Sleep(1000);
		*textIndex = 4;
	}
}
*/

//sets every value in scorekeeper to 0. Yes I know its global I didnt want to rewrite every
//function parameter
void initScoreKeeper() {
	for (int x = 0; x < 2; x++) {
		scorekeeper[x].hits = 0;
		scorekeeper[x].misses = 0;
		scorekeeper[x].totalShots = 0;
	}
}


void printResults(int winner) {

	FILE* outfile = NULL;
	outfile = fopen("data.txt", "w");
	double playerHitMissRatio = (double)scorekeeper[0].hits / (double)scorekeeper[0].misses;
	double cpuHitMissRatio = (double)scorekeeper[1].hits / (double)scorekeeper[1].misses;
	if (winner == 0) {
		fprintf(outfile, "Winner: PLAYER\n");
	}
	else if (winner == 1) {
		fprintf(outfile, "Winner: CPU\n");
	}
	fprintf(outfile, "Player Total Shots: %d\nPlayer Hit/Miss Ratio: %lf\n", scorekeeper[0].totalShots, playerHitMissRatio);
	fprintf(outfile, "CPU Total Shots: %d\nCPU Hit/Miss Ratio: %lf\n", scorekeeper[1].totalShots, cpuHitMissRatio);
	
}
//Opens all of the resources, runs game loop.
int run() {

	window = SDL_CreateWindow("Battleship!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1408, 800, 0);
	if (window == NULL) {
		return 1;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == NULL) {
		return 1;
	}

	SDL_Texture* gameboard = IMG_LoadTexture(renderer, "gameboard.png");
	if (gameboard == NULL) {
		return 1;
	}
	SDL_Texture* titleScreen = IMG_LoadTexture(renderer, "titlescreen.png");
	if (titleScreen == NULL) {
		return 1;
	}
	SDL_Surface* tileSurface = IMG_Load("tiles.png");
	SDL_Texture* tiles = NULL;
	if (tileSurface == NULL) {
		return 1;
	}
	else {
		SDL_SetColorKey(tileSurface, SDL_TRUE, SDL_MapRGB(tileSurface->format, 255, 0, 255));
		tiles = SDL_CreateTextureFromSurface(renderer, tileSurface);
		SDL_FreeSurface(tileSurface);
		if (tiles == NULL) {
			return 1;
		}
	}
	SDL_Texture *textboxes = IMG_LoadTexture(renderer, "texts.png");
	if (textboxes == NULL) {
		return 1;
	}
	SDL_Texture *winScreen = IMG_LoadTexture(renderer, "playerwinscreen.png");
	if (winScreen == NULL) {
		return 1;
	}
	SDL_Texture *loseScreen = IMG_LoadTexture(renderer, "playerlosescreen.png");
	if (loseScreen == NULL) {
		return 1;
	}

	SDL_Event event;
	Tile playerTileset[10][10];
	Tile cpuTileset[10][10];

	int playerUnderboard[10][10];
	int cpuUnderboard[10][10];

	srand((unsigned int)(time(NULL)));

	setTilesToWater(playerTileset, cpuTileset);

	setUnderboardToZero(cpuUnderboard);
	setUnderboardToZero(playerUnderboard);
	randomizeShip(cpuUnderboard);



	int hasSetUp = 0;
	int length = 5;
	int shipsPlaced = 0;
	int turnSwitch = 0;
	int textIndex = 0;
	int gameOver = 0;
	int isMenu = 1;

	initScoreKeeper();

	int isRunning = 1;


	while (isRunning == 1) {

		SDL_RenderClear(renderer);
		if (isMenu == 1) {
			SDL_RenderCopy(renderer, titleScreen, NULL, NULL);
		}
		else if (gameOver == 1) {
			SDL_RenderCopy(renderer, winScreen, NULL, NULL);
			printResults(0);
		}
		else if (gameOver == 2) {
			SDL_RenderCopy(renderer, loseScreen, NULL, NULL);
			printResults(1);
		}
		else {
			drawBoard(gameboard);
			drawTiles(playerTileset, cpuTileset, tiles);
			manageTextBoxes(textIndex, textboxes);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(16);

		while (SDL_PollEvent(&event) != 0) {

			if (event.type == SDL_KEYDOWN) {
				isMenu = 0;
			}

			if (hasSetUp == 0 && isMenu == 0) {
				int placedShip = setup(event, playerTileset, playerUnderboard, length, &textIndex);
				if (placedShip == 1) {
					placedShip = 0;
					length--;
					shipsPlaced++;
					if (shipsPlaced == 5) {
						textIndex = 4;
						hasSetUp = 1;
					}
					if (length == 1) {
						length = 3;
					}
				}
			}
			if (hasSetUp == 1 && gameOver == 0) {
				if (turnSwitch == 1) {
					cpuMove(playerTileset, playerUnderboard, &textIndex);
					turnSwitch = 0;
				}
				manageBattleship(event, playerTileset, cpuTileset, playerUnderboard, cpuUnderboard, &turnSwitch, &textIndex);
				gameOver = checkIsOver(playerTileset, cpuTileset);
			}
		}
		if (event.type == SDL_QUIT) {
			isRunning = 0;
		}
	}
	SDL_DestroyTexture(gameboard);
	SDL_DestroyTexture(tiles);
	SDL_DestroyTexture(loseScreen);
	SDL_DestroyTexture(winScreen);
	SDL_DestroyTexture(titleScreen);
	SDL_DestroyTexture(textboxes);
}
