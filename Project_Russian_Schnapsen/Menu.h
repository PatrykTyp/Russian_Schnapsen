#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
public:
	Menu(float x, float y);
	~Menu();

	void draw(sf::RenderWindow& window);
	void down();
	void up();
	int getOption();
private:
	sf::Font font;
	sf::Text menu[3];
	sf::RectangleShape menuShape;
	int option = 0;
};

