#include "Dinosaur.hpp"

trex::Dinosaur::Dinosaur()
{
    shape.setSize(sf::Vector2f(100.f, 100.f));
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin({ 0.f,  shape.getGlobalBounds().height });
    shape.setPosition({ 100.f, 400.f });
}

void trex::Dinosaur::jump()
{
    if (currentJumpHight > 0)
        return;

    currentJumpSpeed = 10.f;
    state = State::Jumping;
}

void trex::Dinosaur::update()
{
    auto position = shape.getPosition();

    currentJumpHight += currentJumpSpeed;
    shape.setPosition({ position.x, 400.f - currentJumpHight });

    if (currentJumpHight > 0.f)
    {
        state = State::Jumping;
        currentJumpSpeed -= 0.2f;
        return;
    }

    state = State::Running;
    currentJumpSpeed = 0.f;
    currentJumpHight = 0.f;
}

void trex::Dinosaur::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    target.draw(shape);
}
