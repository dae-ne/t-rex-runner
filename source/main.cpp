#include <iostream>

#include "config.hpp"
#include "game.hpp"

int main()
{
    trex::Config config = {

        // WINDOW //

        "T-Rex Runner", // title
        600u,           // width
        200u,           // height
        10u,            // padding
        
    };

    auto game = trex::Game(config);
    auto [success, errorMessage] = game.loadFiles();

    if (!success)
    {
        std::cerr << errorMessage << std::endl;
        return 1;
    }

    game.mainloop();
}
