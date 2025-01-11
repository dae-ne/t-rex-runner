#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

namespace trex
{
    class Obstacle : public sf::Drawable
    {
    public:
        Obstacle(sf::Texture&);

        virtual void update(int elapsedTime);
        float getXPosition() const;

    protected:
        sf::Sprite sprite;

        void draw(sf::RenderTarget&, sf::RenderStates) const;
    };

    class ObstacleSmallCactus : public Obstacle
    {
    public:
        ObstacleSmallCactus(sf::Texture&);
    };

    class ObstacleLargeCactus : public Obstacle
    {
    public:
        ObstacleLargeCactus(sf::Texture&);
    };

    class ObstacleBird : public Obstacle
    {
    public:
        ObstacleBird(sf::Texture&);

        void update(int elapsedTime) override;
    };

    class ObstacleManager
    {
    public:
        ObstacleManager(sf::Texture&);

        void generateRandomObstacle();
        void popObstacle();

        void updateObstacles(int elapsedTime);
        void drawObstacles(sf::RenderTarget&);

    private:
        sf::Texture texture;
        std::queue<Obstacle*> obstacles;
    };
}