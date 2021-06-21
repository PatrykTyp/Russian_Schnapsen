#pragma once

#include <string>
#include <random>
#include <SFML/Graphics.hpp>
#include <iostream>


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

	static void loadCard(Card[]);    
	static void reshuffleCard(Card[]);  
	static void deal(Card[], Card[], Card[], Card[], Card[]);
	static void assignImg(Card[]);

	static sf::Texture getTextureUsed();
	static void setTextures();

	
};

