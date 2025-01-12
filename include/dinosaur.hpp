#pragma once

#include <SFML/Graphics.hpp>

#include "animations.hpp"
#include "sprites.hpp"

#define TREX_MIN_Y_POSITION 180.f

namespace trex {

class Dinosaur : public sf::Drawable
{
    enum class State { Running, Jumping };

public:
    Dinosaur(SpriteManager&, AnimationsManager&);

    void jump();
    void update(int elapsedTime);

    sf::FloatRect getBoundingBox() const;

private:
    State state = State::Running;

    SpriteManager& spriteManager;
    AnimationsManager& animationsManager;

    sf::Vector2f position = { 40.f, TREX_MIN_Y_POSITION };
    sf::Vector2f size;

    float currentJumpHight = 0.f;
    float currentJumpSpeed = 0.f;

    void draw(sf::RenderTarget&, sf::RenderStates) const;
};

}
