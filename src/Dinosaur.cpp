#include "Dinosaur.hpp"

trex::Dinosaur::Dinosaur()
{
    shape.setSize(sf::Vector2f(100.f, 100.f));
    shape.setFillColor(sf::Color::Red);
}

void trex::Dinosaur::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    target.draw(shape);
}
