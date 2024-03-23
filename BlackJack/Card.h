#pragma once

#include <string>

#include "TextureManager.h"

class Card {
public:
	Card();
	Card(SDL_Renderer* renderer, int suit, int rank);

	auto GetCardSuit() const -> int;
	auto GetCardRank() const -> int;
	auto GetPoint() const -> int;

	void SetPosition(int x, int y);
	void Render() const;
	void SetRenderer(SDL_Renderer* renderer);

	std::string id;
	
private:
	int m_suit;
	int m_rank;
	int m_x;
	int m_y;

	auto ToStringSuit() const -> std::string;
	auto ToStringRank(int rank) const -> std::string;

	SDL_Renderer* _renderer;
};
