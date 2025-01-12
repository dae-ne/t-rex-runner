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
    auto isRunning = true;

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

        if (!isRunning)
        {
            clock.restart();
            continue;
        }

        auto elapsedTime = clock.getElapsedTime().asMilliseconds();

        animationsManager.update(elapsedTime);
        dinosaur.update(elapsedTime);
        obstaclesManager.updateObstacles(elapsedTime);

        isRunning = !obstaclesManager.isColliding(dinosaur.getBoundingBox());

        window.clear(sf::Color::Red);
        obstaclesManager.drawObstacles(window);
        window.draw(dinosaur);
        window.display();
    }
}
