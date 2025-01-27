#pragma once

#include <SFML/Graphics.hpp>

#include "config.hpp"
#include "sprites.hpp"
#include "state.hpp"

namespace trex {

class Dinosaur : public sf::Drawable
{
public:
    Dinosaur(Config&, SpriteManager&);

    void jump();
    void update(GameState&);

    sf::FloatRect getBoundingBox() const;

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const;
    void resetPosition();

    const float MinYPosition;
    const float InitialJumpSpeed;
    const float GravitationalAcceleration;

    SpriteType currentSprite = SpriteType::DinosaurStanding;

    SpriteManager& spriteManager;

    sf::Vector2f position;
    sf::Vector2f size;

    float currentJumpHight = 0.f;
    float currentJumpSpeed = 0.f;
};

}
