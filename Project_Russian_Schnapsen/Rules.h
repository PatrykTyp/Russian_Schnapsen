#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>

class Rules
{
public:
	Rules();
	~Rules();

	void draw(sf::RenderWindow& window);
	void scrollUp();
	void scrollDown();
	void scrollReset();


private:
	sf::Texture texture;
	sf::Sprite bground;
	sf::View view;

	sf::Font font;
	sf::Text text;

	void outRules();
};
