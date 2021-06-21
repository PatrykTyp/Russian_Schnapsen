#pragma once

#include <utility>
#include <string>
#include <iostream>

#include "Card.h"
#include "Players.h"
#include "Triumph.h"
#include "Points.h"
#include "Move.h"

class GameMechanics: public Triumph {
public:
	
	static std::pair<bool, bool> whoFirst;
	static bool throwCard;

	static int who;
	static float a, b;

	static int bidder;

	static Card* previousCardP1Ptr;
	static Card* previousCardP2Ptr;
	static Card* previousCardP3Ptr;

	static void sendValues(Card&, Card&);
	static Card sendValuesBot(Card[], float);
	static Card sendValuesBot(Card&, Card[], float);
	static void getCardAddress(Card&);

	static void checkGame(Card&, Card&, Card&);

	static void removeCard();
};
 
