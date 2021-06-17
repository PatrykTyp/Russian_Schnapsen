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
	
	static sf::Texture cardBack;
	static sf::Texture cardUsed;
	static sf::Texture deckTexture;

	static sf::Texture* ptrTexture;

	static void loadCard(Card[]);    // Wczytywanie kart do talii
	static void reshuffleCard(Card[]);  // Tasowanie kart w talii
	static void deal(Card[], Card[], Card[], Card[], Card[]);
	static void assignImg(Card[]);

	static sf::Texture getTextureUsed();
	static void setTextures();

	
};

