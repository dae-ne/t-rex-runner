#include "Obstacles.hpp"

trex::Obstacle::Obstacle(sf::Texture& texture)
{
    sprite.setTexture(texture);
    sprite.setPosition({ 600.f, 180.f });
}

void trex::Obstacle::update(int elapsedTime)
{
    sprite.move(-2.f, 0.f);
}

float trex::Obstacle::getXPosition() const
{
    return sprite.getPosition().x;
}

void trex::Obstacle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}

trex::ObstacleSmallCactus::ObstacleSmallCactus(sf::Texture& texture)
    : Obstacle(texture)
{
    sprite.setTextureRect({ 92, 0, 17, 35 });
    sprite.setOrigin({ 0.f,  sprite.getGlobalBounds().height });
}

trex::ObstacleLargeCactus::ObstacleLargeCactus(sf::Texture& texture)
    : Obstacle(texture)
{
    sprite.setTextureRect({ 109, 0, 25, 50 });
    sprite.setOrigin({ 0.f,  sprite.getGlobalBounds().height });
    sprite.move(0.f, 2.f);
}

trex::ObstacleBird::ObstacleBird(sf::Texture& texture)
    : Obstacle(texture)
{
    sprite.setTextureRect({ 0, 0, 46, 39 });
    sprite.setOrigin({ 0.f,  sprite.getGlobalBounds().height });
}

void trex::ObstacleBird::update(int elapsedTime)
{
    trex::Obstacle::update(elapsedTime);
}

trex::ObstacleManager::ObstacleManager(sf::Texture& texture)
{
    this->texture = texture;
}

void trex::ObstacleManager::generateRandomObstacle()
{
    int selection = rand() % 3;

    switch (selection)
    {
    case 0:
        obstacles.push(new ObstacleSmallCactus(texture));
        break;
    case 1:
        obstacles.push(new ObstacleLargeCactus(texture));
        break;
    case 2:
        obstacles.push(new ObstacleBird(texture));
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

    if (obstacles.front()->getXPosition() < 50.0f)
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
