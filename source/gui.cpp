#include "gui.hpp"

void trex::GameOverScreen::setFont(sf::Font &font)
{
    text.setFont(font);
    text.setString("GAME OVER");
}

void trex::GameOverScreen::draw(sf::RenderTarget& target, sf::RenderStates ) const
{
    target.draw(text);
}

void trex::GUI::setFont(sf::Font& font)
{
    gameOverScreen.setFont(font);
}

void trex::GUI::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    switch (gameState.getState())
    {
    case GameState::State::Dead:
        target.draw(gameOverScreen);
        break;
    default:
        break;
    }
}
