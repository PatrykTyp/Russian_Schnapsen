#pragma once

#include <SFML/Graphics.hpp>

#include "Card.h"
#include "Players.h"
#include "Bidding.h"

class Move{
private:
	

	static bool isStock;
	static int selectedCard;
public:
	Move();

	static int cardUsed[];
	static int cardStockUsed[];
	static int isReset;
	static int cardStock;
	static int turn;

	static bool checkCard;

	static sf::RectangleShape chooseCard;

	static void left();
	static void right();
	static void init();

	static bool getStock();
	static void setStock(bool);
	static int getSelectedCard();

	static void choosenCard(Card&);

	static void turnBack();
	static void turnBack(Card&);
	static void turnFront(Card&);

	friend class Stock; 
};



