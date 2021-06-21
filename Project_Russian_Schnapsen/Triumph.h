#pragma once

#include "Card.h"

#include <utility>
#include <iostream>

class Triumph{
public:
	static std::pair<std::pair<bool, int>, std::string> tKing[4];
	static std::pair<std::pair<bool, int>, std::string> tQueen[4];
	static int activeT;

	static void isTriumph(Card[]);
};

