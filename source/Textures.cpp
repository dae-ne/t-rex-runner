#include "Textures.hpp"

trex::TexturesManager* trex::TexturesManager::pInstance = nullptr;
std::mutex trex::TexturesManager::mtx;

trex::TexturesManager* trex::TexturesManager::getInstance()
{
    if (pInstance != nullptr)
        return pInstance;
    
    std::lock_guard<std::mutex> lock(mtx);

    if (pInstance == nullptr)
        pInstance = new TexturesManager();

    return pInstance;
}

bool trex::TexturesManager::loadFiles()
{
    if (!trexTexture.loadFromFile(TREX_TEXTURE_PATH))
        return false;

    if (!obstaclesTexture.loadFromFile(OBSTACLES_TEXTURE_PATH))
        return false;

    return true;
}

sf::Texture& trex::TexturesManager::getTrexTexture()
{
    return trexTexture;
}

sf::Texture& trex::TexturesManager::getObstaclesTexture()
{
    return obstaclesTexture;
}
