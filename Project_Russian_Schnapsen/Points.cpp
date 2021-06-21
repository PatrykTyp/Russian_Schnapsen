#include "Points.h"

sf::Font Points::font;

sf::Text Points::pointsTextP1;
int Points::pointsP1 = 0;
int Points::pointsP1tmp = 0;

sf::Text Points::pointsTextP2;
int Points::pointsP2 = 0;
int Points::pointsP2tmp = 0;

sf::Text Points::pointsTextP3;
int Points::pointsP3 = 0;
int Points::pointsP3tmp = 0;

bool Points::winP1 = 0;
bool Points::winP2 = 0;
bool Points::winP3 = 0;

void Points::init() {

	font.loadFromFile("ex/font/sansation.ttf");

	pointsTextP1.setFont(font);
	pointsTextP1.setFillColor(sf::Color::Red);
	pointsTextP1.setCharacterSize(32);
	pointsTextP1.setString("0");
	pointsTextP1.setPosition(sf::Vector2f(100.0f, 160.0f));

	pointsTextP2.setFont(font);
	pointsTextP2.setFillColor(sf::Color::Red);
	pointsTextP2.setCharacterSize(32);
	pointsTextP2.setString("0");
	pointsTextP2.setPosition(sf::Vector2f(100.0f, 600.0f));

	pointsTextP3.setFont(font);
	pointsTextP3.setFillColor(sf::Color::Red);
	pointsTextP3.setCharacterSize(32);
	pointsTextP3.setString("0");
	pointsTextP3.setPosition(sf::Vector2f(995.0f, 75.0f));
}

void Points::sumPoints(std::string cardP1, std::string cardP2, std::string cardP3) {
	std::cout << "sum points" << std::endl;
	int roundPoints = 0;

	if (cardP1 == "A")
		roundPoints += 11;
	else if (cardP1 == "K")
		roundPoints += 4;
	else if (cardP1 == "Q")
		roundPoints += 3;
	else if (cardP1 == "J")
		roundPoints += 2;
	else if (cardP1 == "10")
		roundPoints += 10;

	if (cardP2 == "A")
		roundPoints += 11;
	else if (cardP2 == "K")
		roundPoints += 4;
	else if (cardP2 == "Q")
		roundPoints += 3;
	else if (cardP2 == "J")
		roundPoints += 2;
	else if (cardP2 == "10")
		roundPoints += 10;

	if (cardP3 == "A")
		roundPoints += 11;
	else if (cardP3 == "K")
		roundPoints += 4;
	else if (cardP3 == "Q")
		roundPoints += 3;
	else if (cardP3 == "J")
		roundPoints += 2;
	else if (cardP3 == "10")
		roundPoints += 10;

	if (winP1 == 1) {
		pointsP1tmp += roundPoints;
	}
	else if (winP2 == 1) {
		pointsP2tmp += roundPoints;
	}
	else if (winP3 == 1) {
		pointsP3tmp += roundPoints;
	}
	roundPoints = 0;
	if (Bidding::reset == 7) {
		if (Bidding::whoWonBid == 1) {
			if (Bidding::pointsNeeded < pointsP1tmp) {
				pointsP1 += pointsP1tmp;
			}
			else {
				pointsP1 -= Bidding::pointsNeeded;
			}
			pointsP2 += pointsP2tmp;
			pointsP3 += pointsP3tmp;
			Bidding::whoWonMatch = 1;
		}
		if (Bidding::whoWonBid == 2) {
			if (Bidding::pointsNeeded < pointsP2tmp) {
				pointsP2 += pointsP2tmp;
			}
			else {
				pointsP2 -= Bidding::pointsNeeded;
			}
			pointsP1 += pointsP1tmp;
			pointsP3 += pointsP3tmp;
			Bidding::whoWonMatch = 2;
		}
		if (Bidding::whoWonBid == 3) {
			if (Bidding::pointsNeeded < pointsP3tmp) {
				pointsP3 += pointsP3tmp;
			}
			else {
				pointsP3 -= Bidding::pointsNeeded;
			}
			pointsP1 += pointsP1tmp;
			pointsP2 += pointsP2tmp;
			Bidding::whoWonMatch = 3;
		}
		pointsP1tmp = 0;
		pointsP2tmp = 0;
		pointsP3tmp = 0;
		Bidding::circle1.setFillColor(sf::Color::Green);
		Bidding::circle2.setFillColor(sf::Color::Green);
		Bidding::circle3.setFillColor(sf::Color::Green);
		if (pointsP1 >= 200) {
			Bidding::end = true;
			Bidding::iWin = true;
		}
		if (pointsP2 >= 200 || pointsP3 >= 200) {
			Bidding::end = true;
		}
	}
}

void Points::draw(sf::RenderWindow &window) {
	window.draw(pointsTextP1);
	window.draw(pointsTextP2);
	window.draw(pointsTextP3);
}