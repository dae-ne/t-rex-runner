#include "gui.hpp"

void trex::GameOverScreen::configure(Config& config)
{
    text.setString("GAME OVER");
    text.setFillColor(sf::Color::Black);
    
    auto globalBounds = text.getGlobalBounds();
    text.setOrigin(globalBounds.width / 2.f, globalBounds.height / 2.f);
    text.setPosition(config.WindowWidth / 2, config.WindowHeight / 2);
}

void trex::GameOverScreen::setFont(sf::Font &font)
{
    text.setFont(font);
}

void trex::GameOverScreen::draw(sf::RenderTarget& target, sf::RenderStates ) const
{
    target.draw(text);
}

void trex::GUI::configure(Config& config)
{
    gameOverScreen.configure(config);
}

void trex::GUI::setFont(sf::Font &font)
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
