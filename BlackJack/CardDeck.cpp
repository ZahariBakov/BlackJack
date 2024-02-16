#include "CardDeck.h"

#include <iostream>

CardDeck::CardDeck() {
	int idx = 0;
	this->_currentCard = 0;

	for (int cardSuit = 1; cardSuit < 5; ++cardSuit) {
		for (int cardRank = 2; cardRank < 15; ++cardRank) {
			this->_allCards[idx] = Card(cardSuit, cardRank);
			++idx;
		}
	}

	std::cout << "Deck is created" << std::endl;
}

/// Return current card
Card CardDeck::dealCard() {
	/// If current card is last shuffle deck and set current card to 0
	if (this->_currentCard == 52) {
		this->shuffle();
		this->_currentCard = 0;
	}

	Card dealCard = _allCards[_currentCard];
	_currentCard++;

	std::cout << "Deal card " << dealCard.getCardSuit() << " " << dealCard.getCardRank() << std::endl;

	return dealCard;
}

void CardDeck::shuffle() {
	for (int i = 0; i < 200; ++i) {
		int j = rand() % 52;
		int y = rand() % 52;

		Card tempCard = this->_allCards[j];
		this->_allCards[j] = this->_allCards[y];
		this->_allCards[y] = tempCard;
	}

	std::cout << "Deck is shuffle" << std::endl;
}
