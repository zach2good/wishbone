#pragma once

#include <string>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "SpriteSheet.h"

class Sprite : public Component
{
public: 
	Sprite(SpriteSheet* ss, int i)
        : ss(ss), index(i)
	{ 
		
	}

 private:
    SpriteSheet* ss;
    int index;
};

