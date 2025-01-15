#pragma once

#include <SFML/System/Clock.hpp>

namespace trex {

class Score
{
public:
    void update(int timeMs);

    int getScore() const { return score; }
    int getHighestScore() const { return highestScore; }

    void reset() { score = 0; }

private:
    int score = 0;
    int highestScore = 0;
};

class FrameIndexCalculator
{
public:
    FrameIndexCalculator(int frames, int frameTimeMs)
        : frames(frames), frameTimeMs(frameTimeMs) {}

    void update(int elapsedTime);

    int getCurrentFrameNumber() const { return currentFrame; }
    int getTotalNumberOfFrames() const { return frames; }

    void reset() { currentFrame = 0; elapsedTimeSinceLastFrameUpdate = 0; }

private:
    int frames;
    int frameTimeMs;

    int currentFrame = 0;
    int elapsedTimeSinceLastFrameUpdate = 0;
};


class GameState
{
public:
    enum class State
    {
        Start,
        Running,
        Dead
    };

    void update();

    void setState(State state);
    State getState() const { return state; }

    int getScore() const { return score.getScore(); }
    int getHighestScore() const { return score.getHighestScore(); }

    int getCurrentFrameNumber() const { return frameIndexCalculator.getCurrentFrameNumber(); }
    int getTotalNumberOfFrames() const { return frameIndexCalculator.getTotalNumberOfFrames(); }

    int getInGameTimeMs() const { return clock.getElapsedTime().asMilliseconds(); }

private:
    sf::Clock clock;
    State state = State::Start;
    Score score = Score();
    FrameIndexCalculator frameIndexCalculator = FrameIndexCalculator(8, 100);
};

}
