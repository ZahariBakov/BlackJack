#pragma once

#include <iostream>

#include "CardDeck.h"

class Dealer {
public:
	Dealer(CardDeck& deck);
	~Dealer();

	int getScore() const;

	void increaseScore(int points);

	Card* dealerCards;

	int numberOfCards;
	
private:
	int _score;
};
