#include "state.hpp"

void trex::Score::update(int timeMs)
{
    score = timeMs / 100;

    if (score > highestScore)
    {
        highestScore = score;
    }
}

void trex::FrameIndexCalculator::update(int elapsedTime)
{
    if (elapsedTime - elapsedTimeSinceLastFrameUpdate < frameTimeMs)
        return;

    currentFrame++;

    if (currentFrame >= frames)
        currentFrame = 0;

    elapsedTimeSinceLastFrameUpdate = elapsedTime;
}

void trex::GameState::update()
{
    if (state != State::Running)
        return;

    auto elapsedTime = clock.getElapsedTime().asMilliseconds();

    score.update(elapsedTime);
    frameIndexCalculator.update(elapsedTime);
}

void trex::GameState::setState(State state)
{
    if (this->state == state)
        return;

    if (state == State::Start || state == State::Running)
    {
        score.reset();
        frameIndexCalculator.reset();
        clock.restart();
    }

    this->state = state;
}
