#pragma once

#include <string>

namespace trex {

struct Config
{
    // WINDOW //

    std::string windowTitle;
    
    unsigned int windowWidth;
    unsigned int windowHeight;
    unsigned int windowPadding;
    unsigned int bitsPerPixel;

};

}
