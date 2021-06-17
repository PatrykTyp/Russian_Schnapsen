#pragma once
#include<SFML/Graphics.hpp>

#include "Menu.h"
#include "Rules.h"
#include "Card.h"
#include "Players.h"
#include "Move.h"
#include "GameMechanics.h"
#include "Stock.h"


class Gra : public Stock{
private:
	sf::RenderWindow window;
	sf::View view;
	int windowFocus;

	sf::Sprite table;
	sf::Texture tableTexture;
	
	Card choosenByBot;

	void course();
	void draw();
	void reset();

protected:
	Menu menu;
	Rules rules;

private:
	void cardPosition();
	void cardTurn();
	void oneCardBack(Card&);
	void oneCardFront(Card&);

public:
	Gra();
	void start();
};

