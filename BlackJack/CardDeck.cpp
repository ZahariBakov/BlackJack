#include "CardDeck.h"

#include <iostream>

CardDeck::CardDeck(SDL_Renderer* renderer) {
	this->_currentCard = 0;

	for (int cardSuit = 1; cardSuit < 5; ++cardSuit) {
		for (int cardRank = 2; cardRank < 15; ++cardRank) {
			deckOfCards.push_back(Card(renderer, cardSuit, cardRank));
		}
	}

	std::cout << "Deck is created! " << deckOfCards.size() << std::endl;
}

Card CardDeck::dealCard() {
	if (this->_currentCard == 52) {
		this->shuffle();
		this->_currentCard = 0;
	}

	Card dealCard = deckOfCards[_currentCard];
	_currentCard++;

	std::cout << "Deal card " << dealCard.getCardSuit() << " " << dealCard.getCardRank() << std::endl;

	return dealCard;
}

void CardDeck::shuffle() {
	for (int i = 0; i < 200; ++i) {
		int j = rand() % 52;
		int y = rand() % 52;

		Card tempCard = deckOfCards[j];
		deckOfCards[j] = deckOfCards[y];
		deckOfCards[y] = tempCard;
	}

	std::cout << "Deck is shuffle" << std::endl;
}
