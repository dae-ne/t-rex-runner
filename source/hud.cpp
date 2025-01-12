#include <string>

#include "hud.hpp"

std::string getScoreString(int score, int highestScore)
{
    auto scoreString = std::to_string(score);
    auto highestScoreString = std::to_string(highestScore);

    auto scoreLength = scoreString.length();
    auto highestScoreLength = highestScoreString.length();

    auto scorePadding = std::string(5 - scoreLength, '0');
    auto highestScorePadding = std::string(5 - highestScoreLength, '0');

    return "HI " + highestScorePadding + highestScoreString + " " + scorePadding + scoreString;
}

void trex::Score::update(int elapsedTime)
{
    score = elapsedTime / 100;
    text.setString(getScoreString(score, highestScore));
}

void trex::Score::setFont(sf::Font& font)
{
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(14);
    text.setString(getScoreString(score, highestScore));

    auto globalBounds = text.getGlobalBounds();

    text.setOrigin(globalBounds.width, 0.f);
    text.setPosition(590.f, 10.f);
}

void trex::Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text);
}

void trex::Hud::update(int elapsedTime)
{
    score.update(elapsedTime);
}

bool trex::Hud::loadFontFromFile()
{
    auto result = font.loadFromFile(FONT_PATH);
    score.setFont(font);
    return result;
}

void trex::Hud::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(score);
}
