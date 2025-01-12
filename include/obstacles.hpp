#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

#include "animations.hpp"
#include "sprites.hpp"

namespace trex {

class Obstacle : public sf::Drawable
{
public:
    Obstacle(SpriteManager& spriteManager) : spriteManager(spriteManager) {}

    void update(int elapsedTime);
    sf::Vector2f getPosition() const { return position; }

protected:
    sf::Vector2f position = { 600.f, 180.f };

    SpriteManager& spriteManager;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const = 0;
};

class ObstacleSmallCactus : public Obstacle
{
public:
    ObstacleSmallCactus(SpriteManager& spriteManager) : Obstacle(spriteManager) {}

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

class ObstacleLargeCactus : public Obstacle
{
public:
    ObstacleLargeCactus(SpriteManager& spriteManager) : Obstacle(spriteManager)
    {
        position.y += 2.f; // adding 2 pixels offset to level the cactus with the ground
    }

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

class ObstacleBird : public Obstacle
{
public:
    ObstacleBird(SpriteManager& spriteManager, AnimationsManager& animationsManager)
        : Obstacle(spriteManager), animationsManager(animationsManager) {}

private:
    AnimationsManager& animationsManager;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

class ObstacleManager
{
public:
    ObstacleManager(SpriteManager&, AnimationsManager&);

    void generateRandomObstacle();
    void popObstacle();

    void updateObstacles(int elapsedTime);
    void drawObstacles(sf::RenderTarget&);

    bool isColliding(sf::FloatRect boundingBox);

private:
    int timeElapsedSinceLastObstacle = -4000;

    sf::Vector2f smallCactusSize;
    sf::Vector2f largeCactusSize;
    sf::Vector2f birdSize;

    SpriteManager& spriteManager;
    AnimationsManager& animationsManager;

    std::queue<Obstacle*> obstacles;
};

}
