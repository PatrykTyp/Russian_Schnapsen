#include "Bidding.h"

sf::CircleShape Bidding::circle1, Bidding::circle2, Bidding::circle3, Bidding::circle4;
sf::Text Bidding::bid[3], Bidding::win, Bidding::currentBid;
sf::Font Bidding::font;
sf::RectangleShape Bidding::bidShape;
int Bidding::biddingP1, Bidding::biddingP2, Bidding::biddingP3;


int Bidding::option;
int Bidding::minBidding;
bool Bidding::canIPass = false;
bool Bidding::startBot = false;

bool Bidding::isBidding = true;
int Bidding::whoWonBid;
int Bidding::pointsNeeded = 0;
std::pair<int, bool> Bidding::first;

int Bidding::whoWonMatch = 0;
int Bidding::reset = 0;

void Bidding::init() {
	font.loadFromFile("ex/font/sansation.ttf");
	minBidding = 100;
	whoWonBid = 1;
	/*
	* Nadawanie w³aœciwoœci wielkoœci licytacji
	*/
	for (int i = 0; i < 3; i++) {
		bid[i].setFont(font);
		bid[i].setFillColor(sf::Color::Yellow);
		bid[i].setCharacterSize(32);
		bid[i].setPosition(sf::Vector2f(150.0f, 250.0f + (50.0f * i)));
	}
	bid[0].setString("PASS");
	bid[1].setString("+10");
	bid[2].setString("+20");
	
	currentBid.setFont(font);
	currentBid.setCharacterSize(36);
	currentBid.setPosition(sf::Vector2f(430.0f, 250.0f));
	currentBid.setFillColor(sf::Color::Blue);
	currentBid.setString("Aktualna licytacja: " + std::to_string(minBidding));


	bidShape.setSize(sf::Vector2f(150.0f, 50.0f));
	bidShape.setFillColor(sf::Color::Blue);
	bidShape.setOrigin(sf::Vector2f(bidShape.getGlobalBounds().width / 2, bidShape.getGlobalBounds().height / 2));
	bidShape.setPosition(sf::Vector2f(bid[0].getPosition().x + 50.0f, bid[0].getPosition().y + 10.0f));

	circle1.setFillColor(sf::Color::Green);
	circle1.setRadius(15.0f);
	circle1.setPosition(sf::Vector2f(380.0f, 170.0f));
	circle2.setFillColor(sf::Color::Green);
	circle2.setRadius(15.0f);
	circle2.setPosition(sf::Vector2f(380.0f, 600.0f));
	circle3.setFillColor(sf::Color::Green);
	circle3.setRadius(15.0f);
	circle3.setPosition(sf::Vector2f(950.0f, 170.0f));
	circle4.setFillColor(sf::Color::Yellow);
	circle4.setRadius(18.0f);
	circle4.setPosition(sf::Vector2f(377.0f, 167.0f));
	

	first.first = 1;
	first.second = true;
}

void Bidding::draw(sf::RenderWindow& window) {
	window.draw(bidShape);
	window.draw(circle4);
	window.draw(circle1);
	window.draw(circle2);
	window.draw(circle3);

	window.draw(currentBid);
	for (int i = 0; i < 3; i++) {
		window.draw(bid[i]);
	}
}

void Bidding::down() {
	if (option < 2) {
		option++;
		bidShape.setPosition(sf::Vector2f(bid[option].getPosition().x + 50.0f, bid[option].getPosition().y + 10.0f));
	}
	else {
		option = 0;
		bidShape.setPosition(sf::Vector2f(bid[option].getPosition().x + 50.0f, bid[option].getPosition().y + 10.0f));
	}
};

void Bidding::up() {
	if (option > 0) {
		option--;
		bidShape.setPosition(sf::Vector2f(bid[option].getPosition().x + 50.0f, bid[option].getPosition().y + 10.0f));
	}
	else {
		option = 2;
		bidShape.setPosition(sf::Vector2f(bid[option].getPosition().x + 50.0f, bid[option].getPosition().y + 10.0f));
	}
};

void Bidding::bidding() {
	if ((biddingP1 == -1 && biddingP2 == -1) || (biddingP1 == -1 && biddingP3 == -1) || (biddingP2 == -1 && biddingP3 == -1)) {
		checkBid();
		return;
	}
	if (whoWonBid == 1 && biddingP1 != -1) {
		if (first.second)
			option = 0;
		whoWonBid++;
		switch (option) {
		case 0:
			if (canIPass) {
				for (int i = 0; i < 3; i++) {
					bid[i].setFillColor(sf::Color::Red);
				}
				biddingP1 = -1;
			}
			else {
				biddingP1 = 100;
			}
			break;
		case 1:
			minBidding += 10;
			currentBid.setString("Aktualna licytacja: " + std::to_string(minBidding));
			biddingP1 = minBidding;
			break;
		case 2:
			minBidding += 20;
			currentBid.setString("Aktualna licytacja: " + std::to_string(minBidding));
			biddingP1 = minBidding;
			break;
		default:
			std::cout << "sth wrong!" << std::endl;
			break;
		}
		first.second = false;
		canIPass = true;
		circle4.setPosition(sf::Vector2f(377.0f, 597.0f));
		std::cout << "ja: " << biddingP1 << std::endl;
	}
	else if (whoWonBid == 2) {
		biddingP2 = biddingBot(Players::player2, biddingP2);
		std::cout << "b2: " << biddingP2 << std::endl;
		circle4.setPosition(sf::Vector2f(947.0f, 167.0f));
	}
	else if (whoWonBid == 3) {
		biddingP3 = biddingBot(Players::player3, biddingP3);
		std::cout << "b3: " << biddingP3 << std::endl;
		circle4.setPosition(sf::Vector2f(377.0f, 167.0f));
	}

	
}

int Bidding::biddingBot(Card deck[], int biddingP) {
	whoWonBid++;
	int point = checkDeck(deck);
	/*
	* Wielkoœæ licytacji jest okreœlana za pomoc¹ iloœci asów (karta daj¹ca najwiêcej punktów) w talii gracza.
	*/

	/*
	* Sprawdzane jest czy minimalna wartoœæ licytacji jest mniejsza ni¿ ta, za któr¹ gracz mo¿e zalicytowaæ
	* Je¿eli tak to licytuje, tym samym podnosz¹c minimum jakie musi zostaæ wylicytowane, eliminuj¹c powtarzanie siê wartoœci w partii
	*/
	if (startBot == true) {
		minBidding = 100;
		startBot = false;
		return 100;
	}
	else if (point != 0 && point <= 11 && minBidding < 120) {
		minBidding += 10;
		currentBid.setString("Aktualna licytacja: " + std::to_string(minBidding));
		return minBidding;
	}
	else if (point != 0 && point >= 20 && minBidding < 120) {
		minBidding += 10;
		currentBid.setString("Aktualna licytacja: " + std::to_string(minBidding));
		return minBidding;
	}
	else {
		return -1;
	}
	/*
	* Zmiana wartoœci pierwszej licytacji, jezeli gracz sterowany przez osobê by³ pierwszy
	*/
}

void Bidding::checkBid() {
	std::cout << "P1: " << biddingP1 << "____P2: " << biddingP2 << "_____P3: " << biddingP3 << std::endl;
	if (biddingP1 == -1)
		circle1.setFillColor(sf::Color::Red);
	if (biddingP2 == -1)
		circle2.setFillColor(sf::Color::Red);
	if (biddingP3 == -1)
		circle3.setFillColor(sf::Color::Red);

	if (biddingP2 == -1 && biddingP3 == -1) {
		GameMechanics::whoFirst.first = true;
		GameMechanics::whoFirst.second = true;
		isBidding = false;
		whoWonBid = 1;
		pointsNeeded = biddingP1;
	}
	else if (biddingP1 == -1 && biddingP3 == -1) {
		GameMechanics::whoFirst.first = false;
		GameMechanics::whoFirst.second = true;
		isBidding = false;
		whoWonBid = 2;
		pointsNeeded = biddingP2;
		//wybierzMusikBot(gracz2, gracz1, gracz3);
	}
	else if (biddingP1 == -1 && biddingP2 == -1) {
		GameMechanics::whoFirst.first = true;
		GameMechanics::whoFirst.second = false;
		isBidding = false;
		whoWonBid = 3;
		pointsNeeded = biddingP3;

		//wybierzMusikBot(gracz3, gracz1, gracz2);
	}

	if (!isBidding) {
		Move::setStock(true);
		Move::turn = whoWonBid;
	}
	
	if (biddingP1 > biddingP2 && biddingP1 > biddingP3) {
		//wygrywaLicytacje.setString("Wygrywa G1 : " + to_string(licytacjaJa));
		GameMechanics::whoFirst.first = true;
		GameMechanics::whoFirst.second = true;
	}
	else if (biddingP2 > biddingP1 && biddingP2 > biddingP3) {
		//wygrywaLicytacje.setString("Wygrywa G2 : " + to_string(licytacjaBot2));
		GameMechanics::whoFirst.first = false;
		GameMechanics::whoFirst.second = true;
	}
	else if (biddingP3 > biddingP1 && biddingP3 > biddingP2) {
		//wygrywaLicytacje.setString("Wygrywa G3 : " + to_string(licytacjaBot3));
		GameMechanics::whoFirst.first = true;
		GameMechanics::whoFirst.second = false;
	}
}

int Bidding::checkDeck(Card deck[]) {
	int points = 0;
	for (int i = 0; i < 8; i++) {
		if (deck[i].figure == "A")
			points += 11;
	}
	return points;
}

bool Bidding::getPass() {
	if (biddingP1 != -1) {
		return false;
	}
	return true;
}