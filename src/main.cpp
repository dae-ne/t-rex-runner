#include <iostream>
#include <SFML/Graphics.hpp>

#include "Dinosaur.hpp"

int main()
{
    auto window = sf::RenderWindow({ 800u, 600u }, "SFML Simple Game");
    window.setFramerateLimit(60);

    auto dinosaur = trex::Dinosaur();

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            dinosaur.jump();
        }

        dinosaur.update();

        window.clear(sf::Color::White);
        window.draw(dinosaur);
        window.display();
    }
}
