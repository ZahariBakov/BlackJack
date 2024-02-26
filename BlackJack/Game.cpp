#include "Game.h"

#include <string>

std::string thirdCardName;

//Player* player;
//Dealer* dealer;
CardDeck* mainDeck;

Game::Game() {
	Game::window   = NULL;
	Game::renderer = NULL;

	Game::running = true;
	Game::isStay  = false;
	Game::isRound = false;

	Game::isBet = 0;

	Game::dealerTexture         = NULL;
	Game::playerTexture         = NULL;
	Game::scoreTexture          = NULL;
	Game::scoreStrTexture       = NULL;
	Game::moneyTexture          = NULL;
	Game::moneyStrTexture       = NULL;
	Game::minBetTexture         = NULL;
	Game::maxBetTexture         = NULL;
	Game::betStrTexture         = NULL;
	Game::hitBtnTexture         = NULL;
	Game::stayBtnTexture        = NULL;
	Game::dealerScoreTexture    = NULL;
	Game::dealerScoreStrTexture = NULL;
	Game::minBetBtnTexture      = NULL;
	Game::maxBetBtnTexture      = NULL;
	Game::quitBtnTexture        = NULL;
	Game::okBtnTexture          = NULL;

	Game::dealerRect         = { 0, 0, 0, 0 };
	Game::playerRect         = { 0, 0, 0, 0 };
	Game::scoreRect			 = { 0, 0, 0, 0 };
	Game::scoreStrRect		 = { 0, 0, 0, 0 };
	Game::moneyRect		     = { 0, 0, 0, 0 };
	Game::moneyStrRect	     = { 0, 0, 0, 0 };
	Game::minBetRect		 = { 0, 0, 0, 0 };
	Game::maxBetRect		 = { 0, 0, 0, 0 };
	Game::betStrRect		 = { 0, 0, 0, 0 }; 
	Game::hitBtnRect		 = { 0, 0, 0, 0 };
	Game::stayBtnRect		 = { 0, 0, 0, 0 };
	Game::dealerScoreRect    = { 0, 0, 0, 0 };
	Game::dealerScoreStrRect = { 0, 0, 0, 0 };
	Game::minBetBtnRect		 = { 0, 0, 0, 0 };
	Game::maxBetBtnRect		 = { 0, 0, 0, 0 };
	Game::quitBtnRect		 = { 0, 0, 0, 0 };
	Game::okBtnRect			 = { 0, 0, 0, 0 };

	Game::mouseDownX = Game::mouseDownY = 0;
}


Game::~Game() {
	delete window;
	delete renderer;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success!\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);/*!< */
		if (window != 0) {
			std::cout << "Window creation success!\n";

			renderer = SDL_CreateRenderer(window, -1, 0);

			if (renderer != 0) {
				std::cout << "Renderer creation success!\n";

				mainDeck = new CardDeck(renderer);
				//mainDeck->shuffle();

				/*player = new Player(*mainDeck);
				dealer = new Dealer(*mainDeck);*/
				
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

bool Game::ttf_init() {
	if (TTF_Init() == -1) {
		return false;
	}

	TTF_Font* font1 = TTF_OpenFont("fonts/Arcade.ttf", 24);
	TTF_Font* font2 = TTF_OpenFont("fonts/COLONNA.ttf", 20);
	TTF_Font* font3 = TTF_OpenFont("fonts/arial.ttf", 24);

	if (font1 == NULL || font2 == NULL || font3 == NULL) {
		std::cout << "Font 1 or Font 2 or Font3 is NULL" << std::endl;
		return false;
	}

	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);

	SDL_Surface* tempSurfaceText = NULL;

	tempSurfaceText = TTF_RenderText_Blended(font1, "DEALER :", { 0, 0, 0, 255 });
	dealerTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font1, "PLAYER :", { 0, 0, 0, 255 });
	playerTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "Money: $", { 255, 255, 255, 255 });
	moneyStrTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "Score: ", { 255, 255, 255, 255 });
	scoreStrTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	dealerScoreStrTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "Current Bet: $", { 255, 255, 255, 255 });
	betStrTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "100", { 255, 255, 255, 255 });
	minBetTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "1000", { 255, 255, 255, 255 });
	maxBetTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	/// Buttons
	tempSurfaceText = TTF_RenderText_Blended(font3, "HIT", { 255, 255, 255, 255 });
	hitBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "STAY", { 255, 255, 255, 255 });
	stayBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "BET 100", { 255, 255, 255, 255 });
	minBetBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "BET 1000", { 255, 255, 255, 255 });
	maxBetBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "QUIT", { 255, 255, 255, 255 });
	quitBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "OK", { 255, 255, 255, 255 });
	okBtnTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	int tw, th;

	SDL_QueryTexture(dealerTexture, 0, 0, &tw, &th);
	dealerRect = { 10, 10, tw, th };

	SDL_QueryTexture(playerTexture, 0, 0, &tw, &th);
	playerRect = { 10, wh / 2 + 10, tw, th };

	SDL_QueryTexture(moneyStrTexture, 0, 0, &tw, &th);
	moneyStrRect = { 10, wh / 2 + 30, tw, th };

	SDL_QueryTexture(scoreStrTexture, 0, 0, &tw, &th);
	scoreStrRect = { 10, wh / 2 + 50, tw, th };

	SDL_QueryTexture(dealerScoreStrTexture, 0, 0, &tw, &th);
	dealerScoreStrRect = { 10, 30, tw, th };	

	SDL_QueryTexture(betStrTexture, 0, 0, &tw, &th);
	betStrRect = { 10, wh / 2 + 70, tw, th };

	SDL_QueryTexture(minBetTexture, 0, 0, &tw, &th);
	minBetRect = { 125, wh / 2 + 70, tw, th };

	SDL_QueryTexture(maxBetTexture, 0, 0, &tw, &th);
	maxBetRect = { 125, wh / 2 + 70, tw, th };

	SDL_QueryTexture(hitBtnTexture, 0, 0, &tw, &th);
	hitBtnRect = { 30, wh / 2 + 120, tw, th };

	SDL_QueryTexture(stayBtnTexture, 0, 0, &tw, &th);
	stayBtnRect = { 30, wh / 2 + 175, tw, th };

	SDL_QueryTexture(minBetBtnTexture, 0, 0, &tw, &th);
	minBetBtnRect = { 30, wh / 2 + 230, tw, th };

	SDL_QueryTexture(maxBetBtnTexture, 0, 0, &tw, &th);
	maxBetBtnRect = { 170, wh / 2 + 230, tw, th };

	SDL_QueryTexture(quitBtnTexture, 0, 0, &tw, &th);
	quitBtnRect = { ww - 80, wh / 2 + 230, tw, th };

	SDL_QueryTexture(okBtnTexture, 0, 0, &tw, &th);
	okBtnRect = { ww - 150, wh / 2 + 230, tw, th };

	SDL_FreeSurface(tempSurfaceText);
	TTF_CloseFont(font1);
	TTF_CloseFont(font2);
	TTF_CloseFont(font3);

	return true;
}

void Game::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		int msx, msy;

		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_MOUSEBUTTONDOWN: {
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&msx, &msy);
				Game::mouseDownX = msx;
				Game::mouseDownY = msy;
			}
		}; break;
		case SDL_MOUSEBUTTONUP: {
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&msx, &msy);
				Game::clickedBtn(mouseDownX, mouseDownY, msx, msy);
			}
		}

		default: break;
		}
	}
}

void Game::render() {
	//SDL_SetRenderDrawColor(renderer, 0, 153, 0, 255); // base table color
	SDL_RenderClear(renderer);

	SDL_Surface* tempSurfaceText = NULL;
	TTF_Font* font2 = TTF_OpenFont("fonts/COLONNA.ttf", 20);

	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);

	TextureManager::Instance()->drawTexture("background", 0, 0, ww, wh, renderer);

	//if (Game::isBet > 0) {
	//	int x = 180;
	//	int y = 10;
	//	std::string cardName = "p";
	//	std::string dealerCardName = "d";

	//	for (int i = 0; i < player->numberOfCards; ++i) {
	//		if (i > 0) {
	//			x = 180 + (i * 30);
	//		}
	//		cardName += std::to_string(i);

	//		TextureManager::Instance()->loadTexture(player->playerCards[i].toStringSuit().c_str(), cardName, renderer);
	//		TextureManager::Instance()->drawTexture(cardName, x, wh / 2 + 20, 140, 190, renderer);
	//	}

	//	TextureManager::Instance()->loadTexture(dealer->dealerCards[0].toStringSuit().c_str(), "firstdealerCard", renderer);
	//	TextureManager::Instance()->drawTexture("firstdealerCard", 180, y, 140, 190, renderer);

	//	if (Game::isStay) {
	//		TextureManager::Instance()->loadTexture(dealer->dealerCards[1].toStringSuit().c_str(), "seconddealerCard", renderer);
	//		TextureManager::Instance()->drawTexture("seconddealerCard", 180 + 30, y, 140, 190, renderer);
	//		std::cout << "now must wait" << std::endl;
	//		SDL_Delay(500);

	//		if (Game::isStay && dealer->score < player->getScore()) {
	//			dealer->addCard(*mainDeck);
	//		}

	//		for (int i = 2; i < dealer->numberOfCards; ++i) {
	//			SDL_Delay(500);

	//			x = 180 + (i * 30);

	//			dealerCardName += std::to_string(i);

	//			TextureManager::Instance()->loadTexture(dealer->dealerCards[i].toStringSuit().c_str(), dealerCardName, renderer);
	//			TextureManager::Instance()->drawTexture(dealerCardName, x, y, 140, 190, renderer);				
	//		}
	//	}
	//	else {
	//		TextureManager::Instance()->drawTexture("card-back", 210, 10, 140, 190, renderer);
	//	}
	//}

	//std::string t = std::to_string(player->getMoney());
	//char const* playerMoneyToString = t.c_str();

	//tempSurfaceText = TTF_RenderText_Blended(font2, playerMoneyToString, { 255, 255, 255, 255 });
	//moneyTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	//if (Game::isBet > 0) {
	//	/// Get the player's score and convert the value to a string.
	//	std::string t = std::to_string(player->getScore());
	//	char const* scoreStr = t.c_str();

	//	tempSurfaceText = TTF_RenderText_Blended(font2, scoreStr, { 255, 255, 255, 255 });
	//	scoreTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	//	/// Get the dealer's score and convert to a string
	//	t = std::to_string(dealer->score);
	//	char const* dealerScoreStr = t.c_str();

	//	tempSurfaceText = TTF_RenderText_Blended(font2, dealerScoreStr, { 255, 255, 255, 255 });
	//	dealerScoreTexture = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);
	//}
	//int tw, th;
	//// Money value
	//SDL_QueryTexture(moneyTexture, 0, 0, &tw, &th);
	//moneyRect = { 85, wh / 2 + 30, tw, th };

	//SDL_QueryTexture(scoreTexture, 0, 0, &tw, &th);
	//scoreRect = { 70, wh / 2 + 50, tw, th };

	//SDL_QueryTexture(dealerScoreTexture, 0, 0, &tw, &th);
	//dealerScoreRect = { 70, 30, tw, th };
	//
	///// Drawing a line in the middle
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//SDL_RenderDrawLine(renderer, 0, wh / 2, ww, wh / 2);

	TextureManager::Instance()->drawRecnatgle(renderer, 10, wh / 2 + 115, 80, 40);
	TextureManager::Instance()->drawRecnatgle(renderer, 10, wh / 2 + 170, 100, 40);
	TextureManager::Instance()->drawRecnatgle(renderer, 10, wh / 2 + 225, 130, 40);
	TextureManager::Instance()->drawRecnatgle(renderer, 160, wh / 2 + 225, 130, 40);
	if (!Game::isRound) {
		TextureManager::Instance()->drawRecnatgle(renderer, ww - 90, wh / 2 + 225, 80, 40);
		TextureManager::Instance()->drawRecnatgle(renderer, ww - 155, wh / 2 + 225, 50, 40);
	}
	
	SDL_RenderCopy(renderer, dealerTexture, NULL, &dealerRect);
	SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);

	SDL_RenderCopy(renderer, scoreStrTexture, NULL, &scoreStrRect);
	SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
	SDL_RenderCopy(renderer, dealerScoreStrTexture, NULL, &dealerScoreStrRect);
	SDL_RenderCopy(renderer, dealerScoreTexture, NULL, &dealerScoreRect);

	SDL_RenderCopy(renderer, moneyStrTexture, NULL, &moneyStrRect);
	SDL_RenderCopy(renderer, moneyTexture, NULL, &moneyRect);
	
	SDL_RenderCopy(renderer, betStrTexture, NULL, &betStrRect);

	//if (Game::isBet == 1) {
	//	SDL_RenderCopy(renderer, minBetTexture, NULL, &minBetRect);
	//}
	//if (Game::isBet == 2) {
	//	SDL_RenderCopy(renderer, maxBetTexture, NULL, &maxBetRect);
	//}
	
	SDL_RenderCopy(renderer, hitBtnTexture, NULL, &hitBtnRect);
	SDL_RenderCopy(renderer, stayBtnTexture, NULL, &stayBtnRect);
	SDL_RenderCopy(renderer, minBetBtnTexture, NULL, &minBetBtnRect);
	SDL_RenderCopy(renderer, maxBetBtnTexture, NULL, &maxBetBtnRect);
	if (!Game::isRound) {
		SDL_RenderCopy(renderer, quitBtnTexture, NULL, &quitBtnRect);
		SDL_RenderCopy(renderer, okBtnTexture, NULL, &okBtnRect);
	}

	SDL_RenderPresent(renderer);

	SDL_FreeSurface(tempSurfaceText);
	TTF_CloseFont(font2);
}

void Game::update() {
	//if (player->getScore() > 21) {
	//	Game::isRound = false;
	//}
}

void Game::clean() {
	std::cout << "Cleaning game!\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::isRunning() const {
	return Game::running;
}

void Game::clickedBtn( int xDown, int yDown, int xUp, int yUp) {
	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);

	int hitBtnX = 10;
	int hitBtnY = wh / 2 + 115;
	int hitBtnW = 80;
	int hitBtnH = 40;

	if ((xDown > hitBtnX && xDown < (hitBtnX + hitBtnW)) && (xUp > hitBtnX && xUp < (hitBtnX + hitBtnW)) &&
		(yDown > hitBtnY && yDown < (hitBtnY + hitBtnH)) && (yUp > hitBtnY && yUp < (hitBtnY + hitBtnH))) {
		std::cout << "HIT button is clicked" << std::endl;
		//if (Game::isBet > 0 && player->numberOfCards < 11 && !Game::isStay) {
		//	player->addCard(*mainDeck);
		//}

		return;
	}

	int stayBtnX = 10;
	int stayBtnY = wh / 2 + 175;
	int stayBtnW = 100;
	int stayBtnH = 40;

	if ((xDown > stayBtnX && xDown < (stayBtnX + stayBtnW)) && (xUp > stayBtnX && xUp < (stayBtnX + stayBtnW)) &&
		(yDown > stayBtnY && yDown < (stayBtnY + stayBtnH)) && (yUp > stayBtnY && yUp < (stayBtnY + stayBtnH))) {
		std::cout << "STAY button is clicked" << std::endl;
		//if (Game::isBet > 0 && !Game::isStay) {
		//	Game::isStay = true;

		//	dealer->score += dealer->dealerCards[1].getPoint();
		//}

		return;
	}

	int minBetBtnX = 10;
	int minBetBtnY = wh / 2 + 225;
	int minBetBtnW = 130; 
	int minBetBtnH = 40;

	if ((xDown > minBetBtnX && xDown < (minBetBtnX + minBetBtnW)) && (xUp > minBetBtnX && xUp < (minBetBtnX + minBetBtnW)) &&
		(yDown > minBetBtnY && yDown < (minBetBtnY + minBetBtnH)) && (yUp > minBetBtnY && yUp < (minBetBtnY + minBetBtnH))) {
		std::cout << "min BET button is clicked" << std::endl;
		//if (Game::isBet == 0) {
		//	Game::isBet = 1;
		//	Game::isRound = true;
		//	player->setBet(false);
		//}

		return;
	}

	int maxBetBtnX = 160;
	int maxBetBtnY = wh / 2 + 225;
	int maxBetBtnW = 130;
	int maxBetBtnH = 40;

	if ((xDown > maxBetBtnX && xDown < (maxBetBtnX + maxBetBtnW)) && (xUp > maxBetBtnX && xUp < (maxBetBtnX + maxBetBtnW)) &&
		(yDown > maxBetBtnY && yDown < (maxBetBtnY + maxBetBtnH)) && (yUp > maxBetBtnY && yUp < (maxBetBtnY + maxBetBtnH))) {
		std::cout << "max BET button is clicked" << std::endl;
		//if (Game::isBet == 0) {
		//	Game::isBet = 2;
		//	Game::isRound = true;
		//	player->setBet(true);
		//}

		return;
	}

	int quitBetBtnX = ww - 90;
	int quitBetBtnY = wh / 2 + 225;
	int quitBetBtnW = 80;
	int quitBetBtnH = 40;

	if ((xDown > quitBetBtnX && xDown < (quitBetBtnX + quitBetBtnW)) && (xUp > quitBetBtnX && xUp < (quitBetBtnX + quitBetBtnW)) &&
		(yDown > quitBetBtnY && yDown < (quitBetBtnY + quitBetBtnH)) && (yUp > quitBetBtnY && yUp < (quitBetBtnY + quitBetBtnH))) {
		std::cout << "quit button is clicked" << std::endl;

		return;
	}

	int okBetBtnX = ww - 155;
	int okBetBtnY = wh / 2 + 225;
	int okBetBtnW = 50;
	int okBetBtnH = 40;

	if ((xDown > okBetBtnX && xDown < (okBetBtnX + okBetBtnW)) && (xUp > okBetBtnX && xUp < (okBetBtnX + okBetBtnW)) &&
		(yDown > okBetBtnY && yDown < (okBetBtnY + okBetBtnH)) && (yUp > okBetBtnY && yUp < (okBetBtnY + okBetBtnH))) {
		std::cout << "ok button is clicked" << std::endl;

		return;
	}
}
