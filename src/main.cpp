#include <SFML/Graphics.hpp>
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

	return 0;

	sf::RenderWindow window(sf::VideoMode({600, 600}), "SFML 3 Circle");

	// Create a circle shape
	sf::CircleShape circle(200.f); // radius
	circle.setFillColor(sf::Color::Black);
	circle.setPosition({100.f, 100.f}); // x, y

	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear(sf::Color::White);
		window.draw(circle);
		window.display();
	}

	return 0;
}
