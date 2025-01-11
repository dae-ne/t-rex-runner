#pragma once

#include <iostream>
#include <mutex>
#include <SFML/Graphics.hpp>

#define TREX_TEXTURE_PATH      "assets/trex.png"
#define OBSTACLES_TEXTURE_PATH "assets/obstacles.png"

namespace trex
{
    class TexturesManager
    {
    public:
        TexturesManager(const TexturesManager&) = delete;

        static TexturesManager* getInstance();

        bool loadFiles();

        sf::Texture& getTrexTexture();
        sf::Texture& getObstaclesTexture();

    private:
        static TexturesManager* pInstance;
        static std::mutex mtx;

        sf::Texture trexTexture;
        sf::Texture obstaclesTexture;

        TexturesManager() {}
    };
}
