#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

#include "Card.h"
#include "Players.h"
#include "GameMechanics.h"
#include "Move.h"
#include "Stock.h"

class Bidding{
private:
	
	static sf::Text bid[], win, currentBid;
	static sf::Font font;
	static sf::RectangleShape bidShape;
	

	static int option;
	static int minBidding;
	static bool canIPass;
	static bool startBot;

public:
	static sf::CircleShape circle1, circle2, circle3, circle4;
	static sf::Text bidWin;

	static int biddingP1, biddingP2, biddingP3;
	static bool isBidding;
	static int whoWonBid;
	static int pointsNeeded;
	static std::pair<int, bool>first;

	static int whoWonMatch;

	static int reset;
	static bool isReset;
	static bool iWin;
	static bool end;

	static void init();
	static sf::Font getFont();

	static void draw(sf::RenderWindow& window);
	static void down();
	static void up();

	static void bidding();
	static int biddingBot(Card[], int);
	static void checkBid();
	static int checkDeck(Card []);

	static bool getPass();
	static void resetAll();

};

