#include "Game.h"

#include <iostream>

Game::~Game() 
{
	//delete m_window;
	//delete m_renderer;
}

bool Game::Init(const char* title, int xpos, int ypos, int flags) 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		std::cout << "SDL init success!\n";

		m_window = SDL_CreateWindow(title, xpos, ypos, GetWindowsWidth(), GetWindowsHeight(), flags);
		if (m_window != 0) 
		{
			std::cout << "Window creation success!\n";

			m_renderer = SDL_CreateRenderer(m_window, -1, 0);

			if (m_renderer != 0) 
			{
				std::cout << "Renderer creation success!\n";

				m_mainDeck = new CardDeck(m_renderer);
				m_mainDeck->Shuffle();

				m_player = new Player(m_mainDeck);
				m_dealer = new Dealer(m_mainDeck);
				
				TextureManager::Instance()->LoadTexture("assets/table-background.jpg", "background", m_renderer);
				TextureManager::Instance()->LoadTexture("assets/cards/cardBack_blue3.png", "card-back", m_renderer);

				TtfInit();
			}
			else 
			{
				std::cout << "Renderer init failed!\n";
				return false;
			}
		}
		else 
		{
			std::cout << "Window init failed!\n";
			return false;
		}
	}
	else 
	{
		std::cout << "SDL init fail!\n";
		return false;
	}
	std::cout << "Init success!\n";
	m_running = true;

	return true;
}

bool Game::TtfInit() 
{
	if (TTF_Init() == -1)
	{
		return false;
	}

	TTF_Font* font1 = TTF_OpenFont("fonts/Arcade.ttf", 24);
	TTF_Font* font2 = TTF_OpenFont("fonts/COLONNA.ttf", 20);
	TTF_Font* font3 = TTF_OpenFont("fonts/arial.ttf", 24);

	if (font1 == nullptr || font2 == nullptr || font3 == nullptr)
	{
		std::cout << "Font 1 or Font 2 or Font3 is nullptr" << std::endl;
		return false;
	}

	SDL_Surface* tempSurfaceText = nullptr;

	tempSurfaceText = TTF_RenderText_Blended(font1, "DEALER :", { 0, 0, 0, 255 });
	m_dealerTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font1, "PLAYER :", { 0, 0, 0, 255 });
	m_playerTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "Money: $", { 255, 255, 255, 255 });
	m_moneyTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "Score: ", { 255, 255, 255, 255 });
	m_scoreTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);
	m_dealerScoreTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "Current Bet: $", { 255, 255, 255, 255 });
	m_betTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "100", { 255, 255, 255, 255 });
	m_minBetTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font2, "1000", { 255, 255, 255, 255 });
	m_maxBetTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "HIT", { 255, 255, 255, 255 });
	m_hitBtnTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "STAY", { 255, 255, 255, 255 });
	m_stayBtnTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "BET 100", { 255, 255, 255, 255 });
	m_minBetBtnTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "BET 1000", { 255, 255, 255, 255 });
	m_maxBetBtnTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "QUIT", { 255, 255, 255, 255 });
	m_quitBtnTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	tempSurfaceText = TTF_RenderText_Blended(font3, "OK", { 255, 255, 255, 255 });
	m_okBtnTexture = SDL_CreateTextureFromSurface(m_renderer, tempSurfaceText);

	int tw, th;

	SDL_QueryTexture(m_dealerTexture, 0, 0, &tw, &th);
	m_dealerRect = { 10, 10, tw, th };

	SDL_QueryTexture(m_playerTexture, 0, 0, &tw, &th);
	m_playerRect = { 10, GetWindowsHeight() / 2 + 10, tw, th };

	SDL_QueryTexture(m_moneyTexture, 0, 0, &tw, &th);
	m_moneyRect = { 10, GetWindowsHeight() / 2 + 30, tw, th };

	SDL_QueryTexture(m_scoreTexture, 0, 0, &tw, &th);
	m_scoreRect = { 10, GetWindowsHeight() / 2 + 50, tw, th };

	SDL_QueryTexture(m_dealerScoreTexture, 0, 0, &tw, &th);
	m_dealerScoreRect = { 10, 30, tw, th };	

	SDL_QueryTexture(m_betTexture, 0, 0, &tw, &th);
	m_betRect = { 10, GetWindowsHeight() / 2 + 70, tw, th };

	SDL_QueryTexture(m_minBetTexture, 0, 0, &tw, &th);
	m_minBetRect = { 125, GetWindowsHeight() / 2 + 70, tw, th };

	SDL_QueryTexture(m_maxBetTexture, 0, 0, &tw, &th);
	m_maxBetRect = { 125, GetWindowsHeight() / 2 + 70, tw, th };

	SDL_QueryTexture(m_hitBtnTexture, 0, 0, &tw, &th);
	m_hitBtnRect = { 30, GetWindowsHeight() / 2 + 120, tw, th };

	SDL_QueryTexture(m_stayBtnTexture, 0, 0, &tw, &th);
	m_stayBtnRect = { 30, GetWindowsHeight() / 2 + 175, tw, th };

	SDL_QueryTexture(m_minBetBtnTexture, 0, 0, &tw, &th);
	m_minBetBtnRect = { 30, GetWindowsHeight() / 2 + 230, tw, th };

	SDL_QueryTexture(m_maxBetBtnTexture, 0, 0, &tw, &th);
	m_maxBetBtnRect = { 170, GetWindowsHeight() / 2 + 230, tw, th };

	SDL_QueryTexture(m_quitBtnTexture, 0, 0, &tw, &th);
	m_quitBtnRect = { GetWindowsWidth() - 80, GetWindowsHeight() / 2 + 230, tw, th};

	SDL_QueryTexture(m_okBtnTexture, 0, 0, &tw, &th);
	m_okBtnRect = { GetWindowsWidth() - 150, GetWindowsHeight() / 2 + 230, tw, th};

	SDL_FreeSurface(tempSurfaceText);
	TTF_CloseFont(font1);
	TTF_CloseFont(font2);
	TTF_CloseFont(font3);

	return true;
}

void Game::HandleEvents() 
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) 
	{
		int msx, msy;

		switch (event.type) 
		{
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_MOUSEBUTTONDOWN: 
			{
			if (event.button.button == SDL_BUTTON_LEFT) 
			{
				SDL_GetMouseState(&msx, &msy);
				m_mouseDownX = msx;
				m_mouseDownY = msy;
			}
		}; break;
		case SDL_MOUSEBUTTONUP: 
			{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&msx, &msy);
				ClickedBtn(m_mouseDownX, m_mouseDownY, msx, msy);
			}
		}

		default: break;
		}
	}
}

void Game::Render() 
{
	SDL_RenderClear(m_renderer);

	SDL_Surface* tempSurfaceText = nullptr;

	TTF_Font* font2 = TTF_OpenFont("fonts/COLONNA.ttf", 20);

	TextureManager::Instance()->DrawTexture("background", 0, 0, GetWindowsWidth(), GetWindowsHeight(), m_renderer);

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(m_renderer, 0, GetWindowsHeight() / 2, GetWindowsWidth(), GetWindowsHeight() / 2);

	TextureManager::Instance()->DrawRecnatgle(m_renderer, 10, GetWindowsHeight() / 2 + 115, 80, 40);
	TextureManager::Instance()->DrawRecnatgle(m_renderer, 10, GetWindowsHeight() / 2 + 170, 100, 40);
	TextureManager::Instance()->DrawRecnatgle(m_renderer, 10, GetWindowsHeight() / 2 + 225, 130, 40);
	TextureManager::Instance()->DrawRecnatgle(m_renderer, 160, GetWindowsHeight() / 2 + 225, 130, 40);

	if (!m_isRound) 
	{
		TextureManager::Instance()->DrawRecnatgle(m_renderer, GetWindowsWidth() - 90, GetWindowsHeight() / 2 + 225, 80, 40);
		TextureManager::Instance()->DrawRecnatgle(m_renderer, GetWindowsWidth() - 155, GetWindowsHeight() / 2 + 225, 50, 40);
	}
	
	SDL_RenderCopy(m_renderer, m_dealerTexture, nullptr, &m_dealerRect);
	SDL_RenderCopy(m_renderer, m_playerTexture, nullptr, &m_playerRect);
	SDL_RenderCopy(m_renderer, m_moneyTexture, nullptr, &m_moneyRect);
	SDL_RenderCopy(m_renderer, m_scoreTexture, nullptr, &m_scoreRect);
	SDL_RenderCopy(m_renderer, m_dealerScoreTexture, nullptr, &m_dealerScoreRect);
	SDL_RenderCopy(m_renderer, m_betTexture, nullptr, &m_betRect);
	SDL_RenderCopy(m_renderer, m_hitBtnTexture, nullptr, &m_hitBtnRect);
	SDL_RenderCopy(m_renderer, m_stayBtnTexture, nullptr, &m_stayBtnRect);
	SDL_RenderCopy(m_renderer, m_minBetBtnTexture, nullptr, &m_minBetBtnRect);
	SDL_RenderCopy(m_renderer, m_maxBetBtnTexture, nullptr, &m_maxBetBtnRect);

	if (m_betFlag == 1)
	{
		SDL_RenderCopy(m_renderer, m_minBetTexture, nullptr, &m_minBetRect);
	} 

	if (m_betFlag == 2) 
	{
		SDL_RenderCopy(m_renderer, m_maxBetTexture, nullptr, &m_maxBetRect);
	}
	
	if (!m_isRound) 
	{
		SDL_RenderCopy(m_renderer, m_quitBtnTexture, nullptr, &m_quitBtnRect);
		SDL_RenderCopy(m_renderer, m_okBtnTexture, nullptr, &m_okBtnRect);
	}

	int x = 180;

	if (!m_isStay)
	{
		TextureManager::Instance()->DrawTexture(m_dealer->GetCurrentCard(0).GetId(), x, 30, 140, 190, m_renderer);
		TextureManager::Instance()->DrawTexture("card-back", 210, 30, 140, 190, m_renderer);
	}
	else 
	{
		TextureManager::Instance()->DrawTexture(m_dealer->GetCurrentCard(0).GetId(), x, 30, 140, 190, m_renderer);
		TextureManager::Instance()->DrawTexture(m_dealer->GetCurrentCard(1).GetId(), x + 30, 30, 140, 190, m_renderer);
	}

	for (int i = 0; i < m_player->GetNumberOfCards(); ++i) 
	{
		x = x + 30 * i;
		TextureManager::Instance()->DrawTexture(m_player->GetCurrentCard(i).GetId(), x, GetWindowsHeight() - 250, 140, 190, m_renderer);
	}

	SDL_RenderPresent(m_renderer);

	SDL_FreeSurface(tempSurfaceText);
	TTF_CloseFont(font2);
}

void Game::Update() {}

void Game::Clean() 
{
	std::cout << "Cleaning game!\n";
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

bool Game::IsRunning() const 
{
	return m_running;
}

void Game::ClickedBtn( int xDown, int yDown, int xUp, int yUp) 
{

	int hitBtnX = 10;
	int hitBtnY = GetWindowsHeight() / 2 + 115;
	int hitBtnW = 80;
	int hitBtnH = 40;

	if ((xDown > hitBtnX && xDown < (hitBtnX + hitBtnW)) && (xUp > hitBtnX && xUp < (hitBtnX + hitBtnW)) &&
		(yDown > hitBtnY && yDown < (hitBtnY + hitBtnH)) && (yUp > hitBtnY && yUp < (hitBtnY + hitBtnH)))
	{
		std::cout << "HIT button is clicked" << std::endl;

		return;
	}

	int stayBtnX = 10;
	int stayBtnY = GetWindowsHeight() / 2 + 175;
	int stayBtnW = 100;
	int stayBtnH = 40;

	if ((xDown > stayBtnX && xDown < (stayBtnX + stayBtnW)) && (xUp > stayBtnX && xUp < (stayBtnX + stayBtnW)) &&
		(yDown > stayBtnY && yDown < (stayBtnY + stayBtnH)) && (yUp > stayBtnY && yUp < (stayBtnY + stayBtnH))) 
	{
		m_isStay = true;

		std::cout << "STAY button is clicked" << std::endl;

		return;
	}

	int minBetBtnX = 10;
	int minBetBtnY = GetWindowsHeight() / 2 + 225;
	int minBetBtnW = 130; 
	int minBetBtnH = 40;

	if ((xDown > minBetBtnX && xDown < (minBetBtnX + minBetBtnW)) && (xUp > minBetBtnX && xUp < (minBetBtnX + minBetBtnW)) &&
		(yDown > minBetBtnY && yDown < (minBetBtnY + minBetBtnH)) && (yUp > minBetBtnY && yUp < (minBetBtnY + minBetBtnH))) 
	{
		std::cout << "min BET button is clicked" << std::endl;

		return;
	}

	int maxBetBtnX = 160;
	int maxBetBtnY = GetWindowsHeight() / 2 + 225;
	int maxBetBtnW = 130;
	int maxBetBtnH = 40;

	if ((xDown > maxBetBtnX && xDown < (maxBetBtnX + maxBetBtnW)) && (xUp > maxBetBtnX && xUp < (maxBetBtnX + maxBetBtnW)) &&
		(yDown > maxBetBtnY && yDown < (maxBetBtnY + maxBetBtnH)) && (yUp > maxBetBtnY && yUp < (maxBetBtnY + maxBetBtnH))) 
	{
		std::cout << "max BET button is clicked" << std::endl;

		return;
	}

	int quitBetBtnX = GetWindowsWidth() - 90;
	int quitBetBtnY = GetWindowsHeight() / 2 + 225;
	int quitBetBtnW = 80;
	int quitBetBtnH = 40;

	if ((xDown > quitBetBtnX && xDown < (quitBetBtnX + quitBetBtnW)) && (xUp > quitBetBtnX && xUp < (quitBetBtnX + quitBetBtnW)) &&
		(yDown > quitBetBtnY && yDown < (quitBetBtnY + quitBetBtnH)) && (yUp > quitBetBtnY && yUp < (quitBetBtnY + quitBetBtnH))) 
	{
		std::cout << "QUIT button is clicked" << std::endl;
		m_running = false;

		return;
	}

	int okBetBtnX = GetWindowsWidth() - 155;
	int okBetBtnY = GetWindowsHeight() / 2 + 225;
	int okBetBtnW = 50;
	int okBetBtnH = 40;

	if ((xDown > okBetBtnX && xDown < (okBetBtnX + okBetBtnW)) && (xUp > okBetBtnX && xUp < (okBetBtnX + okBetBtnW)) &&
		(yDown > okBetBtnY && yDown < (okBetBtnY + okBetBtnH)) && (yUp > okBetBtnY && yUp < (okBetBtnY + okBetBtnH))) 
	{
		std::cout << "OK button is clicked" << std::endl;

		return;
	}
}
