#include <iostream>
#include <SFML/Graphics.hpp>

#include "animations.hpp"
#include "dinosaur.hpp"
#include "obstacles.hpp"
#include "sprites.hpp"

int main()
{
    auto window = sf::RenderWindow({ 600u, 200u }, "T-Rex Runner", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    auto spriteManager = trex::SpriteManager();
    auto animationsManager = trex::AnimationsManager(8, 100);

    if (!spriteManager.loadTextureFromFile())
    {
        std::cerr << "Failed to load texture\n";
        exit(1);
    }
    
    auto dinosaur = trex::Dinosaur(spriteManager, animationsManager);
    auto obstaclesManager = trex::ObstacleManager(spriteManager, animationsManager);
    auto clock = sf::Clock();

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
        animationsManager.update(elapsedTime);
        dinosaur.update(elapsedTime);
        obstaclesManager.updateObstacles(elapsedTime);

        window.clear(sf::Color::Red);
        window.draw(dinosaur);
        obstaclesManager.drawObstacles(window);
        window.display();
    }
}
