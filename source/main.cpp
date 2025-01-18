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
    auto loadingFilesResult = game.loadFiles();

    if (!loadingFilesResult.success)
    {
        std::cerr << loadingFilesResult.errorMessage << std::endl;
    }

    game.mainloop();
}
