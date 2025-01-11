#include "obstacles.hpp"

void trex::Obstacle::update(int elapsedTime)
{
    position.x -= 2.0f;
}

void trex::ObstacleSmallCactus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    spriteManager.setSprite(SpriteManager::SpriteType::SmallCactus, position);
    target.draw(spriteManager.getSprite());
}

void trex::ObstacleLargeCactus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    spriteManager.setSprite(SpriteManager::SpriteType::LargeCactus, position);
    target.draw(spriteManager.getSprite());
}

void trex::ObstacleBird::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    auto spriteType = animationsManager.getCurrentFrame() > animationsManager.getFramesNumber() / 2
        ? SpriteManager::SpriteType::BirdAnimation1
        : SpriteManager::SpriteType::BirdAnimation2;
    
    spriteManager.setSprite(spriteType, position);
    target.draw(spriteManager.getSprite());
}

void trex::ObstacleManager::generateRandomObstacle()
{
    int selection = rand() % 3;

    switch (selection)
    {
    case 0:
        obstacles.push(new ObstacleSmallCactus(spriteManager));
        break;
    case 1:
        obstacles.push(new ObstacleLargeCactus(spriteManager));
        break;
    case 2:
        obstacles.push(new ObstacleBird(spriteManager, animationsManager));
        break;
    }
}

void trex::ObstacleManager::popObstacle()
{
    delete obstacles.front();
    obstacles.pop();
}

void trex::ObstacleManager::updateObstacles(int elapsedTime)
{
    if (obstacles.empty())
    {
        generateRandomObstacle();
        return;
    }

    if (elapsedTime % 1000 < 10)
    {
        generateRandomObstacle();
    }

    for (size_t i = 0; i < obstacles.size(); i++)
    {
        auto obstacle = obstacles.front();
        obstacles.pop();
        obstacle->update(elapsedTime);
        obstacles.push(obstacle);
    }

    if (obstacles.front()->getPositionX() < 50.f)
    {
        popObstacle();
    }
}

void trex::ObstacleManager::drawObstacles(sf::RenderTarget& target)
{
    for (size_t i = 0; i < obstacles.size(); i++)
    {
        auto obstacle = obstacles.front();
        obstacles.pop();
        target.draw(*obstacle);
        obstacles.push(obstacle);
    }
}
