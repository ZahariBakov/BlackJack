#include "Dealer.h"

Dealer::Dealer(CardDeck& deck) {
	dealerCards = new Card[11];
	dealerCards[0] = deck.dealCard();
	dealerCards[1] = deck.dealCard();

	numberOfCards = 2;
	this->_score = dealerCards[0].getPoint();

	std::cout << "Dealer is created" << std::endl;
}

Dealer::~Dealer() {
	delete[] dealerCards;
}

int Dealer::getScore() const {
	return this->_score;
}

void Dealer::increaseScore(int points) {
	this->_score += points;

	std::cout << "Dealer score is: " << _score << " after increase with " << points << std::endl;
}
