#include "Rules.h"



/*
* Konstruktor Zasady
*/
Rules::Rules() {
	texture.loadFromFile("ex/image/zasady.png");

	view.setSize(sf::Vector2f(1200.0f, 800.0f));
	view.setCenter(sf::Vector2f(600.0f, 400.0f));

	bground.setTexture(texture);

	font.loadFromFile("ex/font/sansation.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Red);

	outRules();
}

Rules::~Rules() {}

/*
* Poruszanie siê po oknie Zasady za pomoc¹ scrolla
* W górê
* i w dó³
*/
void Rules::scrollUp() {
	if (view.getCenter().y > 400.0f)
		view.move(sf::Vector2f(0, -25.0f));
}

void Rules::scrollDown() {
	if (view.getCenter().y < 1200.0f)
		view.move(sf::Vector2f(0, 25.0f));
}

/*
* Resetowanie widoku okna na domyœln¹
*/
void Rules::scrollReset() {
	float tmp = -(view.getCenter().y - 400.0f);
	view.move(sf::Vector2f(0, tmp));
}

/*
* Rysowanie t³a i obiektów Zasady
*/
void Rules::draw(sf::RenderWindow& window) {
	window.setView(view);
	window.draw(bground);
	window.draw(text);
}

/*
* Metoda, która wczytuje na ekran zapisany w pliku tekst z zasadmi dotycz¹cymi gry
*/
void Rules::outRules() {
	std::string line;
	std::ifstream rulesFile;
	std::string rulesText;
	rulesFile.open("ex/rules/zasady.txt");
	if (rulesFile) {
		while (std::getline(rulesFile, line)) {
			rulesText += line + "\n";
		}
	}
	else {
		std::cout << "Nie udalo sie otworzyc pliku";
	}
	text.setString(rulesText);
	text.setCharacterSize(25);
	text.setPosition(15.0f, 15.0f);
}