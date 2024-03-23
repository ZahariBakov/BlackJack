#pragma once

#include "CardDeck.h"

class Player 
{
public:
	Player(CardDeck* deck);
	~Player();

	//int getMoney() const;
	//int getScore() const;
	//int getBet() const;

	//void increaseMoney(int profit);
	//void decreaseMoney(int loss);
	//void setBet(bool big);
	//void increaseScore(int points);
	//void addCard(CardDeck& deck);

	auto GetNumberOfCards() const -> int;

	auto GetCurrentCard(int idx) const -> Card;

private:
	int m_money = 100000;
	int m_score;
	int m_bet = 100;
	int m_numberOfCards = 2;

	Card* m_playerCards;
};
