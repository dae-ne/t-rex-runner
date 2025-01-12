#pragma once

#include <SFML/Graphics.hpp>

#define FONT_PATH "assets/font.ttf"

namespace trex {

class Score : public sf::Drawable
{
public:
    void update(int elapsedTime);

    int getScore() const { return score; }
    int getHighestScore() const { return highestScore; }
    void setHighestScore(int score) { highestScore = score; }

    void setFont(sf::Font& font);

private:
    int score = 0;
    int highestScore = 0;

    sf::Text text;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

class Hud : public sf::Drawable
{
public:
    void update(int elapsedTime);
    bool loadFontFromFile();

    void setHighestScore(int score) { this->score.setHighestScore(score); }

private:
    sf::Font font;
    Score score;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

}