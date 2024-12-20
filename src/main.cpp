#include <iostream>
#include <SFML/Graphics.hpp>

#include "Dinosaur.h"

int main()
{
    auto window = sf::RenderWindow({ 800u, 600u }, "SFML Simple Game");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            std::cout << "jump\n";
        }

        auto dinosaur = Dinosaur();

        window.clear(sf::Color::White);
        window.draw(dinosaur);
        window.display();
    }
}
