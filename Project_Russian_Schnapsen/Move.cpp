#include "Move.h"

bool Move::isBidding = false;

int Move::cardBidding = 0;
int Move::selectedCard = 0;
int Move::isReset = 0;
int Move::cardUsed[8] = { -1,-1,-1 ,-1 ,-1 ,-1 ,-1 ,-1 };
int Move::cardBiddingUsed[3] = { -1,-1,-1 };

sf::RectangleShape Move::chooseCard;


Move::Move() {
	
}

void Move::init() {
	chooseCard.setSize(sf::Vector2f(96.0f, 16.0f));
	chooseCard.setFillColor(sf::Color::Red);
	chooseCard.setOrigin(sf::Vector2f(chooseCard.getGlobalBounds().width / 2, chooseCard.getGlobalBounds().height / 2));
	chooseCard.setPosition(sf::Vector2f(490.0f, 470.0f));
}

void Move::left() {
	/*
	* ustawienie znacznika kart, na pierwsz¹ w rêce, gdy partia dobiegnie koñca
	*/
	if (isReset == 7)
		chooseCard.setPosition(sf::Vector2f(Players::player1[0].cardImg.getPosition().x, Players::player1[0].cardImg.getPosition().y + 70.0f));
	/*
	* Sprawdzenie czy aktualnie nie rozdajemy musiku
	* W zale¿noœci od tego albo poruszamy siê po kartach musiku rozdaj¹c je graczom,
	* albo poruszamy siê po w³asnych kartach
	*/
	if (!isBidding) {
		cardBidding = 0;
		/*
		* Sprawdzenie, czy nastêpna karta nie zosta³a ju¿ u¿yta
		* Je¿eli karta s¹siednia, na któr¹ chcemy prze³¹czyæ znacznik jest u¿yta,
		* to nastêpuje przeskok do nastêpnej, wolnej karty, której mo¿emy u¿yæ
		*
		* Je¿eli karta, na której aktualnie jest znacznik znajduje siê skrajnie po lewej stronie,
		* to znacznik zostanie ustawiony na kartê skrajnie po prawej stronie
		*/
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
	/*
	* Analogia dla musiku
	*/
	else {
		selectedCard = 0;
		if (cardBidding >= 0) {
			do {
				if (cardBidding == 0)
					cardBidding = 2;
				else
					cardBidding--;
			} while (cardBidding == cardBiddingUsed[cardBidding]);
			chooseCard.setPosition(sf::Vector2f(Players::bidding[cardBidding].cardImg.getPosition().x, Players::bidding[cardBidding].cardImg.getPosition().y + 70.0f));
		}
	}
}

void Move::right() {
	/*
	* ustawienie znacznika kart, na pierwsz¹ w rêce, gdy partia dobiegnie koñca
	*/
	if (isReset == 7)
		chooseCard.setPosition(sf::Vector2f(Players::player1[0].cardImg.getPosition().x, Players::player1[0].cardImg.getPosition().y + 70.0f));
	if (!isBidding) {
		cardBidding = 0;
		/*
		* Sprawdzenie, czy nastêpna karta nie zosta³a ju¿ u¿yta
		* Je¿eli karta s¹siednia, na któr¹ chcemy prze³¹czyæ znacznik jest u¿yta,
		* to nastêpuje przeskok do nastêpnej, wolnej karty, której mo¿emy u¿yæ
		*
		* Je¿eli karta, na której aktualnie jest znacznik znajduje siê skrajnie po prawej stronie,
		* to znacznik zostanie ustawiony na kartê skrajnie po lewej stronie
		*/
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
	/*
	* Analogia dla musiku
	*/
	else {
		selectedCard = 0;
		if (cardBidding <= 2) {
			do {
				if (cardBidding == 2)
					cardBidding = 0;
				else
					cardBidding++;
			} while (cardBidding == cardBiddingUsed[cardBidding]);
			chooseCard.setPosition(sf::Vector2f(Players::bidding[cardBidding].cardImg.getPosition().x, Players::bidding[cardBidding].cardImg.getPosition().y + 70.0f));
		}
	}
}