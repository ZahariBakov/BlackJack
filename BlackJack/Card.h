#pragma once

#include <string>

#include "TextureManager.h"

class Card 
{
public:
	Card();
	Card(SDL_Renderer* renderer, int suit, int rank);

	auto GetCardSuit() const -> int;

	auto GetCardRank() const -> int;

	auto GetPoint() const -> int;

	void SetPosition(int x, int y);

	auto GetId() const -> std::string;

	void Render() const;
	void SetRenderer(SDL_Renderer* renderer);
	
private:
	auto ToStringSuit() const->std::string;
	auto ToStringRank(int rank) const->std::string;

	int m_suit;
	int m_rank;
	int m_x;
	int m_y;

	std::string m_id;

	SDL_Renderer* m_renderer;
};
