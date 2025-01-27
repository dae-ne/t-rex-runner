#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "config.hpp"
#include "dinosaur.hpp"
#include "gui.hpp"
#include "hud.hpp"
#include "obstacles.hpp"
#include "sprites.hpp"
#include "state.hpp"

namespace trex {

struct LoadingFilesResult
{
    LoadingFilesResult() = default;

    LoadingFilesResult(std::string errorMessage)
    {
        success = false;
        this->errorMessage = errorMessage;
    }

    bool success = true;
    std::string errorMessage;
};

class Game
{
public:
    Game(Config&);

    LoadingFilesResult loadFiles(Config&);
    void configureUI();
    void mainloop();

private:
    void handleEvents();

    void control();
    void update();
    void draw();

    bool loadFontFromFile(std::string path);

    sf::RenderWindow window;
    sf::Font font;

    Config& config;

    GameState gameState;
    GUI gui = GUI(gameState);
    HUD hud;

    SpriteManager spriteManager = SpriteManager();
    Dinosaur dinosaur = Dinosaur(config, spriteManager);
    ObstacleManager obstacleManager = ObstacleManager(spriteManager);

    bool isReloadBlocked = true;
};

}
