#include "CardDeck.h"

#include <iostream>

CardDeck::CardDeck(SDL_Renderer* renderer) {
	this->m_currentCard = 0;

	for (int cardSuit = 1; cardSuit < 5; ++cardSuit) {
		for (int cardRank = 2; cardRank < 15; ++cardRank) {
			m_deckOfCards.push_back(Card(renderer, cardSuit, cardRank));
		}
	}

	std::cout << "Deck is created! " << m_deckOfCards.size() << std::endl;
}

Card CardDeck::DealCard() {
	if (this->m_currentCard == 52) {
		this->Shuffle();
		this->m_currentCard = 0;
	}

	Card dealCard = m_deckOfCards[m_currentCard];
	m_currentCard++;

	std::cout << "Deal card " << dealCard.GetCardRank() << " " << dealCard.GetCardSuit() << std::endl;

	return dealCard;
}

void CardDeck::Shuffle() {
	for (int i = 0; i < 200; ++i) {
		int j = rand() % 52;
		int y = rand() % 52;

		Card tempCard = m_deckOfCards[j];
		m_deckOfCards[j] = m_deckOfCards[y];
		m_deckOfCards[y] = tempCard;
	}

	std::cout << "Deck is shuffle" << std::endl;
}
