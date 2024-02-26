#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "TextureManager.h"
#include "Player.h"
#include "CardDeck.h"
#include "Dealer.h"

class Game {
public:
	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	bool ttf_init();

	void render();
	void handleEvents();
	void update();
	void clean();

	bool isRunning() const;
	void clickedBtn(int xDown, int yDown, int xUp, int yUp);

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running, isStay, isRound;

	SDL_Texture* dealerTexture,
		* playerTexture,
		* scoreTexture,
		* scoreStrTexture,
		* moneyTexture,
		* moneyStrTexture,
		* betStrTexture,
		* minBetTexture,
		* maxBetTexture,
		* hitBtnTexture,
		* stayBtnTexture,
		* dealerScoreTexture,
		* dealerScoreStrTexture,
		* minBetBtnTexture,
		* maxBetBtnTexture,
		* quitBtnTexture,
		* okBtnTexture;

	SDL_Rect dealerRect,
		playerRect,
		scoreRect,
		scoreStrRect,
		moneyRect,
		moneyStrRect,
		betStrRect,
		minBetRect,
		maxBetRect,
		hitBtnRect,
		stayBtnRect,
		dealerScoreRect,
		dealerScoreStrRect,
		minBetBtnRect,
		maxBetBtnRect,
		quitBtnRect,
		okBtnRect;

	int mouseDownX, mouseDownY;
	
	int isBet;
};
