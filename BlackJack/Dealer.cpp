#include "Dealer.h"

Dealer::Dealer(CardDeck* deck) {
	dealerCards = new Card[11];
	dealerCards[0] = deck->dealCard();
	dealerCards[1] = deck->dealCard();

	numberOfCards = 2;
	this->score = dealerCards[0].getPoint();

	std::cout << "Dealer is created" << std::endl;
}

Dealer::~Dealer() {
	delete[] dealerCards;
}

//void Dealer::increaseScore(int points) {
//	this->score += points;
//
//	std::cout << "Dealer score is: " << score << " after increase with " << points << std::endl;
//}
//
//void Dealer::addCard(CardDeck& deck) {
//	dealerCards[numberOfCards] = deck.dealCard();
//	this->score += dealerCards[numberOfCards].getPoint();
//	numberOfCards++;
//	std::cout << "Dealer add new card" << std::endl;
//}
