#pragma once

#include <SFML/Graphics.hpp>

class Dinosaur : public sf::Drawable
{
public:
    Dinosaur()
    {
        shape.setSize(sf::Vector2f(100.f, 100.f));
        shape.setFillColor(sf::Color::Red);
    }

private:
    sf::RectangleShape shape;

    void draw(sf::RenderTarget& target, sf::RenderStates) const
    {
        target.draw(shape);
    }
};
