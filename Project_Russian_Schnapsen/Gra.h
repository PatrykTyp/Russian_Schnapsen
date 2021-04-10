#pragma once
#include<SFML/Graphics.hpp>

#include "Menu.h"
#include "Rules.h"
#include "Card.h"
#include "Players.h"
#include "Move.h"


class Gra{
private:
	sf::RenderWindow window;
	sf::View view;
	int windowFocus;

	sf::Sprite table;
	sf::Texture deckTexture;
	sf::Texture tableTexture;
	sf::Texture cardBack;
	sf::Texture cardUsed;

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

