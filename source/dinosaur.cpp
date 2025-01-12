#include "dinosaur.hpp"

trex::Dinosaur::Dinosaur(SpriteManager& spriteManager, AnimationsManager& animationsManager)
    : spriteManager(spriteManager), animationsManager(animationsManager)
{
    spriteManager.setSprite(SpriteManager::SpriteType::DinosaurStanding, position);
    auto globalBounds = spriteManager.getSprite().getGlobalBounds();
    size = { globalBounds.width, globalBounds.height };
}

void trex::Dinosaur::jump()
{
    if (currentJumpHight > 0.f)
        return;

    currentJumpSpeed = 10.f;
    state = State::Jumping;
}

void trex::Dinosaur::update(int elapsedTime)
{
    currentJumpHight += currentJumpSpeed;
    position.y = TREX_MIN_Y_POSITION - currentJumpHight;

    if (currentJumpHight > 0.f)
    {
        state = State::Jumping;
        currentJumpSpeed -= 0.4f;
        return;
    }

    state = State::Running;
    currentJumpSpeed = 0.f;
    currentJumpHight = 0.f;
    position.y = TREX_MIN_Y_POSITION;
}

sf::FloatRect trex::Dinosaur::getBoundingBox() const
{
    return { position, size };
}

void trex::Dinosaur::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    auto spriteType = SpriteManager::SpriteType::DinosaurStanding;

    switch (state)
    {
    case State::Running:
        spriteType = animationsManager.getCurrentFrame() % 2 == 0
            ? SpriteManager::SpriteType::DinosaurRunningAnimation1
            : SpriteManager::SpriteType::DinosaurRunningAnimation2;
        break;
    default:
        spriteType = SpriteManager::SpriteType::DinosaurStanding;
        break;
    }

    spriteManager.setSprite(spriteType, position);
    target.draw(spriteManager.getSprite());
}
