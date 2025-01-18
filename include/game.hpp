#pragma once

#include <SFML/Graphics.hpp>
#include <string>

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
    Game();
    ~Game();

    LoadingFilesResult loadFiles();
    void mainloop();

private:
    void handleEvents();

    void control();
    void update();
    void draw();

    bool loadFontFromFile();

    const unsigned int WindowWidth = 600u;
    const unsigned int WindowHeight = 200u;
    const std::string WindowName = "T-Rex Runner";

    sf::RenderWindow* pWindow;
    sf::Font font;

    GameState gameState;
    GUI gui = GUI(gameState);
    HUD hud;

    SpriteManager spriteManager = SpriteManager();
    Dinosaur dinosaur = Dinosaur(spriteManager);
    ObstacleManager obstacleManager = ObstacleManager(spriteManager);

    bool isReloadBlocked = true;
};

}
