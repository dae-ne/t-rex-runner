#include "Dinosaur.hpp"

trex::Dinosaur::Dinosaur(sf::Texture& texture)
{
    sprite.setTexture(texture);
    sprite.setTextureRect({ 677, 2, 44, 46 });
    sprite.setOrigin({ 0.f,  sprite.getGlobalBounds().height });
    sprite.setPosition({ 40.f, 180.f });
}

void trex::Dinosaur::jump()
{
    if (currentJumpHight > 0.f)
        return;

    currentJumpSpeed = 10.f;
    state = State::Jumping;

    sprite.setTextureRect({ 677, 2, 44, 46 });
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
        ? sprite.setTextureRect({ 765, 2, 44, 46 })
        : sprite.setTextureRect({ 809, 2, 44, 46 });
}

void trex::Dinosaur::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    target.draw(sprite);
}
