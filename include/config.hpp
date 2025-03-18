#pragma once

#include <string>

struct Config
{
    // WINDOW //

    const std::string WindowTitle;

    const unsigned int WindowWidth;
    const unsigned int WindowHeight;
    const unsigned int WindowPadding;
    const unsigned int FramerateLimit;


    // COLORS //

    const unsigned int BitsPerPixel;


    // GAME //

    const float DinosaurXPosition;
    const float GroundYPosition;
    const float InitialJumpSpeed;
    const float GravitationalAcceleration;


    // PATHS //
    const std::string FontPath;

};
