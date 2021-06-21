#include "Move.h"

bool Move::isStock = false;
bool Move::checkCard = true;

int Move::turn = 0;
int Move::cardStock = 0;
int Move::selectedCard = 0;
int Move::isReset = 0;
int Move::cardUsed[8] = { -1,-1,-1 ,-1 ,-1 ,-1 ,-1 ,-1 };
int Move::cardStockUsed[3] = { -1,-1,-1 };

sf::RectangleShape Move::chooseCard;


Move::Move() {
	
}

void Move::init() {
	chooseCard.setSize(sf::Vector2f(96.0f, 16.0f));
	chooseCard.setFillColor(sf::Color::Red);
	chooseCard.setOrigin(sf::Vector2f(chooseCard.getGlobalBounds().width / 2, chooseCard.getGlobalBounds().height / 2));
	chooseCard.setPosition(sf::Vector2f(490.0f, 470.0f));

	Bidding::init();
}

void Move::left() {
	if (isReset == 7)
		chooseCard.setPosition(sf::Vector2f(Players::player1[0].cardImg.getPosition().x, Players::player1[0].cardImg.getPosition().y + 70.0f));
	if (!isStock) {
		cardStock = 0;
		if (selectedCard >= 0) {
			do {
				if (selectedCard == 0)
					selectedCard = 7;
				else
					selectedCard--;
			} while (selectedCard == cardUsed[selectedCard]);
			chooseCard.setPosition(sf::Vector2f(Players::player1[selectedCard].cardImg.getPosition().x, Players::player1[selectedCard].cardImg.getPosition().y + 70.0f));
		}
	}
	else {
		selectedCard = 0;
		if (cardStock >= 0) {
			do {
				if (cardStock == 0)
					cardStock = 2;
				else
					cardStock--;
			} while (cardStock == cardStockUsed[cardStock]);
			chooseCard.setPosition(sf::Vector2f(Players::stock[cardStock].cardImg.getPosition().x, Players::stock[cardStock].cardImg.getPosition().y + 70.0f));
		}
	}
}

void Move::right() {
	if (isReset == 7)
		chooseCard.setPosition(sf::Vector2f(Players::player1[0].cardImg.getPosition().x, Players::player1[0].cardImg.getPosition().y + 70.0f));
	if (!isStock) {
		cardStock = 0;
		if (selectedCard <= 7) {
			do {
				if (selectedCard == 7)
					selectedCard = 0;
				else
					selectedCard++;
			} while (selectedCard == cardUsed[selectedCard]);
			chooseCard.setPosition(sf::Vector2f(Players::player1[selectedCard].cardImg.getPosition().x, Players::player1[selectedCard].cardImg.getPosition().y + 70.0f));
		}
	}
	else {
		selectedCard = 0;
		if (cardStock <= 2) {
			do {
				if (cardStock == 2)
					cardStock = 0;
				else
					cardStock++;
			} while (cardStock == cardStockUsed[cardStock]);
			chooseCard.setPosition(sf::Vector2f(Players::stock[cardStock].cardImg.getPosition().x, Players::stock[cardStock].cardImg.getPosition().y + 70.0f));
		}
	}
}

bool Move::getStock() {
	return isStock;
}

int Move::getSelectedCard() {
	return selectedCard;
}

void Move::choosenCard(Card& card) {
	std::cout << "choosenCard" << std::endl;
	card.cardImg.setPosition(sf::Vector2f(490.0f, 400.0f));
	chooseCard.setPosition(sf::Vector2f(card.cardImg.getPosition().x, card.cardImg.getPosition().y + 70.0f));
}

void Move::turnBack() {
	sf::Vector2u backSize = Card::cardBack.getSize();
	backSize.x /= 6;
	backSize.y /= 4;
	int n = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			Players::player2[n].cardImg.setTexture(Card::cardBack);
			Players::player2[n].cardImg.setTextureRect(sf::IntRect(backSize.x * j, backSize.y * i, backSize.x, backSize.y));
			Players::player3[n].cardImg.setTexture(Card::cardBack);
			Players::player3[n].cardImg.setTextureRect(sf::IntRect(backSize.x * j, backSize.y * i, backSize.x, backSize.y));
			if (n == 6)
				break;
			else
				n++;
		}

	}
}

void Move::turnBack(Card& card) {
	sf::Vector2u backSize = Card::cardBack.getSize();
	backSize.x /= 6;
	backSize.y /= 4;
	int x = card.value % 6;
	int y = card.value / 6;

	card.cardImg.setTexture(Card::cardBack);
	card.cardImg.setTextureRect(sf::IntRect(backSize.x * x, backSize.y * y, backSize.x, backSize.y));
}

void Move::turnFront(Card& card) {
	sf::Vector2u frontSize = Card::deckTexture.getSize();
	frontSize.x /= 6;
	frontSize.y /= 4;
	int x = card.value % 6;
	int y = card.value / 6;

	card.cardImg.setTexture(Card::deckTexture);
	card.cardImg.setTextureRect(sf::IntRect(frontSize.x * x, frontSize.y * y, frontSize.x, frontSize.y));
}


