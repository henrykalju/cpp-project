#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>

int main() {
    sf::RenderWindow window(sf::VideoMode({600, 400}), "SFML 3 Circle");

    // Create a circle shape
    sf::CircleShape circle(100.f); // radius
    circle.setFillColor(sf::Color::White);
    circle.setPosition({200.f, 150.f}); // x, y

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}