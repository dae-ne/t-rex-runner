#include <iostream>

#include "config.hpp"
#include "game.hpp"

int main()
{
    trex::Config config = {

        // WINDOW //

        "T-Rex Runner",     // title
        600u,               // width
        200u,               // height
        10u,                // padding
        60u,                // framerate limit


        // COLORS //

        8u,                 // bits per pixel


        // GAME //

        40.f,               // dinosaur X position
        180.f,              // ground level (y position)
        10.f,               // initial jump speed
        .4f,                // gravitational acceleration


        // PATHS //

        "assets/font.ttf",  // font path
        
    };
    

    auto game = trex::Game(config);
    auto [success, errorMessage] = game.loadFiles(config);

    if (!success)
    {
        std::cerr << errorMessage << std::endl;
        return 1;
    }

    game.configureUI();
    game.mainloop();
}
