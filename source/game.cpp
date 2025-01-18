#include "game.hpp"

trex::Game::Game(Config& config) : config(config)
{
    sf::VideoMode mode = {
        config.windowWidth,
        config.windowHeight,
        config.bitsPerPixel
    };

    auto style = sf::Style::Titlebar | sf::Style::Close;

    window.create(mode, config.windowTitle, style);
    window.setFramerateLimit(60);
}

trex::LoadingFilesResult trex::Game::loadFiles()
{
    if (!spriteManager.loadTextureFromFile())
        return { "Failed to load texture!" };

    if (!loadFontFromFile())
        return { "Failed to load font!" };

    return {};
}

void trex::Game::mainloop()
{
    while (window.isOpen())
    {
        handleEvents();

        control();
        update();
        draw();
    }
}

void trex::Game::handleEvents()
{
    auto state = gameState.getState();

    for (auto event = sf::Event(); window.pollEvent(event);)
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return;
        }

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Space &&
            !isReloadBlocked)
        {
            switch (state)
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

    if (state == GameState::State::Running)
    {
        isReloadBlocked = true;
        return;
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        isReloadBlocked = false;
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
    window.clear(sf::Color::Red);

    obstacleManager.drawObstacles(window);
    window.draw(dinosaur);
    window.draw(hud);
    window.draw(gui);

    window.display();
}

bool trex::Game::loadFontFromFile()
{
    auto result = font.loadFromFile(FONT_PATH);
    hud.setFont(font);
    gui.setFont(font);
    return result;
}
