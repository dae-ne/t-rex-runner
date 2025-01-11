#pragma once

#include <SFML/Graphics.hpp>

#define TEXTURE_PATH "assets/texture.png"

namespace trex
{
    class SpriteManager
    {
    public:
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

        bool loadTextureFromFile();

        sf::Sprite& getSprite() { return sprite; }
        void setSprite(SpriteType spriteType, sf::Vector2f position);
    
    private:
        sf::Sprite sprite;
        sf::Texture texture;
    };
}
