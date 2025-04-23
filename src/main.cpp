#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    std::cout << "hello" << std::endl;
    sf::RenderWindow window(sf::VideoMode(600, 600), "Test");

    sf::CircleShape circle(200);
    circle.setFillColor(sf::Color::Black);
    circle.setPosition(100, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        window.draw(circle);

        window.display();
    }

    return 0;
}