#include <iostream>
#include <SFML/Graphics.hpp>

#include "Dinosaur.hpp"
#include "Obstacles.hpp"
#include "Textures.hpp"

int main()
{
    auto window = sf::RenderWindow({ 600u, 200u }, "T-Rex Runner", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    auto texturesManager = trex::TexturesManager::getInstance();

    if (!texturesManager->loadFiles())
    {
        std::cerr << "Failed to load textures\n";
        exit(1);
    }

    auto trexTexture      = texturesManager->getTrexTexture();
    auto obstaclesTexture = texturesManager->getObstaclesTexture();
    
    auto dinosaur         = trex::Dinosaur(trexTexture);
    auto obstaclesManager = trex::ObstacleManager(obstaclesTexture);
    auto clock            = sf::Clock();

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

        auto elapsedTime = clock.getElapsedTime().asMilliseconds();
        dinosaur.update(elapsedTime);
        obstaclesManager.updateObstacles(elapsedTime);

        window.clear(sf::Color::Red);
        window.draw(dinosaur);
        obstaclesManager.drawObstacles(window);
        window.display();
    }
}
