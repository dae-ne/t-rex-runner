#include "obstacles.hpp"

void Obstacle::update(GameState& gameState)
{
    if (gameState.getState() != GameState::State::Running)
        return;

    position.x -= 8.f;
}

void Obstacle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    spriteManager.setSprite(currentSprite, position);
    target.draw(spriteManager.getSprite());
}

ObstacleSmallCactus::ObstacleSmallCactus(SpriteManager& spriteManager)
    : Obstacle(spriteManager)
{
    currentSprite = SpriteType::SmallCactus;
}

ObstacleLargeCactus::ObstacleLargeCactus(SpriteManager& spriteManager)
    : Obstacle(spriteManager)
{
    currentSprite = SpriteType::LargeCactus;
    position.y += 2.f; // adding 2 pixels offset to level the cactus with the ground
}

ObstacleBird::ObstacleBird(SpriteManager& spriteManager)
    : Obstacle(spriteManager)
{
    currentSprite = SpriteType::BirdAnimation1;
}

void ObstacleBird::update(GameState& gameState)
{
    Obstacle::update(gameState);

    currentSprite = gameState.getCurrentFrameNumber() > gameState.getTotalNumberOfFrames() / 2
        ? SpriteType::BirdAnimation1
        : SpriteType::BirdAnimation2;
}

ObstacleManager::ObstacleManager(SpriteManager& spriteManager)
    : spriteManager(spriteManager)
{
    smallCactusSize = spriteManager.getSize(SpriteType::SmallCactus);
    largeCactusSize = spriteManager.getSize(SpriteType::LargeCactus);
    birdSize = spriteManager.getSize(SpriteType::BirdAnimation1);
}

ObstacleManager::~ObstacleManager()
{
    removeAllObstacles();
}

void ObstacleManager::generateRandomObstacle()
{
    switch (rand() % 3)
    {
    case 0:
        obstacles.push(new ObstacleSmallCactus(spriteManager));
        break;
    case 1:
        obstacles.push(new ObstacleLargeCactus(spriteManager));
        break;
    case 2:
        obstacles.push(new ObstacleBird(spriteManager));
        break;
    }
}

void ObstacleManager::popObstacle()
{
    delete obstacles.front();
    obstacles.pop();
}

void ObstacleManager::removeAllObstacles()
{
    for (size_t i = 0; i < obstacles.size(); i++)
        popObstacle();
}

void ObstacleManager::updateObstacles(GameState& gameState)
{
    if (gameState.getState() == GameState::State::Start)
    {
        removeAllObstacles();
        timeElapsedSinceLastObstacleMs = 0;
        return;
    }

    auto elapsedTime = gameState.getInGameTimeMs();

    if (elapsedTime - timeElapsedSinceLastObstacleMs > 5000)
    {
        generateRandomObstacle();
        timeElapsedSinceLastObstacleMs = elapsedTime;
    }

    if (obstacles.empty())
        return;

    for (size_t i = 0; i < obstacles.size(); i++)
    {
        auto obstacle = obstacles.front();
        obstacles.pop();
        obstacle->update(gameState);
        obstacles.push(obstacle);
    }

    if (obstacles.front()->getPosition().x < -200.f)
    {
        popObstacle();
    }
}

void ObstacleManager::drawObstacles(sf::RenderTarget& target)
{
    for (size_t i = 0; i < obstacles.size(); i++)
    {
        auto obstacle = obstacles.front();
        obstacles.pop();
        target.draw(*obstacle);
        obstacles.push(obstacle);
    }
}

bool ObstacleManager::isColliding(sf::FloatRect boundingBox)
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
