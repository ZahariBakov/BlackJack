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
	int mouseDownX, mouseDownY, betFlag;

	SDL_Texture* dealerTexture,
		* playerTexture,
		* moneyTexture,
		* scoreTexture,
		* dealerScoreTexture,
		* betTexture,
		* minBetTexture,
		* maxBetTexture,
		* hitBtnTexture,
		* stayBtnTexture,
		* minBetBtnTexture,
		* maxBetBtnTexture,
		* quitBtnTexture,
		* okBtnTexture;

	SDL_Rect dealerRect,
		playerRect,
		moneyRect,
		scoreRect,
		dealerScoreRect,
		betRect,
		minBetRect,
		maxBetRect,
		hitBtnRect,
		stayBtnRect,
		minBetBtnRect,
		maxBetBtnRect,
		quitBtnRect,
		okBtnRect;
};
