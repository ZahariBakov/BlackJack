#include "Game.h"

#include <string>

std::string thirdCardName;

Player* player;
Dealer* dealer;

/// Default constructor
Game::Game() {
	Game::window = NULL;
	Game::renderer = NULL;

	Game::running = true;
	Game::stayClicked = false;
	Game::isBet = false;

	/// Initialize texture pointers
	Game::dealerTexture = NULL;
	Game::playerTexture = NULL;
	Game::scoreTexture = NULL;
	Game::scoreStrTexture = NULL;
	Game::moneyTexture = NULL;
	Game::moneyStrTexture = NULL;
	Game::betTexture = NULL;
	Game::betStrTexture = NULL;
	Game::hitBtnTexture = NULL;
	Game::stayBtnTexture = NULL;
	Game::dealerScoreTexture = NULL;
	Game::dealerScoreStrTexture = NULL;
	Game::minBetBtnTexture = NULL;
	Game::maxBetBtnTexture = NULL;

	/// Initialize rectangles
	Game::dealerRect = { 0, 0, 0, 0 };
	Game::playerRect = { 0, 0, 0, 0 };
	Game::scoreRect = { 0, 0, 0, 0 };
	Game::scoreStrRect = { 0, 0, 0, 0 };
	Game::moneyRect = { 0, 0, 0, 0 };
	Game::moneyStrRect = { 0, 0, 0, 0 };
	Game::betRect = { 0, 0, 0, 0 };
	Game::betStrRect = { 0, 0, 0, 0 }; 
	Game::hitBtnRect = { 0, 0, 0, 0 };
	Game::stayBtnRect = { 0, 0, 0, 0 };
	Game::dealerScoreRect = { 0, 0, 0, 0 };
	Game::dealerScoreStrRect = { 0, 0, 0, 0 };
	Game::minBetBtnRect = { 0, 0, 0, 0 };
	Game::maxBetBtnRect = { 0, 0, 0, 0 };

	Game::mouseDownX = Game::mouseDownY = 0;/*!< Initialize mouse coordinates to 0*/
}

/// Destructor
Game::~Game() {
	//delete renderer;
}

/// Initialize SDL and create window, renderer
bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
	/// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success!\n";

		/// Create window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);/*!< */
		if (window != 0) {
			std::cout << "Window creation success!\n";

			/// Get window surface
			renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer != 0) {
				std::cout << "Renderer creation success!\n";

				Game::mainDeck.shuffle();

				player = new Player(mainDeck);
				dealer = new Dealer(mainDeck);
				
				/// Load textures
				TextureManager::Instance()->loadTexture("assets/table-background.jpg", "background", renderer);
				TextureManager::Instance()->loadTexture("assets/cards/cardBack_blue3.png", "card-back", renderer);
			}
			else {
				std::cout << "Renderer init failed!\n";
				return false;
			}
		}
		else {
			std::cout << "Window init failed!\n";
			return false;
		}
	}
	else {
		std::cout << "SDL init fail!\n";
		return false;
	}
	std::cout << "Init success!\n";
	running = true;

	return true;
}

/// Function to initoalize TTF and render text 
bool Game::ttf_init() {
	if (TTF_Init() == -1) {
		return false;
	}

	/// Load fonts
	TTF_Font* font1 = TTF_OpenFont("fonts/Arcade.ttf", 24);
	TTF_Font* font2 = TTF_OpenFont("fonts/COLONNA.ttf", 20);
	TTF_Font* font3 = TTF_OpenFont("fonts/arial.ttf", 24);

	/// Check if fonts are loaded
	if (font1 == NULL || font2 == NULL || font3 == NULL) {
		std::cout << "Font 1 or Font 2 or Font3 is NULL" << std::endl;
		return false;
	}

	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);/*!< Get window size*/

	SDL_Surface* tempSurfaceText = NULL;/*!< Declare variable text rendering*/

	/// Render text using fonts to create textures for displaying
	tempSurfaceText = TTF_RenderText_Blended(font1, "DEALER :", { 0, 0, 0, 255 });
	dealerTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font1, "PLAYER :", { 0, 0, 0, 255 });
	playerTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "Money: $", { 255, 255, 255, 255 });
	moneyStrTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	/// Decrease the player's money by the amount of their bet and convert the updated money value to a char const*.
	std::string t = std::to_string(player->getMoney());
	char const* playerMoneyToString = t.c_str();

	tempSurfaceText = TTF_RenderText_Blended(font2, playerMoneyToString, { 255, 255, 255, 255 });
	moneyTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "Score: ", { 255, 255, 255, 255 });
	scoreStrTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	dealerScoreStrTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	if (Game::isBet) {
		/// Get the player's score and convert the value to a string.
		t = std::to_string(player->getScore());
		char const* scoreStr = t.c_str();

		tempSurfaceText = TTF_RenderText_Blended(font2, scoreStr, { 255, 255, 255, 255 });
		scoreTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

		/// Get the dealer's score and convert to a string
		t = std::to_string(dealer->getScore());
		char const* dealerScoreStr = t.c_str();

		tempSurfaceText = TTF_RenderText_Blended(font2, dealerScoreStr, { 255, 255, 255, 255 });
		dealerScoreTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	}

	tempSurfaceText = TTF_RenderText_Blended(font2, "Current Bet: $", { 255, 255, 255, 255 });
	betStrTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	/// Convert the player's bet amount to a string for display.
	if (Game::isBet) {
		t = std::to_string(player->getBet());
		char const* betStr = t.c_str();

		tempSurfaceText = TTF_RenderText_Blended(font2, betStr, { 255, 255, 255, 255 });
		betTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	}

	/// Buttons
	tempSurfaceText = TTF_RenderText_Blended(font3, "HIT", { 255, 255, 255, 255 });
	hitBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "STAY", { 255, 255, 255, 255 });
	stayBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "BET 100", { 255, 255, 255, 255 });
	minBetBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "BET 1000", { 255, 255, 255, 255 });
	maxBetBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	/// Query the dimensions of each texture and set corresponding rectangles for rendering.
	int tw, th;

	// Dealer
	SDL_QueryTexture(dealerTexture, 0, 0, &tw, &th);
	dealerRect = { 10, 10, tw, th };

	// Player
	SDL_QueryTexture(playerTexture, 0, 0, &tw, &th);
	playerRect = { 10, wh / 2 + 10, tw, th };

	// Money string
	SDL_QueryTexture(moneyStrTexture, 0, 0, &tw, &th);
	moneyStrRect = { 10, wh / 2 + 30, tw, th };

	// Money value
	SDL_QueryTexture(moneyTexture, 0, 0, &tw, &th);
	moneyRect = { 85, wh / 2 + 30, tw, th };

	// Score string
	SDL_QueryTexture(scoreStrTexture, 0, 0, &tw, &th);
	scoreStrRect = { 10, wh / 2 + 50, tw, th };

	SDL_QueryTexture(dealerScoreStrTexture, 0, 0, &tw, &th);
	dealerScoreStrRect = { 10, 30, tw, th };

	// Score value
	SDL_QueryTexture(scoreTexture, 0, 0, &tw, &th);
	scoreRect = { 70, wh / 2 + 50, tw, th };

	SDL_QueryTexture(dealerScoreTexture, 0, 0, &tw, &th);
	dealerScoreRect = { 70, 30, tw, th };

	// Bet string
	SDL_QueryTexture(betStrTexture, 0, 0, &tw, &th);
	betStrRect = { 10, wh / 2 + 70, tw, th };

	// Bet value
	SDL_QueryTexture(betTexture, 0, 0, &tw, &th);
	betRect = { 125, wh / 2 + 70, tw, th };

	/// Buttons
	// Hit button
	SDL_QueryTexture(hitBtnTexture, 0, 0, &tw, &th);
	hitBtnRect = { 30, wh / 2 + 120, tw, th };

	// Stay button
	SDL_QueryTexture(stayBtnTexture, 0, 0, &tw, &th);
	stayBtnRect = { 30, wh / 2 + 175, tw, th };

	// bet button
	SDL_QueryTexture(minBetBtnTexture, 0, 0, &tw, &th);
	minBetBtnRect = { 30, wh / 2 + 230, tw, th };

	SDL_QueryTexture(maxBetBtnTexture, 0, 0, &tw, &th);
	maxBetBtnRect = { 170, wh / 2 + 230, tw, th };

	/// Free resources allocated for temporary surfaces and fonts.
	SDL_FreeSurface(tempSurfaceText);
	TTF_CloseFont(font1);
	TTF_CloseFont(font2);
	TTF_CloseFont(font3);

	return true;
}

void Game::update() {}

/// Render function
void Game::render() {
	//SDL_SetRenderDrawColor(renderer, 0, 153, 0, 255); // base table color
	SDL_RenderClear(renderer);/*!<Clear renderer*/

	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);/*!< Get window size and store*/

	/// Drawing background and cards
	TextureManager::Instance()->drawTexture("background", 0, 0, ww, wh, renderer);

	if (Game::isBet) {
		int x = 180;
		std::string cardname = "player";

		for (int i = 0; i < player->numberOfCards; ++i) {
			if (i > 0) {
				x = 180 + (i * 30);
			}
			cardname += std::to_string(i);

			TextureManager::Instance()->loadTexture(player->playerCards[i].toStringSuit().c_str(), cardname, renderer);
			TextureManager::Instance()->drawTexture(cardname, x, wh / 2 + 20, 140, 190, renderer);
		}

		TextureManager::Instance()->loadTexture(dealer->dealerCards[0].toStringSuit().c_str(), "firstdealerCard", renderer);
		TextureManager::Instance()->drawTexture("firstdealerCard", 150, 10, 140, 190, renderer);
		TextureManager::Instance()->drawTexture("card-back", 180, 10, 140, 190, renderer);
	}
	
	/// Drawing a line in the middle
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, 0, wh / 2, ww, wh / 2);

	/// Draw a buttons
	TextureManager::Instance()->drawRecnatgle(renderer, 10, wh / 2 + 115, 80, 40);
	TextureManager::Instance()->drawRecnatgle(renderer, 10, wh / 2 + 170, 100, 40);
	TextureManager::Instance()->drawRecnatgle(renderer, 10, wh / 2 + 225, 130, 40);
	TextureManager::Instance()->drawRecnatgle(renderer, 160, wh / 2 + 225, 130, 40);

	/// Render texture on window
	SDL_RenderCopy(renderer, dealerTexture, NULL, &dealerRect);
	SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

	SDL_RenderCopy(renderer, scoreStrTexture, NULL, &scoreStrRect);
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
	SDL_RenderCopy(renderer, dealerScoreStrTexture, NULL, &dealerScoreStrRect);
	SDL_RenderCopy(renderer, dealerScoreTexture, NULL, &dealerScoreRect);

	SDL_RenderCopy(renderer, moneyStrTexture, NULL, &moneyStrRect);
	SDL_RenderCopy(renderer, moneyTexture, NULL, &moneyRect);
	
	SDL_RenderCopy(renderer, betStrTexture, NULL, &betStrRect);
	SDL_RenderCopy(renderer, betTexture, NULL, &betRect);
	SDL_RenderCopy(renderer, hitBtnTexture, NULL, &hitBtnRect);
	SDL_RenderCopy(renderer, stayBtnTexture, NULL, &stayBtnRect);
	SDL_RenderCopy(renderer, minBetBtnTexture, NULL, &minBetBtnRect);
	SDL_RenderCopy(renderer, maxBetBtnTexture, NULL, &maxBetBtnRect);
	

	SDL_RenderPresent(renderer);
}

/// Handle user events
void Game::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		int msx, msy;

		switch (event.type) {
		case SDL_QUIT: /*!< Quit if X is clicked */
			running = false;
			break;
		case SDL_MOUSEBUTTONDOWN: {/*!< Get mouse button press (left mouse button)*/
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&msx, &msy);/*!< Get mouse coordinates*/

				/// Store mouse coordinates
				Game::mouseDownX = msx;
				Game::mouseDownY = msy;
			}
		}; break;
		case SDL_MOUSEBUTTONUP: {/*!< Get mouse button release (left mouse button)*/
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&msx, &msy);/*!< Get mouse coordinates*/
				Game::clickedBtn(mouseDownX, mouseDownY, msx, msy);/*!< Check if any button is pressed*/
			}
		}

		default: break;
		}
	}
}

/// Clean up resources and shut down SDL
void Game::clean() {
	std::cout << "Cleaning game!\n";
	SDL_DestroyWindow(window);/*!< Destroy window*/
	SDL_DestroyRenderer(renderer);/*!< Destroy renderer*/
	SDL_Quit();/*!< Quit SDL*/
}

/// Check if the game is still running
bool Game::isRunning() const {
	return Game::running;
}

/// Checking if a button is pressed
void Game::clickedBtn( int xDown, int yDown, int xUp, int yUp) {
	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);/*!< Get window size*/

	/// Hit button coordinates and size
	int hitBtnX = 10;
	int hitBtnY = wh / 2 + 115;
	int hitBtnW = 80;
	int hitBtnH = 40;

	/// Check if Hit button is clicked
	if ((xDown > hitBtnX && xDown < (hitBtnX + hitBtnW)) && (xUp > hitBtnX && xUp < (hitBtnX + hitBtnW)) &&
		(yDown > hitBtnY && yDown < (hitBtnY + hitBtnH)) && (yUp > hitBtnY && yUp < (hitBtnY + hitBtnH))) {
		std::cout << "HIT button is clicked" << std::endl;
		player->addCard(mainDeck);

		return;
	}

	/// Stay button coordinates and size
	int stayBtnX = 10;
	int stayBtnY = wh / 2 + 175;
	int stayBtnW = 100;
	int stayBtnH = 40;

	/// Check if Stay button is clicked
	if ((xDown > stayBtnX && xDown < (stayBtnX + stayBtnW)) && (xUp > stayBtnX && xUp < (stayBtnX + stayBtnW)) &&
		(yDown > stayBtnY && yDown < (stayBtnY + stayBtnH)) && (yUp > stayBtnY && yUp < (stayBtnY + stayBtnH))) {
		std::cout << "STAY button is clicked" << std::endl;

		return;
	}

	/// min Bet button coordinates and size
	int minBetBtnX = 10;
	int minBetBtnY = wh / 2 + 225;
	int minBetBtnW = 130; 
	int minBetBtnH = 40;

	/// Check if min Bet button is clicked
	if ((xDown > minBetBtnX && xDown < (minBetBtnX + minBetBtnW)) && (xUp > minBetBtnX && xUp < (minBetBtnX + minBetBtnW)) &&
		(yDown > minBetBtnY && yDown < (minBetBtnY + minBetBtnH)) && (yUp > minBetBtnY && yUp < (minBetBtnY + minBetBtnH))) {
		std::cout << "min BET button is clicked" << std::endl;
		if (!Game::isBet) {
			Game::isBet = true;
			player->setBet(false);
		}

		return;
	}

	/// miax Bet button coordinates and size
	int maxBetBtnX = 160;
	int maxBetBtnY = wh / 2 + 225;
	int maxBetBtnW = 130;
	int maxBetBtnH = 40;

	/// Check if max Bet button is clicked
	if ((xDown > maxBetBtnX && xDown < (maxBetBtnX + maxBetBtnW)) && (xUp > maxBetBtnX && xUp < (maxBetBtnX + maxBetBtnW)) &&
		(yDown > maxBetBtnY && yDown < (maxBetBtnY + maxBetBtnH)) && (yUp > maxBetBtnY && yUp < (maxBetBtnY + maxBetBtnH))) {
		std::cout << "max BET button is clicked" << std::endl;
		if (!Game::isBet) {
			Game::isBet = true;
			player->setBet(true);
		}

		return;
	}
}
