#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "dinosaur.hpp"
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

    sf::RenderWindow* pWindow;

    GameState gameState = GameState();
    HUD hud = HUD();

    SpriteManager spriteManager = SpriteManager();
    Dinosaur dinosaur = Dinosaur(spriteManager);
    ObstacleManager obstacleManager = ObstacleManager(spriteManager);
};

}
