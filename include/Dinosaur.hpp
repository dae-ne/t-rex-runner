#pragma once

#include <SFML/Graphics.hpp>

namespace trex
{
    class Dinosaur : public sf::Drawable
    {
    public:
        Dinosaur();

    private:
        sf::RectangleShape shape;

        void draw(sf::RenderTarget&, sf::RenderStates) const;
    };
}
