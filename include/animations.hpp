#pragma once

namespace trex {

class AnimationsManager
{
public:
    AnimationsManager(int frames, int frameTime)
        : frames(frames), frameTime(frameTime) {}

    void update(int elapsedTime);
    int getCurrentFrame() const { return currentFrame; }
    int getFramesNumber() const { return frames; }

private:
    int frames;
    int frameTime;

    int currentFrame = 0;
    int elapsedTime = 0;
};

}
