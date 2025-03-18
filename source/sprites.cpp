#include "sprites.hpp"

bool SpriteManager::loadTextureFromFile()
{
    bool result = texture.loadFromFile(TEXTURE_PATH);
    sprite.setTexture(texture);
    return result;
}

void SpriteManager::setSprite(SpriteType spriteType, sf::Vector2f position)
{
    switch (spriteType)
    {
    case SpriteType::DinosaurStanding:
        sprite.setTextureRect({ 0, 0, 44, 47 });
        break;
    case SpriteType::DinosaurRunningAnimation1:
        sprite.setTextureRect({ 44, 0, 44, 47 });
        break;
    case SpriteType::DinosaurRunningAnimation2:
        sprite.setTextureRect({ 88, 0, 44, 47 });
        break;
    case SpriteType::BirdAnimation1:
        sprite.setTextureRect({ 0, 48, 46, 39 });
        break;
    case SpriteType::BirdAnimation2:
        sprite.setTextureRect({ 46, 48, 46, 39 });
        break;
    case SpriteType::SmallCactus:
        sprite.setTextureRect({ 0, 89, 17, 35 });
        break;
    case SpriteType::LargeCactus:
        sprite.setTextureRect({ 18, 89, 25, 50 });
        break;
    default:
        break;
    }

    sprite.setOrigin({ 0.f, sprite.getGlobalBounds().height });
    sprite.setPosition(position);
}

sf::Vector2f SpriteManager::getSize(SpriteType spriteType)
{
    setSprite(spriteType, { 0.f, 0.f });
    auto globalBounds = sprite.getGlobalBounds();
    return { globalBounds.width, globalBounds.height };
}
