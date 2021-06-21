#pragma once

#include <iostream>

#include "Players.h"
#include "Move.h"
#include "Card.h"
#include "Triumph.h"
#include "SFML/Graphics.hpp"

class Stock : public Players{
public:
	static int intStock;
	static void stockToPlayers();
	static void stockToPlayersByBot(Card[], Card[], Card[]);
	static void setStock(Card[], bool&, sf::Vector2u, int, int, int);
};

