#include "Card.h"

void Card::loadCard(Card tab[]) {
	std::string color[4] = { "pik", "trefl", "karo", "kier" }, figure[6] = { "9","10","J","Q","K","A" };
	int wart{};
	/*
	* Dodanie do talii kart, wszystkie potrzebne do gry 24 karty (wszystkie 4 kolory + karty od 9 do Asa)
	*/
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			tab[wart].figure = figure[j];
			tab[wart].color = color[i];
			tab[wart].value = wart;
			tab[wart].use = false;
			tab[wart].marriage == false;
			wart++;

		}
	}
}

/*
* Przypisanie grafiki do poszczególnych kart
*/
void Card::assignImg(Card tab[], sf::Texture* texture) {
	sf::Vector2u taliaSize = texture->getSize();
	taliaSize.x /= 6;
	taliaSize.y /= 4;
	float a = 0, b = 20.0f;
	int n = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			tab[n].cardImg.setTexture(*texture);
			tab[n].cardImg.setTextureRect(sf::IntRect(taliaSize.x * j, taliaSize.y * i, taliaSize.x, taliaSize.y));
			tab[n].cardImg.setPosition(sf::Vector2f(a + 20.0f, b));
			tab[n].cardImg.setOrigin(sf::Vector2f(tab[n].cardImg.getGlobalBounds().width / 2, tab[n].cardImg.getGlobalBounds().height / 2));
			a += 50.0f;
			n++;
			if (n % 6 == 0) {
				b += 60.0f;
				a = 0;
			}
		}
	}
}

/*
* Przetasowanie kart, by by³y one nieuporz¹dkowane
*/
void Card::reshuffleCard(Card tab[]) {
	Card tmp;
	/*
	* System losowania polega na wylosowaniu dwóch losowych indeksów od 0 do 23, które zostan¹ zamienione miejscami
	* Powtarzamy to 1000 razy, w celu dok³adnego wymieszania kart
	*/
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> random(0, 23);
	int zamiana1{}, zamiana2{};
	for (int i = 0; i < 1000; i++) {
		zamiana1 = random(generator);
		zamiana2 = random(generator);
		tmp.figure = tab[zamiana1].figure;
		tmp.color = tab[zamiana1].color;
		tmp.value = tab[zamiana1].value;
		tmp.cardImg = tab[zamiana1].cardImg;
		tab[zamiana1].figure = tab[zamiana2].figure;
		tab[zamiana1].color = tab[zamiana2].color;
		tab[zamiana1].value = tab[zamiana2].value;
		tab[zamiana1].cardImg = tab[zamiana2].cardImg;
		tab[zamiana2].figure = tmp.figure;
		tab[zamiana2].color = tmp.color;
		tab[zamiana2].value = tmp.value;
		tab[zamiana2].cardImg = tmp.cardImg;
	}
}

/*
* Rozdanie potasowanych kart,
* Pokolei zaczynaj¹c od gracza1, rozdajemy 21 kart, 3 pozosta³e l¹duj¹ w musiku, który póŸniej bêdzie rozdany
*/
void Card::deal(Card gracz1[], Card gracz2[], Card gracz3[], Card talia[], Card musik[]) {
	int licznik{}, iloscKartWRece{};

	for (int i = 0; i < 21; i++) {
		if (i % 3 == 0) {
			gracz1[iloscKartWRece].figure = talia[i].figure;
			gracz1[iloscKartWRece].color = talia[i].color;
			gracz1[iloscKartWRece].value = talia[i].value;
			gracz1[iloscKartWRece].cardImg = talia[i].cardImg;
			licznik++;
		}
		else if (i % 3 == 1) {
			gracz2[iloscKartWRece].figure = talia[i].figure;
			gracz2[iloscKartWRece].color = talia[i].color;
			gracz2[iloscKartWRece].value = talia[i].value;
			gracz2[iloscKartWRece].cardImg = talia[i].cardImg;
			licznik++;
		}
		else {
			gracz3[iloscKartWRece].figure = talia[i].figure;
			gracz3[iloscKartWRece].color = talia[i].color;
			gracz3[iloscKartWRece].value = talia[i].value;
			gracz3[iloscKartWRece].cardImg = talia[i].cardImg;
			licznik++;
		}
		if (licznik == 3) {
			iloscKartWRece++;
			licznik = 0;
		}
	}
	for (int i = 0; i < 3; i++) {
		musik[i].figure = talia[i + 21].figure;
		musik[i].color = talia[i + 21].color;
		musik[i].value = talia[i + 21].value;
		musik[i].cardImg = talia[i + 21].cardImg;
	}
}


