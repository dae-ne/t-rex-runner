#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

#include "animations.hpp"
#include "sprites.hpp"

namespace trex
{
    class Obstacle : public sf::Drawable
    {
    public:
        Obstacle(SpriteManager& spriteManager) : spriteManager(spriteManager) {}

        void update(int elapsedTime);
        float getPositionX() const { return position.x; }

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
            position.y += 2.f;
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
        ObstacleManager(SpriteManager& spriteManager, AnimationsManager& animationsManager)
            : spriteManager(spriteManager), animationsManager(animationsManager) {}

        void generateRandomObstacle();
        void popObstacle();

        void updateObstacles(int elapsedTime);
        void drawObstacles(sf::RenderTarget&);

    private:
        SpriteManager& spriteManager;
        AnimationsManager& animationsManager;

        std::queue<Obstacle*> obstacles;
    };
}
