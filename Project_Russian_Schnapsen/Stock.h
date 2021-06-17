#pragma once

#include <iostream>

#include "Players.h"
#include "Move.h"
#include "Card.h"
#include "SFML/Graphics.hpp"

class Stock : public Players, public Move{
private:

	int intStock = 1;


public:

	void stockToPlayers();
	void stockToPlayersByBot(Card[], Card[], Card[]);
	void setStock(Card[], bool, sf::Vector2u, int, int, int);
};

