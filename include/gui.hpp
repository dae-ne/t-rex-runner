#pragma once

#include <SFML/Graphics.hpp>

#include "config.hpp"
#include "state.hpp"

class GameOverScreen : public sf::Drawable
{
public:
    void configure(Config&);
    void setFont(sf::Font&);

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    sf::Text text;
};

class GUI : public sf::Drawable
{
public:
    GUI(GameState& gs) : gameState(gs) {}

    void configure(Config&);
    void setFont(sf::Font&);

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    GameState& gameState;
    GameOverScreen gameOverScreen;
};
