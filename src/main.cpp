#include <SFML/Graphics.hpp>

int main() {
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