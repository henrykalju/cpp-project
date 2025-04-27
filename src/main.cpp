#include <iostream>
#include "gamestate.cpp"

void drawBoard(Board b) {
	std::cout << "---------" << std::endl;
	for (int row = 0; row < ROW_COUNT; row++) {
		std::cout << "|";
		for (int col = 0; col < COL_COUNT; col++) {
			std::cout << b.GetSpace({.row = row, .col = col}) << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "---------" << std::endl;
};

int main() {
	Board b;

	std::cout << "0 tähistab tühja ruutu. 1 ja 2 tähistavad mängija 1 nuppude külgi 1 ja 2. 3 ja 4 tähistavad mängija 2 külgi 1 ja 2." << std::endl;
	std::cout << "Mängija 1 alustab" << std::endl;

	while (b.GetWinner() == Winner::None) {
		drawBoard(b);
		
		auto c = b.GetEmptySpaces();
		std::cout << "Empty spaces - ";
		for (size_t i = 0; i < c.size(); i++) {
			std::cout << c.at(i).row << "," << c.at(i).col << " ";
		}
		std::cout << std::endl;
	
		int row, col, side;
		SpacePlayer t;

		do {
			std::cout << "Enter [row] [col] [side(1 or 2)]: ";
			std::cin >> row;
			std::cin >> col;
			std::cin >> side;

			t = b.Turn == Player::Player1 ? (side == 1 ? Player1Side1 : Player1Side2) : (side == 1 ? Player2Side1 : Player2Side2);
		} while (!b.Place({.row = row, .col = col}, t) && std::cout << "Try again" << std::endl);
		
		drawBoard(b);
		std::cout << "Nüüd on mängija " << (b.Turn == Player::Player1 ? "1" : "2") << " kord" << std::endl;
		c = b.GetTurnableSpaces();
		std::cout << "Turnable spaces - ";
		for (size_t i = 0; i < c.size(); i++) {
			std::cout << c.at(i).row << "," << c.at(i).col << " ";
		}
		std::cout << std::endl;

		Direction d;
		do {
			std::cout << "Enter [row] [col] [side(1 - UP, 2 - DOWN, 3 - LEFT, 4 - RIGHT)]: ";
			std::cin >> row;
			std::cin >> col;
			std::cin >> side;

			switch (side)
			{
			case 1:
				d = Up;
				break;
			case 2:
				d = Down;
				break;
			case 3:
				d = Left;
				break;
			case 4:
				d = Right;
				break;
			
			default:
				break;
			}
		} while (!b.Flip({row, col}, d) && std::cout << "Try again" << std::endl);
	}

	std::string winner;
	switch (b.GetWinner())
	{
	case Winner::Tie:
		winner = "viik";
		break;
	case Winner::Player1:
		winner = "mängija 1";
		break;
	case Winner::Player2:
		winner = "mängija 2";
		break;
	default:
		break;
	}
	std::cout << "Võitja on: " << winner << std::endl;

	return 0;
}
