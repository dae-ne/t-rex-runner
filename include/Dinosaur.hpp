#pragma once

#include <SFML/Graphics.hpp>

#define TREX_WIDTH 44
#define TREX_HEIGHT 47

namespace trex
{
    class Dinosaur : public sf::Drawable
    {
        enum class State { Running, Jumping };

    public:
        Dinosaur(sf::Texture&);

        void jump();
        void update(int elapsedTime);

    private:
        sf::Sprite sprite;
        State state = State::Running;

        float currentJumpHight = 0.f;
        float currentJumpSpeed = 0.f;

        void draw(sf::RenderTarget&, sf::RenderStates) const;
    };
}
