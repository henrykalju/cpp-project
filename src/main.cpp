#include "gamestate.cpp"
#include <SFML/Graphics.hpp>

class GUI {
  private:
	sf::RenderWindow window;
	Board board;

  public:
	GUI() : window(sf::RenderWindow(sf::VideoMode({600, 600}), "Game")) {}
	void run() {
		sf::RenderWindow window(sf::VideoMode({600, 600}), "SFML 3 Circle");

		while (window.isOpen()) {
			while (const std::optional event = window.pollEvent()) {
				if (event->is<sf::Event::Closed>()) {
					window.close();
				}
			}

			window.clear(sf::Color::White);
			drawBoard();
			window.display();
		}
	}
	void drawBoard() {
		for (int row = 0; row < ROW_COUNT - 2; row++) {
			for (int col = 0; col < COL_COUNT - 2; col++) {
				switch (board.spaces[row][col]) {
				case SpacePlayer::Empty: {
					sf::RectangleShape rect({10.f, 60.f});
					rect.setPosition({100.f, 100.f});
					rect.setFillColor(sf::Color::Black);
					window.draw(rect);
				}

				default:
					break;
				};
			}
		}
	}
};

int main() {

	GUI gui{};
	gui.run();
	return 0;
}
