#include "game.hpp"

trex::Game::Game()
{
    pWindow = new sf::RenderWindow({ WindowWidth, WindowHeight }, WindowName,
        sf::Style::Titlebar | sf::Style::Close);
    
    pWindow->setFramerateLimit(60);
}

trex::Game::~Game()
{
    delete pWindow;
}

trex::LoadingFilesResult trex::Game::loadFiles()
{
    if (!spriteManager.loadTextureFromFile())
    {
        return LoadingFilesResult("Failed to load texture!");
    }

    if (!hud.loadFontFromFile())
    {
        return LoadingFilesResult("Failed to load font!");
    }

    return LoadingFilesResult();
}

void trex::Game::mainloop()
{
    while (pWindow->isOpen())
    {
        handleEvents();

        control();
        update();
        draw();
    }
}

void trex::Game::handleEvents()
{
    for (auto event = sf::Event(); pWindow->pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
        {
            pWindow->close();
        }

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Space)
        {
            switch (gameState.getState())
            {
            case GameState::State::Start:
                gameState.setState(GameState::State::Running);
                break;
            case GameState::State::Dead:
                gameState.setState(GameState::State::Start);
                break;
            default:
                break;
            }
        }
    }
}

void trex::Game::control()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        dinosaur.jump();
    }
}

void trex::Game::update()
{
    gameState.update();
    dinosaur.update(gameState);
    obstacleManager.updateObstacles(gameState);
    hud.update(gameState);

    if (obstacleManager.isColliding(dinosaur.getBoundingBox()))
        gameState.setState(GameState::State::Dead);

    if (gameState.getState() == GameState::State::Start && gameState.getHighestScore() > 0)
        gameState.setState(GameState::State::Running);
}

void trex::Game::draw()
{
    pWindow->clear(sf::Color::Red);
    obstacleManager.drawObstacles(*pWindow);
    pWindow->draw(dinosaur);
    pWindow->draw(hud);
    pWindow->display();
}
