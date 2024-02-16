#pragma once

#include "Card.h"

class CardDeck {
public:
	CardDeck();

	Card dealCard();
	void shuffle();

private:
	Card _allCards[52];
	int _currentCard;
};
