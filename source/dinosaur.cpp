#include "dinosaur.hpp"

Dinosaur::Dinosaur(Config& config, SpriteManager& spriteManager)
    : MinYPosition(config.GroundYPosition)
    , InitialJumpSpeed(config.InitialJumpSpeed)
    , GravitationalAcceleration(config.GravitationalAcceleration)
    , spriteManager(spriteManager)
{
    position = { config.DinosaurXPosition, config.GroundYPosition };
    size = spriteManager.getSize(SpriteType::DinosaurStanding);
}

void Dinosaur::jump()
{
    if (currentJumpHight > 0.f)
        return;

    currentJumpSpeed = InitialJumpSpeed;
}

void Dinosaur::update(GameState& gameState)
{
    auto state = gameState.getState();

    if (state == GameState::State::Start)
    {
        resetPosition();
        currentSprite = SpriteType::DinosaurStanding;
        return;
    }

    if (state == GameState::State::Dead)
    {
        currentSprite = SpriteType::DinosaurStanding;
        return;
    }

    currentJumpHight += currentJumpSpeed;
    position.y = MinYPosition - currentJumpHight;

    if (currentJumpHight > 0.f)
    {
        currentJumpSpeed -= 0.4f;
        currentSprite = SpriteType::DinosaurStanding;
        return;
    }

    resetPosition();

    currentSprite = gameState.getCurrentFrameNumber() % 2 == 0
        ? SpriteType::DinosaurRunningAnimation1
        : SpriteType::DinosaurRunningAnimation2;
}

sf::FloatRect Dinosaur::getBoundingBox() const
{
    return { position, size };
}

void Dinosaur::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    spriteManager.setSprite(currentSprite, position);
    target.draw(spriteManager.getSprite());
}

void Dinosaur::resetPosition()
{
    currentJumpSpeed = 0.f;
    currentJumpHight = 0.f;
    position.y = MinYPosition;
}
