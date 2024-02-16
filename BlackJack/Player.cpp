#include "Player.h"

#include <iostream>

/// Player constructor that set money, score and bet to default values 
Player::Player(CardDeck& deck) {
	this->_money = 100000;
	this->_bet = 100;

	playerCards = new Card[11];
	playerCards[0] = deck.dealCard();
	playerCards[1] = deck.dealCard();

	numberOfCards = 2;
	this->_score = playerCards[0].getPoint() + playerCards[1].getPoint();

	std::cout << "Player is created" << std::endl;
}

Player::~Player() {
	delete[] playerCards;
}

/// Function that give access to player's money to outside world
int Player::getMoney() const {
	return this->_money;
}

/// Function that give access to player's score to outside world
int Player::getScore() const {
	return this->_score;
}

/// Function that give access to player's bet to outside world
int Player::getBet() const {
	return this->_bet;
}

/// Function that adds profit to the plaeyr's current money
void Player::increaseMoney(int profit) {
	this->_money += profit;
}

/// Function that subtract loss from the player's current money
void Player::decreaseMoney(int loss) {
	this->_money -= loss;
}

/// Function that reset the player's score to 0 after end of a round
void Player::resetScore() {
	this->_score = 0;
}

/// Function that increase the player's score after opening a new card
void Player::increaseScore(int points) {
	this->_score += points;
	std::cout << "Player Score is: " << _score << " after increase with " << points << std::endl;
}

/// Function that sets the player's bet to either 100 or 1000 based on the boolean parameter
void Player::setBet(bool big) {
	if (big == true) {
		this->_bet = 1000;
	}
	else {
		this->_bet = 100;
	}
}
