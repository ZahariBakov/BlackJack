#include "Card.h"
#include <iostream>

int width  = 140;
int height = 190;

Card::Card() 
{
	m_renderer = nullptr;
	m_suit = 0; 
	m_rank = 0;
	m_x = 0;  
	m_y = 0;
}

Card::Card(SDL_Renderer* renderer, int suit, int rank) 
{
	m_renderer = renderer;
	m_suit = suit;
	m_rank = rank;
	m_x = 0;
	m_y = 0;
	std::string path = ToStringSuit();
	m_id = std::to_string(suit) + std::to_string(rank);

	TextureManager::Instance()->LoadTexture(path.c_str(), m_id, m_renderer);
}

int Card::GetCardSuit() const 
{
	return this->m_suit;
}

int Card::GetCardRank() const 
{
	return this->m_rank;
}

int Card::GetPoint() const 
{
	if (GetCardRank() > 10) 
	{
		if (GetCardRank() == 14) 
		{
			return 11;
		}
		else 
		{
			return 10;
		}
	}
	else 
	{
		return GetCardRank();
	}
}

void Card::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

auto Card::GetId() const -> std::string
{
	return m_id;
}

void Card::Render() const 
{
	TextureManager::Instance()->DrawTexture(m_id, m_x, m_y, width, height, m_renderer);
}

void Card::SetRenderer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

std::string Card::ToStringSuit() const 
{
	std::string suit;

	switch (GetCardSuit()) 
	{
		case 1:
		{
			suit = "cardDiamonds";
			break;
		}
		case 2:
		{
			suit = "cardClubs";
			break;
		}
		case 3:
		{
			suit = "cardHearts";
			break;
		}
		case 4:
		{
			suit = "cardSpades";
			break;
		}
		default:
		{
			break;
		}
	}

	std::string result = "assets/cards/" + suit + this->ToStringRank(GetCardRank()) + ".png";

	return result;
}

std::string Card::ToStringRank(int rank) const 
{
	std::string result;

	if (rank > 10) 
	{
		switch (rank) 
		{
			case 11:
			{
				result = "J";
				break;
			}
			case 12:
			{
				result = "Q";
				break;
			}
			case 13:
			{
				result = "K";
				break;
			}
			case 14:
			{
				result = "A";
				break;
			}
			default:
			{
				break;
			}
		}
	}
	else 
	{
		result = std::to_string(rank);
	}

	return result;
}
