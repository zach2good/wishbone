#pragma once

#include <vector>

#include "Component.h"
#include "Sprite.h"

class AnimatedSprite : public Component
{
public:
    AnimatedSprite(double _frametime, std::vector<Sprite*>* _frames)
        : frametime(_frametime), frames(_frames), currentFrame(0), accumulator(0.0)
    {
        type = "anim_sprite";
    }


    // TODO: This is pretty abstract, it should just work with the new renderer, but test it to be sure 
    double frametime;
    double accumulator;
    int currentFrame;
    std::vector<Sprite*>* frames;
};

