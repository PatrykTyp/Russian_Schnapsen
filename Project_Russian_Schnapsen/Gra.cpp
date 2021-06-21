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
	winTexture.loadFromFile("ex/image/win.png");
	loseTexture.loadFromFile("ex/image/lose.png");
	
	Card::cardUsed.loadFromFile("ex/image/uzyta.png");
	Card::cardBack.loadFromFile("ex/image/tyl.png");
	Card::deckTexture.loadFromFile("ex/image/talia.png");
	font.loadFromFile("ex/font/sansation.ttf");

	table.setTexture(tableTexture);
	win.setTexture(winTexture);
	lose.setTexture(loseTexture);

	Card::loadCard(Players::deck);
	Card::assignImg(Players::deck);
	Card::setTextures();

	pressAToContinue.setFont(font);
	pressAToContinue.setFillColor(sf::Color::Green);
	pressAToContinue.setCharacterSize(36);
	pressAToContinue.setString("Wcisnij A by kontynuowac!");
	pressAToContinue.setPosition(sf::Vector2f(300.0f, 550.0f));


	Move::init();
	Points::init();
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
					case 0:
						windowFocus = 1;
						Card::reshuffleCard(Players::deck);
						Card::deal(Players::player1, Players::player2, Players::player3, Players::deck, Players::stock);
						cardPosition();
						cardTurn();
						break;
					case 1:
						windowFocus = 2;
						break;
					case 2:
						window.close();
						break;
					}
				}
			}
			if (windowFocus == 1) {
				switch (ev.key.code) {
				case sf::Keyboard::Escape:
					reset();
					windowFocus = 0;
					break;
				case sf::Keyboard::A:
					std::cout << "is Bidding: " << Bidding::isBidding << "        throwCard: " << GameMechanics::throwCard << std::endl;
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
									if (Bidding::reset != 7) {
										Move::right();
									}

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
							else {
								GameMechanics::removeCard();
								GameMechanics::throwCard = true;

								Points::winP1 = 0;
								Points::winP2 = 0;
								Points::winP3 = 0;

								Bidding::reset++;
								std::cout << Bidding::reset << std::endl;
								std::cout << Bidding::isReset << std::endl;
								reset();
							}
						}
					}
					if (Bidding::end) {
						windowFocus = 4;
					}
					break;
				case sf::Keyboard::R:
					std::cout << "Wykonuje sie RRRRRRRRawr" << std::endl;
					Bidding::isReset = true;
					reset();
					break;
				case sf::Keyboard::Left:
					if (Bidding::reset != 7 && !Bidding::isBidding )
						Move::left();
					break;
				case sf::Keyboard::Right:
					if (Bidding::reset != 7 && !Bidding::isBidding)
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
					reset();
					break;
				case sf::Keyboard::Return:
					windowFocus = 0;
					reset();
					break;
				default:
					break;
				}
			}
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
	
		if (!GameMechanics::throwCard) {
			window.draw(pressAToContinue);
		}
		window.draw(Points::pointsTextP1);
		window.draw(Points::pointsTextP2);
		window.draw(Points::pointsTextP3);
		
	}
	else if (windowFocus == 2) {
		rules.draw(window);
	}
	else if (windowFocus == 4) {
		if (Bidding::iWin) {
			window.draw(win);
		}
		else {
			window.draw(lose);
		}
	}
	window.display();
}

void Gra::cardPosition() {
	std::cout << "Card position" << std::endl;
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
	std::cout << "Card turn" << std::endl;
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
	std::cout << "Card 1 turn" << std::endl;
	sf::Vector2u size = Card::cardBack.getSize();
	size.x /= 6;
	size.y /= 4;
	int x = card.value % 6;
	int y = card.value / 6;

	card.cardImg.setTexture(Card::cardBack);
	card.cardImg.setTextureRect(sf::IntRect(size.x * x, size.y * y, size.x, size.y));
}

void Gra::oneCardFront(Card& card) {
	std::cout << "Card return" << std::endl;
	sf::Vector2u size = Card::deckTexture.getSize();
	size.x /= 6;
	size.y /= 4;
	int x = card.value % 6;
	int y = card.value / 6;

	card.cardImg.setTexture(Card::deckTexture);
	card.cardImg.setTextureRect(sf::IntRect(size.x * x, size.y * y, size.x, size.y));
}

void Gra::reset() {
	std::cout << "RESET" << std::endl;
	if (Bidding::reset == 8 || Bidding::isReset == true) {
		Stock::intStock = 1;
		Bidding::biddingP1 = 0;
		Bidding::biddingP2 = 0;
		Bidding::biddingP3 = 0;
		Move::isStock = true;
		Bidding::isBidding = true;
		GameMechanics::throwCard = true;
		GameMechanics::previousCardP1Ptr = nullptr;
		GameMechanics::previousCardP2Ptr = nullptr;
		GameMechanics::previousCardP3Ptr = nullptr;
		GameMechanics::whoFirst.first = true;
		GameMechanics::whoFirst.second = true;
		player1[7].cardImg.setPosition(sf::Vector2f(-100.0f, -100.0f));
		player2[7].cardImg.setPosition(sf::Vector2f(-100.0f, -100.0f));
		player3[7].cardImg.setPosition(sf::Vector2f(-100.0f, -100.0f));
		Move::chooseCard.setPosition(sf::Vector2f(490.0f, 470.0f));
		Bidding::reset = 0;
		GameMechanics::bidder = 1;
		if (Bidding::isReset == true) {
			Points::pointsP1 = 0;
			Points::pointsP2 = 0;
			Points::pointsP3 = 0;
			Points::pointsP1tmp = 0;
			Points::pointsP2tmp = 0;
			Points::pointsP3tmp = 0;
			Points::pointsTextP1.setString(std::to_string(Points::pointsP1));
			Points::pointsTextP2.setString(std::to_string(Points::pointsP2));
			Points::pointsTextP3.setString(std::to_string(Points::pointsP3));
		}
		for (int i = 0; i < 8; i++) {
			Move::cardUsed[i] = -1;
			player1[i].use = false;
			player2[i].use = false;
			player3[i].use = false;
		}
		for (int i = 0; i < 3; i++)
			Move::cardStockUsed[i] = -1;
		for (int i = 0; i < 4; i++) {
			Triumph::tKing[i].first.first = false;
			Triumph::tKing[i].first.second = 0;
			Triumph::tQueen[i].first.first = false;
			Triumph::tQueen[i].first.second = 0;
		}
		Bidding::resetAll();
		Bidding::circle1.setFillColor(sf::Color::Green);
		Bidding::circle2.setFillColor(sf::Color::Green);
		Bidding::circle3.setFillColor(sf::Color::Green);

		Card::reshuffleCard(deck);
		Card::deal(player1, player2, player3, deck, stock);
		cardPosition();
		cardTurn();
		Bidding::bidWin.setString("");
		Bidding::isReset = false;
	}
}