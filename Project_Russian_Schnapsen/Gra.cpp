#include "Gra.h"

Gra::Gra() :
	window(sf::VideoMode(1200, 800), "Russian Schnapsen", sf::Style::Close | sf::Style::Resize),
	menu(window.getSize().x, window.getSize().y),
	rules(),
	windowFocus(0)
{
	view.setSize(sf::Vector2f(1200.0f, 800.0f));
	view.setCenter(sf::Vector2f(600.0f, 400.0f));

	tableTexture.loadFromFile("ex/image/plansza.png");
	
	Card::cardUsed.loadFromFile("ex/image/uzyta.png");
	Card::cardBack.loadFromFile("ex/image/tyl.png");
	Card::deckTexture.loadFromFile("ex/image/talia.png");

	table.setTexture(tableTexture);

	Card::loadCard(Players::deck);
	Card::assignImg(Players::deck);
	Card::setTextures();

	Move::init();
}


void Gra::start() {
	while (window.isOpen()) {
		course();
		draw();
	}
}

void Gra::course() {
	sf::Event ev;
	while (window.pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyReleased:
			/*
			* Okno menu
			*/
			if (windowFocus == 0) {
				switch (ev.key.code) {
				case sf::Keyboard::Down:
					menu.down();
					break;
				case sf::Keyboard::Up:
					menu.up();
					break;
				case sf::Keyboard::Return:
					switch (menu.getOption()) {
						/*
						* Przejœcie do gry w³aœciwej, rozdanie kart i zmiena t³a.
						*/
					case 0:
						windowFocus = 1;
						Card::reshuffleCard(Players::deck);
						Card::deal(Players::player1, Players::player2, Players::player3, Players::deck, Players::stock);
						cardPosition();
						//cardTurn();
						break;
						/*
						* Przejscie do zasad gry
						*/
					case 1:
						windowFocus = 2;
						break;
						/*
						* Wyjscie z gry
						*/
					case 2:
						window.close();
						break;
					}
				}
			}
			/*
			* Okno gry
			*/
			if (windowFocus == 1) {
				switch (ev.key.code) {
					/*
					* Powrót do menu
					*/
				case sf::Keyboard::Escape:
					//reset();
					windowFocus = 0;
					break;
				case sf::Keyboard::A:
					if (!Bidding::isBidding) {
						if (Move::getStock()) {
							stockToPlayers();
							Move::cardStockUsed[Move::cardStock] = Move::cardStock;
							if (Move::cardStock != 2) {
								Move::right();
							}
							else {
								Move::left();
							}
						}
						else {
							if (GameMechanics::throwCard) {
								if (GameMechanics::bidder == 1) {
									Move::choosenCard(player1[Move::getSelectedCard()]);
									GameMechanics::sendValues(player1[Move::getSelectedCard()], choosenByBot);
									Move::cardUsed[Move::getSelectedCard()] = Move::getSelectedCard();

									Move::right();

									GameMechanics::throwCard = false;
								}
								else if (GameMechanics::bidder == 2) {
									choosenByBot = GameMechanics::sendValuesBot(player2, GameMechanics::a);
									GameMechanics::bidder = 1;
								}
								else if (GameMechanics::bidder == 3) {
									choosenByBot = GameMechanics::sendValuesBot(player3, GameMechanics::b);
									GameMechanics::bidder = 1;
								}
							}
						}
					}
				case sf::Keyboard::Left:
					if (Move::isReset != 7 && !Bidding::isBidding )
						Move::left();
					break;
				case sf::Keyboard::Right:
					if (Move::isReset != 7 && !Bidding::isBidding)
						Move::right();
					break;
				case sf::Keyboard::L:
					if (Bidding::isBidding) {
						if (Bidding::whoWonBid <= 3 && Bidding::whoWonBid >= 1) {
							Bidding::bidding();
						}
						else{
							Bidding::checkBid();
							Bidding::whoWonBid = 1;
						}

					}
				case sf::Keyboard::Down:
					if (Bidding::isBidding) {
						Bidding::down();
					}
					break;
				case sf::Keyboard::Up:
					if (Bidding::isBidding) {
						Bidding::up();
					}
					break;
				}
			}
			if (windowFocus == 4) {
				switch (ev.key.code) {
				case sf::Keyboard::Escape:
					windowFocus = 0;
					//reset();
					break;
				case sf::Keyboard::Return:
					windowFocus = 0;
					//reset();
					break;
				default:
					break;
				}
			}
			/*
			* Ekran zasad
			*/
			if (windowFocus == 2) {
				switch (ev.key.code) {
				case sf::Keyboard::Escape:
					windowFocus = 0;
					rules.scrollReset();
					break;
				default:
					break;
				}
			}
			break;
			/*
			* W celu przesuniêcia ekranu nale¿y u¿yæ Scrolla na myszy
			*/
		case sf::Event::MouseWheelScrolled:
			if (windowFocus == 2) {
				if (ev.mouseWheelScroll.delta > 0) {
					rules.scrollUp();
				}
				else if (ev.mouseWheelScroll.delta < 0) {
					rules.scrollDown();
				}
			}
			break;
		default:
			break;
			}
		}
}

void Gra::draw() {
	window.clear();
	if (windowFocus == 0) {
		window.setView(view);
		menu.draw(window);
	}
	else if (windowFocus == 1) {
		window.setView(view);
		window.draw(table);
		if (!Bidding::isBidding) {
			window.draw(Move::chooseCard);
			if (Move::getStock()) {
				for (int i = 0; i < 3; i++)
					window.draw(Players::stock[i].cardImg);
			}
		}
		else {
			Bidding::draw(window);
		}
		for (int i = 0; i < 8; i++) {
			window.draw(Players::player1[i].cardImg);
			window.draw(Players::player2[i].cardImg);
			window.draw(Players::player3[i].cardImg);
		}
		
	}
	else if (windowFocus == 2) {
		rules.draw(window);
	}
	window.display();
}

void Gra::cardPosition() {
	for (int i = 0; i < 7; i++) {
		Players::player1[i].cardImg.setPosition(sf::Vector2f(72.0f + (97.5f * i), 79.0f));
		Players::player3[i].cardImg.setPosition(sf::Vector2f(1115.0f, 59.0f + (97.0f * i)));
		Players::player3[i].cardImg.setRotation(-90.0f);
		Players::player2[i].cardImg.setPosition(sf::Vector2f(72.0f + (97.5f * i), 721.0f));
	}
	for (int i = 0; i < 3; i++) {
		Players::stock[i].cardImg.setPosition(sf::Vector2f(490.0f + (114.0f * i), 400.0f));
	}
}

void Gra::cardTurn() {
	sf::Vector2u tylSize = Card::cardBack.getSize();
	tylSize.x /= 6;
	tylSize.y /= 4;
	int n = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			Players::player2[n].cardImg.setTexture(Card::cardBack);
			Players::player2[n].cardImg.setTextureRect(sf::IntRect(tylSize.x * j, tylSize.y * i, tylSize.x, tylSize.y));
			Players::player3[n].cardImg.setTexture(Card::cardBack);
			Players::player3[n].cardImg.setTextureRect(sf::IntRect(tylSize.x * j, tylSize.y * i, tylSize.x, tylSize.y));
			if (n == 6)
				break;
			else
				n++;
		}
	}
}

void Gra::oneCardBack(Card& card) {
	sf::Vector2u size = Card::cardBack.getSize();
	size.x /= 6;
	size.y /= 4;
	int x = card.value % 6;
	int y = card.value / 6;

	card.cardImg.setTexture(Card::cardBack);
	card.cardImg.setTextureRect(sf::IntRect(size.x * x, size.y * y, size.x, size.y));
}

void Gra::oneCardFront(Card& card) {
	sf::Vector2u size = Card::deckTexture.getSize();
	size.x /= 6;
	size.y /= 4;
	int x = card.value % 6;
	int y = card.value / 6;

	card.cardImg.setTexture(Card::deckTexture);
	card.cardImg.setTextureRect(sf::IntRect(size.x * x, size.y * y, size.x, size.y));
}

void Gra::reset() {
	/*if (doResetuZostalo == 8 || czyReset == true) {
		tmp = 0;
		przyznanyMusik = 0;
		licytacjaJa = 0;
		licytacjaBot2 = 0;
		licytacjaBot3 = 0;
		czyMusik = true;
		czyLicytacja = true;
		musikCzyNie = true;
		wystawienie = true;
		poprzednia1 = nullptr;
		poprzednia2 = nullptr;
		poprzednia3 = nullptr;
		czyJaProwadze.first = true;
		czyJaProwadze.second = true;
		gracz1[7].card.setPosition(sf::Vector2f(-100.0f, -100.0f));
		gracz2[7].card.setPosition(sf::Vector2f(-100.0f, -100.0f));
		gracz3[7].card.setPosition(sf::Vector2f(-100.0f, -100.0f));
		wybierzKarte.setPosition(sf::Vector2f(490.0f, 470.0f));
		doResetuZostalo = 0;
		prowadziGracz = 1;
		if (czyReset == true) {
			cout << "RESET JEST KURNA TRU" << endl;
			pkt1 = 0;
			pkt2 = 0;
			pkt3 = 0;
			punkty = 0;
			pkt1tmp = 0;
			pkt2tmp = 0;
			pkt3tmp = 0;
			punkty1.setString(to_string(pkt1));
			punkty2.setString(to_string(pkt2));
			punkty3.setString(to_string(pkt3));
		}
		for (int i = 0; i < 8; i++) {
			kartyUzyte[i] = -1;
			gracz1[i].uzyta = false;
			gracz2[i].uzyta = false;
			gracz3[i].uzyta = false;
		}
		for (int i = 0; i < 3; i++)
			kartyUzyteMusik[i] = -1;
		for (int i = 0; i < 4; i++) {
			meldunekKrole[i].first.first = false;
			meldunekKrole[i].first.second = 0;
			meldunekKrolowe[i].first.first = false;
			meldunekKrolowe[i].first.second = 0;
			jakiMeldunek1[i] = false;
			jakiMeldunek2[i] = false;
			jakiMeldunek3[i] = false;
		}
		licytacja.reset();
		przetasujKarty(talia);
		rozdanie(gracz1, gracz2, gracz3, talia, musik);
		pozycjaKart();
		tylKart();
		wygrywaLicytacje.setString("");
		czyReset = false;
	}*/
}