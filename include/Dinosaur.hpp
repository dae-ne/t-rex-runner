#pragma once

#include <SFML/Graphics.hpp>

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

        float currentJumpHight = 0;
        float currentJumpSpeed = 0;

        void draw(sf::RenderTarget&, sf::RenderStates) const;
    };
}
