#pragma once

#include "CardDeck.h"
#include <vector>

class Player {
public:
	Player(CardDeck* deck);/*!< Default constructor*/
	~Player();

	//int getMoney() const;/*!< Function that return the value of money*/
	//int getScore() const;/*!< Function that return the value of score*/
	//int getBet() const;/*!< Function that return the value of bet*/

	//void increaseMoney(int profit);/*!< Function that increase the value of money*/
	//void decreaseMoney(int loss);/*!< Function that decrease the value of money*/
	//void setBet(bool big);/*!< Function that set the value of bet*/
	//void increaseScore(int points);/*!< Function that increase the value of score*/
	//void addCard(CardDeck& deck);

	Card* m_playerCards;

	int m_numberOfCards;

private:
	int m_money;
	int m_score;
	int m_bet;
};
