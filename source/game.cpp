#include "game.hpp"

trex::Game::Game()
{
    pWindow = new sf::RenderWindow({ 600u, 200u }, "T-Rex Runner",
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
            event.key.code == sf::Keyboard::Space &&
            gameState.getState() == trex::GameState::State::Start)
        {
            gameState.setState(trex::GameState::State::Running);
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
        gameState.setState(trex::GameState::State::Dead);
}

void trex::Game::draw()
{
    pWindow->clear(sf::Color::Red);
    obstacleManager.drawObstacles(*pWindow);
    pWindow->draw(dinosaur);
    pWindow->draw(hud);
    pWindow->display();
}
