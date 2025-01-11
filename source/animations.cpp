#include "animations.hpp"

void trex::AnimationsManager::update(int elapsedTime)
{
    if (elapsedTime - this->elapsedTime < frameTime)
        return;

    currentFrame++;

    if (currentFrame >= frames)
        currentFrame = 0;

    this->elapsedTime = elapsedTime;
}
