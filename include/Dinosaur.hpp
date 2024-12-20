#pragma once

#include <SFML/Graphics.hpp>

namespace trex
{
    class Dinosaur : public sf::Drawable
    {
        enum class State { Running, Jumping };

    public:
        Dinosaur();

        void jump();
        void update();

    private:
        sf::RectangleShape shape;
        State state = State::Running;

        float currentJumpHight = 0;
        float currentJumpSpeed = 0;

        void draw(sf::RenderTarget&, sf::RenderStates) const;
    };
}
