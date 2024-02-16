#include "Game.h"

#include <string>

std::string thirdCardName;

Player* player;

/// Default constructor
Game::Game() {
	Game::window = NULL;
	Game::renderer = NULL;

	Game::running = true;

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

				//Card firstDealerCard = mainDeck.dealCard();
				//Card firstPlayerCard = mainDeck.dealCard();
				//player->increaseCards();
				//player->increaseScore(firstPlayerCard.getPoint());

				//Card secondDealerCard = mainDeck.dealCard();
				//Card secondPlayerCard = mainDeck.dealCard();
				//player->increaseCards();
				//player->increaseScore(secondPlayerCard.getPoint());

				//Card thirdPlayerCard = mainDeck.dealCard();
				//Card fourthPlayerCard = mainDeck.dealCard();
				//Card fifthPlayerCard = mainDeck.dealCard();
				
				/// Load textures
				TextureManager::Instance()->loadTexture("assets/table-background.jpg", "background", renderer);
				TextureManager::Instance()->loadTexture("assets/cards/cardBack_blue3.png", "card-back", renderer);

				//TextureManager::Instance()->loadTexture(firstDealerCard.toStringSuit().c_str(), "firstdealerCard", renderer);
				//TextureManager::Instance()->loadTexture(secondDealerCard.toStringSuit().c_str(), "secondDealerCard", renderer);
				//TextureManager::Instance()->loadTexture(firstPlayerCard.toStringSuit().c_str(), "firstPlayerCard", renderer);
				//TextureManager::Instance()->loadTexture(secondPlayerCard.toStringSuit().c_str(), "secondPlayerCard", renderer);
				//TextureManager::Instance()->loadTexture(thirdPlayerCard.toStringSuit().c_str(), "thirdPlayerCard", renderer);
				//TextureManager::Instance()->loadTexture(fourthPlayerCard.toStringSuit().c_str(), "fourthPlayerCard", renderer);
				//TextureManager::Instance()->loadTexture(fifthPlayerCard.toStringSuit().c_str(), "fifthPlayerCard", renderer);

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
	player->getMoney();
	std::string t = std::to_string(player->getMoney());
	char const* playerMoneyToString = t.c_str();

	tempSurfaceText = TTF_RenderText_Blended(font2, playerMoneyToString, { 255, 255, 255, 255 });
	moneyTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "Score: ", { 255, 255, 255, 255 });
	scoreStrTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	/// Get the player's score and convert the value to a string.
	player->getScore();
	t = std::to_string(player->getScore());
	char const* scoreStr = t.c_str();

	tempSurfaceText = TTF_RenderText_Blended(font2, scoreStr, { 255, 255, 255, 255 });
	scoreTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "Current Bet: $", { 255, 255, 255, 255 });
	betStrTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	/// Convert the player's bet amount to a string for display.
	//t = std::to_string(player->getBet());
	//char const* betStr = t.c_str();

	//tempSurfaceText = TTF_RenderText_Blended(font2, betStr, { 255, 255, 255, 255 });
	//betTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "HIT", { 255, 255, 255, 255 });
	hitBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "STAY", { 255, 255, 255, 255 });
	stayBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

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

	// Score value
	SDL_QueryTexture(scoreTexture, 0, 0, &tw, &th);
	scoreRect = { 70, wh / 2 + 50, tw, th };

	// Bet string
	SDL_QueryTexture(betStrTexture, 0, 0, &tw, &th);
	betStrRect = { 10, wh / 2 + 70, tw, th };

	// Bet value
	SDL_QueryTexture(betTexture, 0, 0, &tw, &th);
	betRect = { 125, wh / 2 + 70, tw, th };

	// Hit button
	SDL_QueryTexture(hitBtnTexture, 0, 0, &tw, &th);
	hitBtnRect = { 30, wh / 2 + 120, tw, th };

	// Stay button
	SDL_QueryTexture(stayBtnTexture, 0, 0, &tw, &th);
	stayBtnRect = { 30, wh / 2 + 180, tw, th };

	/// Free resources allocated for temporary surfaces and fonts.
	SDL_FreeSurface(tempSurfaceText);
	TTF_CloseFont(font1);
	TTF_CloseFont(font2);
	TTF_CloseFont(font3);

	return true;
}

void Game::update() {
	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);/*!< Get window size and store*/

	
}

/// Render function
void Game::render() {
	//SDL_SetRenderDrawColor(renderer, 0, 153, 0, 255); // base table color
	SDL_RenderClear(renderer);/*!<Clear renderer*/

	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);/*!< Get window size and store*/

	/// Drawing background and cards
	TextureManager::Instance()->drawTexture("background", 0, 0, ww, wh, renderer);
	TextureManager::Instance()->drawTexture("firstdealerCard", 150, 10, 140, 190, renderer);
	TextureManager::Instance()->drawTexture("card-back", 180, 10, 140, 190, renderer);
	//TextureManager::Instance()->drawTexture("firstPlayerCard", 180, wh / 2 + 20, 140, 190, renderer);
	//TextureManager::Instance()->drawTexture("secondPlayerCard", 210, wh / 2 + 20, 140, 190, renderer);
	TextureManager::Instance()->drawTexture("thirdPlayerCard", 210, wh / 2 + 20, 140, 190, renderer);

	int x = 180;
	std::string cardname = "player";

	for (int i = 0; i < player->numberOfCards; ++i) {
		if (i > 0) {
			x += i * 30;
		}
		cardname += std::to_string(i);

		TextureManager::Instance()->loadTexture(player->playerCards[i].toStringSuit().c_str(), cardname, renderer);
		TextureManager::Instance()->drawTexture(cardname, x, wh / 2 + 20, 140, 190, renderer);
	}



	/// Drawing a line in the middle
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, 0, wh / 2, ww, wh / 2);

	/// Draw a buttons
	TextureManager::Instance()->drawRecnatgle(renderer, 10, wh / 2 + 115, 80, 40);
	TextureManager::Instance()->drawRecnatgle(renderer, 10, wh / 2 + 175, 100, 40);

	/// Render texture on window
	SDL_RenderCopy(renderer, dealerTexture, NULL, &dealerRect);
	SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);
	SDL_RenderCopy(renderer, moneyStrTexture, NULL, &moneyStrRect);
	SDL_RenderCopy(renderer, moneyTexture, NULL, &moneyRect);
	SDL_RenderCopy(renderer, scoreStrTexture, NULL, &scoreStrRect);
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
	SDL_RenderCopy(renderer, betStrTexture, NULL, &betStrRect);
	SDL_RenderCopy(renderer, betTexture, NULL, &betRect);
	SDL_RenderCopy(renderer, hitBtnTexture, NULL, &hitBtnRect);
	SDL_RenderCopy(renderer, stayBtnTexture, NULL, &stayBtnRect);

	SDL_RenderPresent(renderer);
}

/// Handle user events
void Game::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		int msx, msy;

		switch (event.type) {
		case SDL_QUIT: running = false; break;/*!< Quit if X is clicked */
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

	/// Check if Hit button is pressed
	if ((xDown > hitBtnX && xDown < (hitBtnX + hitBtnW)) && (xUp > hitBtnX && xUp < (hitBtnX + hitBtnW)) &&
		(yDown > hitBtnY && yDown < (hitBtnY + hitBtnH)) && (yUp > hitBtnY && yUp < (hitBtnY + hitBtnH))) {
		//player->increaseCards();
		std::cout << "HIT button is clicked" << std::endl;

		return;
	}

	/// Stay button coordinates and size
	int stayBtnX = 10;
	int stayBtnY = wh / 2 + 175;
	int stayBtnW = 100;
	int stayBtnH = 40;

	/// Check if Stay button is pressed
	if ((xDown > stayBtnX && xDown < (stayBtnX + stayBtnW)) && (xUp > stayBtnX && xUp < (stayBtnX + stayBtnW)) &&
		(yDown > stayBtnY && yDown < (stayBtnY + stayBtnH)) && (yUp > stayBtnY && yUp < (stayBtnY + stayBtnH))) {
		std::cout << "STAY button is clicked" << std::endl;

		return;
	}
}
