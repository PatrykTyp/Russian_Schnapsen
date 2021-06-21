#include "Stock.h"

int Stock::intStock = 1;

void Stock::stockToPlayers() {
	const sf::Texture* texture = stock[Move::cardStock].cardImg.getTexture();
	sf::Vector2u textureSize = texture->getSize();
	textureSize.x /= 6;
	textureSize.y /= 4;
	int x = stock[Move::cardStock].value % 6;
	int y = stock[Move::cardStock].value / 6;
	

	switch (intStock) {
	case 1:
		player1[7].figure = stock[Move::cardStock].figure;
		player1[7].color = stock[Move::cardStock].color;
		player1[7].value = stock[Move::cardStock].value;
		player1[7].cardImg.setTexture(*texture);
		player1[7].cardImg.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
		player1[7].cardImg.setPosition(sf::Vector2f(754.5f, 79.0f));
		player1[7].cardImg.setOrigin(sf::Vector2f(player1[7].cardImg.getGlobalBounds().width / 2, player1[7].cardImg.getGlobalBounds().height / 2));
		stock[Move::cardStock].cardImg.setTexture(Card::getTextureUsed());
		Triumph::isTriumph(player1);
		break;
	case 2:
		player2[7].figure = stock[Move::cardStock].figure;
		player2[7].color = stock[Move::cardStock].color;
		player2[7].value = stock[Move::cardStock].value;
		player2[7].cardImg.setTexture(*texture);
		player2[7].cardImg.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
		player2[7].cardImg.setPosition(sf::Vector2f(754.5f, 721.0f));
		player2[7].cardImg.setOrigin(sf::Vector2f(player2[7].cardImg.getGlobalBounds().width / 2, player2[7].cardImg.getGlobalBounds().height / 2));
		stock[Move::cardStock].cardImg.setTexture(Card::getTextureUsed());
		Triumph::isTriumph(player2);
		break;
	case 3:
		player3[7].figure = stock[Move::cardStock].figure;
		player3[7].color = stock[Move::cardStock].color;
		player3[7].value = stock[Move::cardStock].value;
		player3[7].cardImg.setTexture(*texture);
		player3[7].cardImg.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
		player3[7].cardImg.setOrigin(sf::Vector2f(player3[7].cardImg.getGlobalBounds().width / 2, player3[7].cardImg.getGlobalBounds().height / 2));
		player3[7].cardImg.setPosition(sf::Vector2f(1115.0f, 738.0f));
		player3[7].cardImg.setRotation(-90.0f);

		stock[Move::cardStock].cardImg.setTexture(Card::getTextureUsed());
		intStock = 0;
		Move::chooseCard.setPosition(sf::Vector2f(player1[0].cardImg.getPosition().x, player1[0].cardImg.getPosition().y + 70.0f));
		Move::isStock = false;
		Triumph::isTriumph(player3);
		break;
	}
	intStock++;
}

void Stock::stockToPlayersByBot(Card botWinner[], Card p1[], Card botLooser[]) {
	sf::Vector2u textureSize = Card::deckTexture.getSize();
	sf::Vector2u tylKart = Card::cardBack.getSize();
	textureSize.x /= 6;
	textureSize.y /= 4;
	int x, y;

	bool isP3 = false;
	int max{}, id{};

	for (int i = 0; i < 3; i++) {
		if (stock[i].value >= max) {
			max = stock[i].value;
			id = i;
			x = stock[i].value % 6;
			y = stock[i].value / 6;
		}
	}
	setStock(botWinner, isP3, textureSize, x, y, id);
	if (id == 1 || id == 2) {
		x = stock[0].value % 6;
		y = stock[0].value / 6;
		setStock(p1, isP3, textureSize, x, y, 0);
		if (id != 1) {
			x = stock[1].value % 6;
			y = stock[1].value / 6;
			setStock(botLooser, isP3, textureSize, x, y, 1);
		}
		else {
			x = stock[2].value % 6;
			y = stock[2].value / 6;
			setStock(botLooser, isP3, textureSize, x, y, 2);
		}
	}
	else if (id == 0 || id == 2) {
		x = stock[1].value % 6;
		y = stock[1].value / 6;
		setStock(p1, isP3, textureSize, x, y, 1);
		if (id == 0) {
			x = stock[2].value % 6;
			y = stock[2].value / 6;
			setStock(botLooser, isP3, textureSize, x, y, 2);
		}
		else {
			x = stock[0].value % 6;
			y = stock[0].value / 6;
			setStock(botLooser, isP3, textureSize, x, y, 0);
		}
	}
	else if (id == 0 || id == 1) {
		x = stock[2].value % 6;
		y = stock[2].value / 6;
		setStock(p1, isP3, textureSize, x, y, 2);
		if (id == 0) {
			x = stock[1].value % 6;
			y = stock[1].value / 6;
			setStock(botLooser, isP3, textureSize, x, y, 1);
		}
		else {
			x = stock[0].value % 6;
			y = stock[0].value / 6;
			setStock(botLooser, isP3, textureSize, x, y, 0);
		}
	}
	Move::turnBack(player2[7]);
	Move::turnBack(player3[7]);
	Move::isStock = false;
	Move::chooseCard.setPosition(sf::Vector2f(player1[0].cardImg.getPosition().x, player1[0].cardImg.getPosition().y + 70.0f));
}

void Stock::setStock(Card playerDeck[], bool& isP3, sf::Vector2u textureSize, int x, int y, int id) {
	playerDeck[7].figure = stock[id].figure;
	playerDeck[7].color = stock[id].color;
	playerDeck[7].value = stock[id].value;
	playerDeck[7].cardImg.setTexture(Card::deckTexture);
	playerDeck[7].cardImg.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
	if (playerDeck[6].cardImg.getPosition().x - playerDeck[5].cardImg.getPosition().x != 0)
		playerDeck[7].cardImg.setPosition(sf::Vector2f(playerDeck[6].cardImg.getPosition().x + 97.5f, playerDeck[6].cardImg.getPosition().y));
	else {
		playerDeck[7].cardImg.setPosition(sf::Vector2f(1095.5f, playerDeck[6].cardImg.getPosition().y + 79.0f));
		playerDeck[7].cardImg.setRotation(-90.0f);
		isP3 = true;
	}
	playerDeck[7].cardImg.setOrigin(sf::Vector2f(playerDeck[7].cardImg.getGlobalBounds().width / 2, playerDeck[7].cardImg.getGlobalBounds().height / 2));
	stock[id].cardImg.setTexture(Card::cardUsed);
	Triumph::isTriumph(playerDeck);
}

