#pragma once

#include <string>

class Card {
public:
	/// Default Constructor
	Card() : _cardSuit(0), _cardRank(0) {};

	/// Constructor of the class
	Card(int suit, int rank);

	/// Functions to returns suit, rank and points
	int getCardSuit() const;
	int getCardRank() const;
	int getPoint() const;

	/// Function to create card name and rank in string format
	std::string toStringSuit() const;
	
private:
	/// Variables for suit and rank
	int _cardSuit;
	int _cardRank;

	/// Inner function that create rank in string format
	std::string toStringRank(int rank) const;
};
