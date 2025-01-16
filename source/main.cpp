#include <iostream>

#include "game.hpp"

int main()
{
    auto game = trex::Game();
    auto loadingFilesResult = game.loadFiles();

    if (!loadingFilesResult.success)
    {
        std::cerr << loadingFilesResult.errorMessage << std::endl;
    }

    game.mainloop();
}
