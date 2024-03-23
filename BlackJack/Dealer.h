#pragma once

#include <iostream>

#include "CardDeck.h"

class Dealer {
public:
	Dealer(CardDeck* deck);
	~Dealer();

	//void increaseScore(int points);
	//void addCard(CardDeck& deck);

	Card* m_dealerCards;

	int m_numberOfCards;
	int m_score;
private:

};
