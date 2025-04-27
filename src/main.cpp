#include "gamestate.cpp"
#include "raylib.h"
#include <iostream>

// class GUI {
//   private:
// 	sf::RenderWindow window;
// 	Board board;
// 	sf::Color emptyColor{50, 50, 50};
// 	sf::Color side1Color{255, 50, 50};
// 	sf::Color side2Color{50, 50, 255};
//
//   public:
// 	GUI()
// 	    : window(sf::RenderWindow(sf::VideoMode({600, 600}, sf::Style::None),
// 	                              "Game")),
// 	      board(Board()) {
//
// 		const auto s = window.getSize();
// 		std::cout << s.x << " " << s.y;
// 		// sf::FloatRect visibleArea({0, 0}, {(float)s.x, (float)s.y});
// 		sf::FloatRect visibleArea({0, 0}, {900, 1000});
// 		window.setView(sf::View(visibleArea));
// 	}
// 	void run() {
// 		sf::RectangleShape rect({50.f, 50.f});
// 		rect.setPosition({400.f, 400.f});
// 		rect.setFillColor(emptyColor);
//
// 		while (window.isOpen()) {
// 			while (const std::optional event = window.pollEvent()) {
// 				if (event->is<sf::Event::Closed>()) {
// 					window.close();
// 				} else if (const auto *mouseButtonPressed =
// 				               event->getIf<sf::Event::MouseButtonPressed>()) {
// 					if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
// 						const sf::Vector2i pos = sf::Mouse::getPosition(window);
// 						std::cout
// 						    << "mouse x: " << mouseButtonPressed->position.x
// 						    << std::endl;
// 						std::cout
// 						    << "mouse y: " << mouseButtonPressed->position.y
// 						    << std::endl;
// 						std::cout << "mouse x2: " << pos.x << std::endl;
// 						std::cout << "mouse y2: " << pos.y << std::endl;
// 						std::cout << window.getSize().x << " "
// 						          << window.getSize().y << std::endl;
// 						if (rect.getGlobalBounds().contains(
// 						        {(float)pos.x, (float)pos.y})) {
// 							rect.setFillColor(
// 							    sf::Color(rand() % 256, rand() % 256, 0));
// 						}
// 					} else if (const auto *resized =
// 					               event->getIf<sf::Event::Resized>()) {
// 						sf::FloatRect visibleArea(
// 						    {0, 0},
// 						    {(float)resized->size.x, (float)resized->size.y});
// 						window.setView(sf::View(visibleArea));
// 					}
// 				}
// 			}
//
// 			window.clear(sf::Color::Black);
// 			drawBoard();
// 			window.draw(rect);
// 			window.display();
// 		}
// 	}
// 	void drawBoard() {
// 		for (int row = 0; row < ROW_COUNT; row++) {
// 			for (int col = 0; col < COL_COUNT; col++) {
// 				sf::RectangleShape rect({50.f, 50.f});
// 				rect.setPosition({60.f * col + 100.f, 60.f * row + 100.f});
// 				switch (board.spaces[row][col]) {
// 				case SpacePlayer::Empty: {
// 					rect.setFillColor(emptyColor);
// 					break;
// 				}
// 				case SpacePlayer::Player1Side1: {
// 					rect.setFillColor(side1Color);
// 					break;
// 				}
// 				case SpacePlayer::Player1Side2: {
// 					rect.setFillColor(side2Color);
// 					break;
// 				}
// 				case SpacePlayer::Player2Side1: {
// 					rect.setFillColor(side1Color);
// 					break;
// 				}
// 				case SpacePlayer::Player2Side2: {
// 					rect.setFillColor(side2Color);
// 					break;
// 				}
// 				};
// 				window.draw(rect);
// 			}
// 		}
// 	}
// };

int screenWidth = 800;
int screenHeight = 450;

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void) {
	// Update
	//----------------------------------------------------------------------------------
	// TODO: Update your variables here
	//----------------------------------------------------------------------------------

	// Draw
	//----------------------------------------------------------------------------------
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("Congrats! You created your first window!", 190, 200, 20,
	         LIGHTGRAY);

	EndDrawing();
	//----------------------------------------------------------------------------------
}
int main() {

	// Initialization
	//--------------------------------------------------------------------------------------
	InitWindow(screenWidth, screenHeight,
	           "raylib [core] example - basic window");

	SetTargetFPS(60); // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		UpdateDrawFrame();
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow(); // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
	// GUI gui{};
	// gui.run();
	return 0;
}
