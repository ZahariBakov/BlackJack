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
	Game();/*!< Default construcotr*/
	~Game();/*!< Destructor*/

	/**
	 * Initializes the game.
	 *
	 * @param title The title of the window.
	 * @param xpos The initial x position of the window.
	 * @param ypos The initial y position of the window.
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @param flags The flags for the window.
	 * @return True if initialization succeeds, false otherwise.
	 */
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);

	/**
	 * Initializes SDL TTF for text rendering.
	 *
	 * @return True if initialization succeeds, false otherwise.
	 */
	bool ttf_init();

	void update();/*!< Update the game state*/
	void render();/*!< Render the game*/
	void handleEvents();/*!< Handle user events*/
	void clean();/*!< Cleans up resources and shuts down SDL.*/

	bool isRunning() const;/*!< Checks if the game is still running.*/
	void clickedBtn(int xDown, int yDown, int xUp, int yUp);/*!< Handles button clicks.*/

private:
	SDL_Window* window = NULL;/*!< The game window*/
	SDL_Renderer* renderer = NULL;/*!< The renderer for rendering graphics*/
	bool running, stayClicked, isBet, isStay;

	/// Textures
	SDL_Texture* dealerTexture,
		* playerTexture,
		* scoreTexture,
		* scoreStrTexture,
		* moneyTexture,
		* moneyStrTexture,
		* betStrTexture,
		* betTexture,
		* hitBtnTexture,
		* stayBtnTexture,
		* dealerScoreTexture,
		* dealerScoreStrTexture,
		* minBetBtnTexture,
		* maxBetBtnTexture,
		* quitBtnTexture,
		* okBtnTexture;

	/// Rectangles for positionong textures
	SDL_Rect dealerRect,
		playerRect,
		scoreRect,
		scoreStrRect,
		moneyRect,
		moneyStrRect,
		betStrRect,
		betRect,
		hitBtnRect,
		stayBtnRect,
		dealerScoreRect,
		dealerScoreStrRect,
		minBetBtnRect,
		maxBetBtnRect,
		quitBtnRect,
		okBtnRect;

	int mouseDownX, mouseDownY;/*!< Mouse coordinates*/
	CardDeck mainDeck;
};
