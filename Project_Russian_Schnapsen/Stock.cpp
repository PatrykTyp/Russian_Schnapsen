#include "Stock.h"

void Stock::stockToPlayers() {
	const sf::Texture* texture = stock[cardStock].cardImg.getTexture();
	sf::Vector2u textureSize = texture->getSize();
	textureSize.x /= 6;
	textureSize.y /= 4;
	int x = stock[cardStock].value % 6;
	int y = stock[cardStock].value / 6;
	

	switch (intStock) {
	case 1:
		player1[7].figure = stock[cardStock].figure;
		player1[7].color = stock[cardStock].color;
		player1[7].value = stock[cardStock].value;
		player1[7].cardImg.setTexture(*texture);
		player1[7].cardImg.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
		player1[7].cardImg.setPosition(sf::Vector2f(754.5f, 79.0f));
		player1[7].cardImg.setOrigin(sf::Vector2f(player1[7].cardImg.getGlobalBounds().width / 2, player1[7].cardImg.getGlobalBounds().height / 2));
		stock[cardStock].cardImg.setTexture(Card::getTextureUsed());
		//czyMeldunek(gracz1, jakiMeldunek1);
		break;
	case 2:
		player2[7].figure = stock[cardStock].figure;
		player2[7].color = stock[cardStock].color;
		player2[7].value = stock[cardStock].value;
		player2[7].cardImg.setTexture(*texture);
		//player2[7].cardImg.setTexture(tylKarty);
		player2[7].cardImg.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
		player2[7].cardImg.setPosition(sf::Vector2f(754.5f, 721.0f));
		player2[7].cardImg.setOrigin(sf::Vector2f(player2[7].cardImg.getGlobalBounds().width / 2, player2[7].cardImg.getGlobalBounds().height / 2));
		stock[cardStock].cardImg.setTexture(Card::getTextureUsed());
		//czyMeldunek(gracz2, jakiMeldunek2);
		break;
	case 3:
		player3[7].figure = stock[cardStock].figure;
		player3[7].color = stock[cardStock].color;
		player3[7].value = stock[cardStock].value;
		player3[7].cardImg.setTexture(*texture);
		//player3[7].cardImg.setTexture(tylKarty);
		player3[7].cardImg.setTextureRect(sf::IntRect(textureSize.x * x, textureSize.y * y, textureSize.x, textureSize.y));
		player3[7].cardImg.setOrigin(sf::Vector2f(player3[7].cardImg.getGlobalBounds().width / 2, player3[7].cardImg.getGlobalBounds().height / 2));
		player3[7].cardImg.setPosition(sf::Vector2f(1115.0f, 738.0f));
		player3[7].cardImg.setRotation(-90.0f);

		stock[cardStock].cardImg.setTexture(Card::getTextureUsed());
		//przyznanyMusik = 0;
		chooseCard.setPosition(sf::Vector2f(player1[0].cardImg.getPosition().x, player1[0].cardImg.getPosition().y + 70.0f));
		//musikCzyNie = false;
		isStock = false;
		//czyMeldunek(gracz3, jakiMeldunek3);
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

	/*
	* Proste szukanie maksymalnej wartoœci spoœród 3 liczb
	* Znalezienie wœród talii kart odpowiednich wspó³rzêdnych grafiki karty
	*/
	for (int i = 0; i < 3; i++) {
		if (stock[i].value >= max) {
			max = stock[i].value;
			id = i;
			x = stock[i].value % 6;
			y = stock[i].value / 6;
		}
	}
	/*
	* Przekazanie karty do talii gracza
	*/
	setStock(botWinner, isP3, textureSize, x, y, id);
	/*
	* Dopasowanie, które karty z musika nie zosta³y wybrane i roznanie ich pozosta³ym graczom
	*/
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
	/*
	* Wyzerowanie wartoœci odpowiadaj¹cych za fazê musiku
	* Dziêki temu gra mo¿e siê rozpocz¹æ
	*/
	tylJednejKarty(gracz2[7]);
	tylJednejKarty(gracz3[7]);
	czyMusik = false;
	musikCzyNie = false;
	wybierzKarte.setPosition(sf::Vector2f(gracz1[0].card.getPosition().x, gracz1[0].card.getPosition().y + 70.0f));
}

