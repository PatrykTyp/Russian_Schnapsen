#include "Triumph.h"

int Triumph::activeT = 0;
std::pair<std::pair<bool, int>, std::string> Triumph::tKing[4];
std::pair<std::pair<bool, int>, std::string> Triumph::tQueen[4];

void Triumph::isTriumph(Card playerDeck[]) {
	std::cout << "is triumph" << std::endl;
	for (int i = 0; i < 8; i++) {
		if (playerDeck[i].figure == "K") {
			if (playerDeck[i].color == "karo") {
				tKing[0].first.first = true;
				tKing[0].first.second = i;
			}
			else if (playerDeck[i].color == "kier") {
				tKing[1].first.first = true;
				tKing[1].first.second = i;
			}
			else if (playerDeck[i].color == "pik") {
				tKing[2].first.first = true;
				tKing[2].first.second = i;
			}
			else if (playerDeck[i].color == "trefl") {
				tKing[3].first.first = true;
				tKing[3].first.second = i;
			}
		}
		else if (playerDeck[i].figure == "Q") {
			if (playerDeck[i].color == "karo") {
				tQueen[0].first.first = true;
				tQueen[0].first.second = i;
			}
			else if (playerDeck[i].color == "kier") {
				tQueen[1].first.first = true;
				tQueen[1].first.second = i;
			}
			else if (playerDeck[i].color == "pik") {
				tQueen[2].first.first = true;
				tQueen[2].first.second = i;
			}
			else if (playerDeck[i].color == "trefl") {
				tQueen[3].first.first = true;
				tQueen[3].first.second = i;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		if (tKing[i].first.first == true && tQueen[i].first.first == true) {
			playerDeck[tKing[i].first.second].marriage = true;
			playerDeck[tQueen[i].first.second].marriage = true;
		}
	}
	for (int i = 0; i < 4; i++) {
		tKing[i].first.first = false;
		tQueen[i].first.first = false;
		tKing[i].first.second = 0;
		tQueen[i].first.second = 0;
	}
}
