#pragma once

#include <string>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class Player : public Component {
public:
    Player()
    {
        type = "player";
    }
    ~Player();
    
private:
};
