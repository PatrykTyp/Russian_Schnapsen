#pragma once

#include <string>
#include <random>
#include <SFML/Graphics.hpp>


class Card{
public:


	std::string color;
	std::string figure;
	int value{};
	sf::Sprite cardImg;
	bool use;
	bool marriage;

	static void loadCard(Card[]);    // Wczytywanie kart do talii
	static void reshuffleCard(Card[]);  // Tasowanie kart w talii
	static void deal(Card[], Card[], Card[], Card[], Card[]);
	static void assignImg(Card[], sf::Texture*);
};

