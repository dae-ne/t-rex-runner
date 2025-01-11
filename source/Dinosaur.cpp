#include "Dinosaur.hpp"

trex::Dinosaur::Dinosaur(sf::Texture& texture)
{
    sprite.setTexture(texture);
    sprite.setTextureRect({ 0, 0, TREX_WIDTH, TREX_HEIGHT });
    sprite.setOrigin({ 0.f,  TREX_HEIGHT });
    sprite.setPosition({ 40.f, 180.f });
}

void trex::Dinosaur::jump()
{
    if (currentJumpHight > 0.f)
        return;

    currentJumpSpeed = 10.f;
    state = State::Jumping;

    sprite.setTextureRect({ 0, 0, TREX_WIDTH, TREX_HEIGHT });
}

void trex::Dinosaur::update(int elapsedTime)
{
    auto position = sprite.getPosition();

    currentJumpHight += currentJumpSpeed;
    sprite.setPosition({ position.x, 180.f - currentJumpHight });

    if (currentJumpHight > 0.f)
    {
        state = State::Jumping;
        currentJumpSpeed -= 0.4f;
        return;
    }

    state = State::Running;
    currentJumpSpeed = 0.f;
    currentJumpHight = 0.f;

    elapsedTime % 200 < 100
        ? sprite.setTextureRect({ TREX_WIDTH, 0, TREX_WIDTH, TREX_HEIGHT })
        : sprite.setTextureRect({ 2 * TREX_WIDTH, 0, TREX_WIDTH, TREX_HEIGHT });
}

void trex::Dinosaur::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    target.draw(sprite);
}
