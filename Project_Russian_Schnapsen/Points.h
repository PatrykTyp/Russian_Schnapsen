#pragma once

#include <string>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "Bidding.h"

class Points{
public:

	static sf::Font font;

	static sf::Text pointsTextP1;
	static sf::Text pointsTextP2;
	static sf::Text pointsTextP3;

	static int pointsP1, pointsP1tmp;
	static int pointsP2, pointsP2tmp;
	static int pointsP3, pointsP3tmp;

	static bool winP1;
	static bool winP2;
	static bool winP3;

	static void sumPoints(std::string, std::string, std::string);
	static void init();
	static void draw(sf::RenderWindow&);
};

