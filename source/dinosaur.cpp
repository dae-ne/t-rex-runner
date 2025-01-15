#include "dinosaur.hpp"

trex::Dinosaur::Dinosaur(SpriteManager& spriteManager)
    : spriteManager(spriteManager)
{
    size = spriteManager.getSize(SpriteType::DinosaurStanding);
}

void trex::Dinosaur::jump()
{
    if (currentJumpHight > 0.f)
        return;

    currentJumpSpeed = 10.f;
}

void trex::Dinosaur::update(GameState& gameState)
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
    position.y = TREX_MIN_Y_POSITION - currentJumpHight;

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

sf::FloatRect trex::Dinosaur::getBoundingBox() const
{
    return { position, size };
}

void trex::Dinosaur::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    spriteManager.setSprite(currentSprite, position);
    target.draw(spriteManager.getSprite());
}

void trex::Dinosaur::resetPosition()
{
    currentJumpSpeed = 0.f;
    currentJumpHight = 0.f;
    position.y = TREX_MIN_Y_POSITION;
}
