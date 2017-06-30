#pragma once

#include <string>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

class Player : public Component {
public:
    // NOTE: Remember that these component classes are meant to act as data containers
    // There should be no logic in here really
    Player()
    {
        type = "player";
    }
    ~Player();

    unsigned int health;
    
    unsigned int stamina;
    
    unsigned int score;
    
    bool hasJetpack;
    
private:
};
