#include "Menu.h"

Menu::Menu(float x, float y) {
	if (!font.loadFromFile("ex/font/sansation.ttf")) {
		std::cout << "Nie udalo sie pobrac czcionki";
	}

	menu[0].setFont(font);
	menu[0].setString("Graj");
	menu[0].setCharacterSize(50.0f);
	menu[0].setOrigin(sf::Vector2f(menu[0].getGlobalBounds().width / 2, menu[0].getGlobalBounds().height / 2));
	menu[0].setPosition(sf::Vector2f(x / 2, y / (3 + 1) * 1));

	menu[1].setFont(font);
	menu[1].setString("Zasady");
	menu[1].setCharacterSize(50.0f);
	menu[1].setOrigin(sf::Vector2f(menu[1].getGlobalBounds().width / 2, menu[1].getGlobalBounds().height / 2));
	menu[1].setPosition(sf::Vector2f(x / 2, y / (3 + 1) * 2));


	menu[2].setFont(font);
	menu[2].setString("Exit");
	menu[2].setCharacterSize(50.0f);
	menu[2].setOrigin(sf::Vector2f(menu[2].getGlobalBounds().width / 2, menu[2].getGlobalBounds().height / 2));
	menu[2].setPosition(sf::Vector2f(x / 2, y / (3 + 1) * 3));

	menuShape.setSize(sf::Vector2f(200.0f, 100.0f));
	menuShape.setFillColor(sf::Color::Red);
	menuShape.setOrigin(sf::Vector2f(menuShape.getGlobalBounds().width / 2, menuShape.getGlobalBounds().height / 2));
	menuShape.setPosition(sf::Vector2f(x / 2, y / (3 + 1) * 1));
}

Menu::~Menu() {
}

void Menu::draw(sf::RenderWindow& window) {
	window.draw(menuShape);
	for (int i = 0; i < 3; i++) {
		window.draw(menu[i]);
	}
}

void Menu::down() {
	if (option < 2) {
		option++;
		menuShape.setPosition(sf::Vector2f(menu[option].getPosition().x, menu[option].getPosition().y));
	}
	else {
		option = 0;
		menuShape.setPosition(sf::Vector2f(menu[option].getPosition().x, menu[option].getPosition().y));
	}
}
void Menu::up() {
	if (option > 0) {
		option--;
		menuShape.setPosition(sf::Vector2f(menu[option].getPosition().x, menu[option].getPosition().y));
	}
	else {
		option = 2;
		menuShape.setPosition(sf::Vector2f(menu[option].getPosition().x, menu[option].getPosition().y));
	}
}
int Menu::getOption() {
	return option;
}
