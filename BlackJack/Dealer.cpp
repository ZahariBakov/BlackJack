#include "Dealer.h"

Dealer::Dealer(CardDeck* deck) 
{
	m_dealerCards = new Card[2];
	m_dealerCards[0] = deck->DealCard();
	m_dealerCards[1] = deck->DealCard();

	m_numberOfCards = 2;
	this->m_score = m_dealerCards[0].GetPoint();

	std::cout << "Dealer is created" << std::endl;
}

Dealer::~Dealer()
{
	delete[] m_dealerCards;
}

auto Dealer::GetCurrentCard(int idx) const -> Card
{
	return m_dealerCards[idx];
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
