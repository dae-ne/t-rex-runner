#pragma once

#include <SFML/Graphics.hpp>

#include "sprites.hpp"
#include "state.hpp"

#define TREX_MIN_Y_POSITION 180.f

namespace trex {

class Dinosaur : public sf::Drawable
{
public:
    Dinosaur(SpriteManager&);

    void jump();
    void update(GameState&);

    sf::FloatRect getBoundingBox() const;

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const;
    void resetPosition();

    SpriteType currentSprite = SpriteType::DinosaurStanding;

    SpriteManager& spriteManager;

    sf::Vector2f position = { 40.f, TREX_MIN_Y_POSITION };
    sf::Vector2f size;

    float currentJumpHight = 0.f;
    float currentJumpSpeed = 0.f;
};

}
