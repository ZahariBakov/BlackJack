#include "Card.h"
#include <iostream>

int width  = 140;
int height = 190;

Card::Card() 
{
	_renderer = nullptr;
	_suit = 0; 
	_rank = 0;
	_x = 0;  
	_y = 0;
}

Card::Card(SDL_Renderer* renderer, int suit, int rank) 
{
	_renderer = renderer;
	_suit = suit;
	_rank = rank;
	_x = 0;
	_y = 0;
	std::string path = toStringSuit();
	id = std::to_string(suit) + std::to_string(rank);

	TextureManager::Instance()->loadTexture(path.c_str(), id, _renderer);
}

int Card::getCardSuit() const 
{
	return this->_suit;
}

int Card::getCardRank() const 
{
	return this->_rank;
}

int Card::getPoint() const 
{
	if (getCardRank() > 10) {
		if (getCardRank() == 14) {
			return 11;
		}
		else {
			return 10;
		}
	}
	else {
		return getCardRank();
	}
}

void Card::setPosition(int x, int y)
{
	_x = x;
	_y = y;
}

void Card::render() const 
{
	TextureManager::Instance()->drawTexture(id, _x, _y, width, height, _renderer);
}

void Card::setRenderer(SDL_Renderer* renderer)
{
	_renderer = renderer;
}

std::string Card::toStringSuit() const 
{
	std::string suit;

	switch (getCardSuit()) {
	case 1:
		suit = "cardDiamonds";
		break;
	case 2:
		suit = "cardClubs";
		break;
	case 3:
		suit = "cardHearts";
		break;
	case 4:
		suit = "cardSpades";
		break;

	default:
		break;
	}

	std::string result = "assets/cards/" + suit + this->toStringRank(getCardRank()) + ".png";

	return result;
}

std::string Card::toStringRank(int rank) const 
{
	std::string result;

	if (rank > 10) {
		switch (rank) {
			case 11:
				result = "J";
				break;
			case 12:
				result = "Q";
				break;
			case 13:
				result = "K";
				break;
			case 14:
				result = "A";
				break;
			default:
				break;
		}
	}
	else {
		result = std::to_string(rank);
	}

	return result;
}
