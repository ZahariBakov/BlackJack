#pragma once

#include "Card.h"

#include <vector>

class CardDeck 
{
public:
	CardDeck(SDL_Renderer* renderer);

	auto DealCard() -> Card;
	void Shuffle();

private:
	int m_currentCard;

	std::vector<Card> m_deckOfCards;
};
