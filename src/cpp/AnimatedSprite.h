#pragma once

#include <vector>

#include "Component.h"
#include "Sprite.h"

class AnimatedSprite : public Component
{
public:
    AnimatedSprite(double _frametime, std::vector<Sprite*>* _frames)
        : frametime(_frametime), frames(_frames), currentFrame(0)
    {
        type = "anim_sprite";
		accumulator = rand() % 1000;
    }

    double frametime;
    double accumulator;
    int currentFrame;
    std::vector<Sprite*>* frames;
};

