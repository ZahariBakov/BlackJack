#pragma once

#include "Card.h"

#include <vector>

class CardDeck {
public:
	CardDeck(SDL_Renderer* renderer);

	auto DealCard() -> Card;
	void Shuffle();

	std::vector<Card> m_deckOfCards;

private:
	int m_currentCard;
};
