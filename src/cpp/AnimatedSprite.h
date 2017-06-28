#pragma once

#include <vector>
#include <stdarg.h>  

#include "Component.h"
#include "Sprite.h"

class AnimatedSprite : public Component
{
public:
    AnimatedSprite(double _frametime, int n, ...)
        : frametime(_frametime), currentFrame(0)
    {
        type = "anim_sprite";
		accumulator = rand() % 1000;
		frames = std::vector<Sprite*>();

		va_list vl;
		va_start(vl, n);
		for (int i = 0; i<n-1; i++)
		{
			auto val = va_arg(vl, Sprite*);
			frames.push_back(val);
		}
		va_end(vl);
    }

    double frametime;
    double accumulator;
    int currentFrame;
    std::vector<Sprite*> frames;
};

