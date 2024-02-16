#include "Card.h"

Card::Card(int suit, int rank) : _cardSuit(suit), _cardRank(rank) {}

/// Function that give's access to card suit to outside world
int Card::getCardSuit() const {
	return this->_cardSuit;
}

/// Function that give's access to card rank to outside world
int Card::getCardRank() const {
	return this->_cardRank;
}

/// Function that return card points
int Card::getPoint() const {
	if (getCardRank() > 10) {
		if (getCardRank() == 14) {
			return 11;
		}
		else {
			return 10;
		}
	}
	else {
		return getCardRank();
	}
}

/// Function to create string that is used to select image when dislayed
std::string Card::toStringSuit() const {
	std::string suit;

	switch (getCardSuit()){
		case 1:
			suit = "cardDiamonds";
			break;
		case 2:
			suit = "cardClubs";
			break;
		case 3:
			suit = "cardHearts";
			break;
		case 4:
			suit = "cardSpades";
			break;

		default:
			break;
	}

	std::string result = "assets/cards/" + suit + this->toStringRank(getCardRank()) + ".png";

	return result;
}

std::string Card::toStringRank(int rank) const {
	std::string result;

	if (rank > 10) {
		switch (rank) {
			case 11:
				result = "J";
				break;
			case 12:
				result = "Q";
				break;
			case 13:
				result = "K";
				break;
			case 14:
				result = "A";
				break;
			default:
				break;
		}
	}
	else {
		result = std::to_string(rank);
	}

	return result;
}
