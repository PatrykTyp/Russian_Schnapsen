#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

#include "Card.h"
#include "Players.h"
#include "GameMechanics.h"
#include "Move.h"

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

	static int biddingP1, biddingP2, biddingP3;
	static bool isBidding;
	static int whoWonBid; //powygranej rundzie first +1 *DODAÆ*
	static int pointsNeeded;
	static std::pair<int, bool>first;

	static int whoWonMatch;
	static int reset;

	static void init();

	static void draw(sf::RenderWindow& window);
	static void down();
	static void up();

	static void bidding();
	static int biddingBot(Card[], int);
	static void checkBid();
	static int checkDeck(Card []);

	static bool getPass();

};

