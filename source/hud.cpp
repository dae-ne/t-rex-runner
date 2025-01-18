#include <string>

#include "hud.hpp"

std::string getFullScoreString(int score, int highestScore)
{
    auto scoreString = std::to_string(score);
    auto highestScoreString = std::to_string(highestScore);

    auto scoreLength = scoreString.length();
    auto highestScoreLength = highestScoreString.length();

    auto scorePadding = std::string(5 - scoreLength, '0');
    auto highestScorePadding = std::string(5 - highestScoreLength, '0');

    return "HI " + highestScorePadding + highestScoreString + " " + scorePadding + scoreString;
}

void trex::ScoreDisplay::update(GameState& gameState)
{
    auto scoreString = getFullScoreString(gameState.getScore(), gameState.getHighestScore());   
    text.setString(scoreString);
}

void trex::ScoreDisplay::setFont(sf::Font& font)
{
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(14);
    text.setString(getFullScoreString(score, highestScore));

    auto globalBounds = text.getGlobalBounds();

    text.setOrigin(globalBounds.width, 0.f);
    text.setPosition(590.f, 10.f);
}

void trex::ScoreDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text);
}

void trex::HUD::update(GameState &gameState)
{
    score.update(gameState);
}

void trex::HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(score);
}
