#pragma once

#include <SFML/Graphics.hpp>

#define TEXTURE_PATH "assets/texture.png"

enum class SpriteType
{
    DinosaurStanding,
    DinosaurRunningAnimation1,
    DinosaurRunningAnimation2,
    BirdAnimation1,
    BirdAnimation2,
    SmallCactus,
    LargeCactus
};

class SpriteManager
{
public:
    bool loadTextureFromFile();

    sf::Sprite& getSprite() { return sprite; }
    void setSprite(SpriteType spriteType, sf::Vector2f position);

    sf::Vector2f getSize(SpriteType);

private:
    sf::Sprite sprite;
    sf::Texture texture;
};
