#pragma once

#include <SFML/Graphics.hpp>

#include <state.hpp>

namespace trex {

class GameOverScreen : public sf::Drawable
{
public:
    void setFont(sf::Font&);

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    sf::Text text;
};

class GUI : public sf::Drawable
{
public:
    GUI(GameState& gs) : gameState(gs) {}

    void setFont(sf::Font&);

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    GameState& gameState;
    GameOverScreen gameOverScreen;
};

}
