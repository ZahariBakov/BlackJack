#pragma once

#include "Card.h"

#include <vector>

class CardDeck {
public:
	CardDeck(SDL_Renderer* renderer);

	//Card dealCard();
	void shuffle();

	std::vector<Card> deckOfCards;

private:
	int _currentCard;
};
