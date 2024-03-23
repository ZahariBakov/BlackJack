#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "TextureManager.h"
#include "Player.h"
#include "CardDeck.h"
#include "Dealer.h"
#include "GameConstants.h"

class Game 
{
public:
	Game() {};
	~Game();

	auto Init(const char* title, int xpos, int ypos, int flags) -> bool;

	void Render();
	void HandleEvents();
	void Update();
	void Clean();

	auto IsRunning() const -> bool;
	void ClickedBtn(int xDown, int yDown, int xUp, int yUp);

private:
	auto TtfInit() -> bool;

	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	bool m_running = true;
	bool m_isStay  = false;
	bool m_isRound = false;

	int m_mouseDownX = 0;
	int m_mouseDownY = 0;
	int m_betFlag    = 0;

	Player* m_player = nullptr;
	Dealer* m_dealer = nullptr;
	CardDeck* m_mainDeck = nullptr;

	SDL_Texture* m_dealerTexture      = nullptr;
	SDL_Texture* m_playerTexture      = nullptr;
	SDL_Texture* m_moneyTexture       = nullptr;
	SDL_Texture* m_scoreTexture       = nullptr;
	SDL_Texture* m_dealerScoreTexture = nullptr;
	SDL_Texture* m_betTexture         = nullptr;
	SDL_Texture* m_minBetTexture      = nullptr;
	SDL_Texture* m_maxBetTexture      = nullptr;
	SDL_Texture* m_hitBtnTexture      = nullptr;
	SDL_Texture* m_stayBtnTexture     = nullptr;
	SDL_Texture* m_minBetBtnTexture   = nullptr;
	SDL_Texture* m_maxBetBtnTexture   = nullptr;
	SDL_Texture* m_quitBtnTexture     = nullptr;
	SDL_Texture* m_okBtnTexture       = nullptr;

	SDL_Rect m_dealerRect      = { 0, 0, 0, 0 };
	SDL_Rect m_playerRect      = { 0, 0, 0, 0 };
	SDL_Rect m_moneyRect       = { 0, 0, 0, 0 };
	SDL_Rect m_scoreRect       = { 0, 0, 0, 0 };
	SDL_Rect m_dealerScoreRect = { 0, 0, 0, 0 };
	SDL_Rect m_betRect         = { 0, 0, 0, 0 };
	SDL_Rect m_minBetRect      = { 0, 0, 0, 0 };
	SDL_Rect m_maxBetRect      = { 0, 0, 0, 0 };
	SDL_Rect m_hitBtnRect      = { 0, 0, 0, 0 };
	SDL_Rect m_stayBtnRect     = { 0, 0, 0, 0 };
	SDL_Rect m_minBetBtnRect   = { 0, 0, 0, 0 };
	SDL_Rect m_maxBetBtnRect   = { 0, 0, 0, 0 };
	SDL_Rect m_quitBtnRect     = { 0, 0, 0, 0 };
	SDL_Rect m_okBtnRect       = { 0, 0, 0, 0 };
};
