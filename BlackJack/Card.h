#pragma once

#include <string>

#include "TextureManager.h"

class Card {
public:
	Card();
	Card(SDL_Renderer* renderer, int suit, int rank);

	int getCardSuit() const;
	int getCardRank() const;
	int getPoint() const;

	void setPosition(int x, int y);
	void render() const;
	void setRenderer(SDL_Renderer* renderer);
	
private:
	int _suit;
	int _rank;
	std::string id;
	int _x;
	int _y;

	std::string toStringSuit() const;
	std::string toStringRank(int rank) const;

	SDL_Renderer* _renderer;
};
