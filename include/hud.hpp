#pragma once

#include <SFML/Graphics.hpp>

#include "state.hpp"

namespace trex {

class ScoreDisplay : public sf::Drawable
{
public:
    void update(GameState&);

    int getScore() const { return score; }
    int getHighestScore() const { return highestScore; }
    void setHighestScore(int score) { highestScore = score; }

    void setFont(sf::Font& font);

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    int score = 0;
    int highestScore = 0;

    sf::Text text;
};

class HUD : public sf::Drawable
{
public:
    void update(GameState&);

    void setHighestScore(int score) { this->score.setHighestScore(score); }
    void setFont(sf::Font& font) { score.setFont(font); }

private:
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    ScoreDisplay score;
};

}