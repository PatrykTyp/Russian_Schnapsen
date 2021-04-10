#pragma once

#include <SFML/Graphics.hpp>

#include "Card.h"
#include "Players.h"

class Move{
private:
	

	static bool isBidding;
	static int cardBidding;
	static int selectedCard;
public:
	Move();

	static int cardUsed[];
	static int cardBiddingUsed[];
	static int isReset;

	static sf::RectangleShape chooseCard;

	static void left();
	static void right();
	static void init();
};



