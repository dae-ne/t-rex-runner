#include <iostream>
#include <SFML/Graphics.hpp>

#include "Dinosaur.hpp"

int main()
{
    auto window = sf::RenderWindow({ 800u, 600u }, "SFML Simple Game");
    window.setFramerateLimit(60);

    auto textures = sf::Texture();

    if (!textures.loadFromFile("assets/textures.png"))
    {
        std::cout << "Error while loading textures!\n";
        exit(1);
    }

    auto dinosaur = trex::Dinosaur(textures);

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

        window.clear(sf::Color::Red);
        window.draw(dinosaur);
        window.display();
    }
}
