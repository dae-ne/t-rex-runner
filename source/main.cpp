#include <iostream>
#include <SFML/Graphics.hpp>

#include "dinosaur.hpp"
#include "hud.hpp"
#include "obstacles.hpp"
#include "sprites.hpp"
#include "state.hpp"

int main()
{
    auto window = sf::RenderWindow({ 600u, 200u }, "T-Rex Runner",
        sf::Style::Titlebar | sf::Style::Close);
        
    window.setFramerateLimit(60);

    auto spriteManager = trex::SpriteManager();
    auto hud = trex::HUD();

    if (!spriteManager.loadTextureFromFile())
    {
        std::cerr << "Failed to load texture\n";
        exit(1);
    }

    if (!hud.loadFontFromFile())
    {
        std::cerr << "Failed to load font\n";
        exit(1);
    }
    
    auto dinosaur = trex::Dinosaur(spriteManager);
    auto obstaclesManager = trex::ObstacleManager(spriteManager);

    auto gameState = trex::GameState();

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Space &&
                gameState.getState() == trex::GameState::State::Start)
            {
                gameState.setState(trex::GameState::State::Running);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            dinosaur.jump();
        }

        gameState.update();
        dinosaur.update(gameState);
        obstaclesManager.updateObstacles(gameState);
        hud.update(gameState);

        if (obstaclesManager.isColliding(dinosaur.getBoundingBox()))
            gameState.setState(trex::GameState::State::Dead);

        window.clear(sf::Color::Red);
        obstaclesManager.drawObstacles(window);
        window.draw(dinosaur);
        window.draw(hud);
        window.display();
    }
}
