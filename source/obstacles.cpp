#include "obstacles.hpp"

void trex::Obstacle::update(int elapsedTime)
{
    position.x -= 4.0f;
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

trex::ObstacleManager::ObstacleManager(SpriteManager& spriteManager, AnimationsManager& animationsManager)
    : spriteManager(spriteManager), animationsManager(animationsManager)
{
    auto sprite = spriteManager.getSprite();
    auto globalBounds = sf::FloatRect();
    auto vectorZero = sf::Vector2f();

    spriteManager.setSprite(SpriteManager::SpriteType::SmallCactus, vectorZero);
    globalBounds = sprite.getGlobalBounds();
    smallCactusSize = globalBounds.getSize();

    spriteManager.setSprite(SpriteManager::SpriteType::LargeCactus, vectorZero);
    globalBounds = sprite.getGlobalBounds();
    largeCactusSize = globalBounds.getSize();

    spriteManager.setSprite(SpriteManager::SpriteType::BirdAnimation1, vectorZero);
    globalBounds = sprite.getGlobalBounds();
    birdSize = globalBounds.getSize();
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
    if (elapsedTime - timeElapsedSinceLastObstacle > 5000)
    {
        generateRandomObstacle();
        timeElapsedSinceLastObstacle = elapsedTime;
    }

    if (obstacles.empty())
        return;

    for (size_t i = 0; i < obstacles.size(); i++)
    {
        auto obstacle = obstacles.front();
        obstacles.pop();
        obstacle->update(elapsedTime);
        obstacles.push(obstacle);
    }

    if (obstacles.front()->getPosition().x < -200.f)
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

bool trex::ObstacleManager::isColliding(sf::FloatRect boundingBox)
{
    if (obstacles.empty())
        return false;

    auto obstacle = obstacles.front();
    auto position = obstacle->getPosition();
    auto size = sf::Vector2f();

    if (typeid(*obstacle) == typeid(ObstacleBird))
        size = birdSize;
    else if (typeid(*obstacle) == typeid(ObstacleSmallCactus))
        size = smallCactusSize;
    else if (typeid(*obstacle) == typeid(ObstacleLargeCactus))
        size = largeCactusSize;
    else
        return false;

    auto obstacleBoundingBox = sf::FloatRect(position, size);
    return obstacleBoundingBox.intersects(boundingBox);
}
